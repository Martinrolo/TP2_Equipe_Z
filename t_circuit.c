/*
Module: T_CIRCUIT
Description: Définit le type t_entree (Entrée de circuit) et fournit les
			 fonctions pour le manipuler.
Auteurs: Martin Rolo Dussault, Maxim Dmitriev & Antoine St-Amour
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "t_circuit.h"
#include "FILESLIB.h"

t_circuit* t_circuit_init(void)
{
	//Créer un nouveau circuit
	t_circuit* nouveau_circuit;
	nouveau_circuit = (t_circuit*)malloc(sizeof(t_circuit));

	//Mettre tous les nombres d'éléments à 0
	nouveau_circuit->nb_entrees = NULL;
	nouveau_circuit->nb_sorties = NULL;
	nouveau_circuit->nb_portes = NULL;

	//Mettre tous les éléments des tableaux à NULL
	for (int i = 0; i < MAX_ENTREES; i++)
	{
		nouveau_circuit->entrees[i] = NULL;
	}

	for (int i = 0; i < MAX_SORTIES; i++)
	{
		nouveau_circuit->sorties[i] = NULL;
	}

	for (int i = 0; i < CIRCUIT_MAX_PORTES; i++)
	{
		nouveau_circuit->portes[i] = NULL;
	}

	return nouveau_circuit;
}

/********************************************************************/
void t_circuit_destroy(t_circuit* circuit)
{
	//pour chaque entree: t_entree_destroy
	//Pourchaque sortie: t_sortie_destroy
	//Pour chaque porte: t_porte_destroy
	int i;

	for (i = 0;i < circuit->nb_entrees;i++)
		t_entree_destroy(circuit->entrees[i]);

	for (i = 0;i < circuit->nb_sorties;i++)
		t_sortie_destroy(circuit->sorties[i]);

	for (i = 0;i < circuit->nb_portes;i++)
		t_porte_destroy(circuit->portes[i]);

	free(circuit);
}

/********************************************************************/
t_porte* t_circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type, int id, char* nom)
{
	if (circuit->nb_portes == CIRCUIT_MAX_PORTES)
		return NULL; //On ne peut pas créer une nouvelle porte

	//Sinon, créer la porte
	t_porte* porte;
	porte = t_porte_init(id, le_type, nom);

	//Ajouter la porte à l'indice du nombre de portes
	circuit->portes[circuit->nb_portes] = porte;
	circuit->nb_portes++;

	return porte;
}

/********************************************************************/
t_entree* t_circuit_ajouter_entree(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_entrees == MAX_ENTREES)
		return NULL; //On ne peut pas créer une nouvelle entrée

	//Sinon, créer l'entrée
	t_entree* entree;
	entree = t_entree_init(id, nom);

	//Ajouter la porte à l'indice du nombre de portes
	circuit->entrees[circuit->nb_entrees] = entree;
	circuit->nb_entrees++;

	return entree;
}

/********************************************************************/
t_sortie* t_circuit_ajouter_sortie(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_sorties == MAX_SORTIES)
		return NULL; //On ne peut pas créer une nouvelle sortie

	//Sinon, créer l'entrée
	t_sortie* sortie;
	sortie = t_sortie_init(id, nom);

	//Ajouter la porte à l'indice du nombre de portes
	circuit->sorties[circuit->nb_sorties] = sortie;
	circuit->nb_sorties++;

	return sortie;
}

/********************************************************************/
int t_circuit_est_valide(t_circuit* circuit)
{
	int compteur_pas_reliee = 0;
	
	//Vérifier les entrées
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		if (!t_entree_est_reliee(circuit->entrees[i]))
			compteur_pas_reliee++;
	}

	//Vérifier les sorties
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		if (!t_sortie_est_reliee(circuit->sorties[i]))
			compteur_pas_reliee++;
	}

	//Vérifier les entrées
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		if (!t_porte_est_reliee(circuit->portes[i]))
			compteur_pas_reliee++;
	}

	//Si au moins 1 composant n'est pas relié, on retourne FAUX
	if (compteur_pas_reliee > 0)
		return FAUX;

	//Sinon, tout va bien
	return VRAI;
}

/********************************************************************/
int t_circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{
	//Si on a pas assez de bits pour chaque entrée, c'est pas bon
	if (nb_bits != circuit->nb_entrees)
		return FAUX;

	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		//Pour chaque entrée, on met la valeur du signal à son pin de sortie
		t_pin_sortie_set_valeur(circuit->entrees[i]->pin, signal[i]);
	}

	return VRAI;
}

/********************************************************************/
void t_circuit_reset(t_circuit* circuit)
{
	//Reset les entrees
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_reset(circuit->entrees[i]);
	}

	//Reset les sorties
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_reset(circuit->sorties[i]);
	}

	//Reset les portes
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_reset(circuit->portes[i]);
	}
}

/********************************************************************/
int t_circuit_propager_signal(t_circuit* circuit)
{
	//Init t_file file_portes
	t_file file_portes;
	initfile(&file_portes);
	
	t_porte* porte_courante = NULL; //Créer pointeur vers une porte
	int nb_iterations = 0;

	//Si le circuit n'est pas valide, on retourne faux
	if (!t_circuit_est_valide(circuit))
		return FAUX;

	//Si le signal n'a pas été appliqué à une entrée, on retourne faux
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		if (t_entree_get_pin(circuit->entrees[i]) == INACTIF)
			return FAUX;
	}

	//S'il y a une boucle dans le programme, on retourne faux
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		//pour chaque pin entrée de chaque porte
		for (int j = 0; j < circuit->portes[i]->nb_entrees; j++)
		{
			//Si un des pin d'entrées est relié à la sortie de la même porte, on retourne faux.
			if (circuit->portes[i]->entrees[j]->liaison == circuit->portes[i]->sortie)
				return FAUX;
		}
	}

	//Propager le signal de toutes les entrées
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_propager_signal(circuit->entrees[i]);
	}

	//Ajouter les portes à la file
	for (int i = 0; i < circuit->nb_portes; i++)
		ajouterfin(&file_portes, circuit->portes[i]);

	//Défiler les portes
	while (!vide(&file_portes) && nb_iterations < (circuit->nb_portes * (circuit->nb_portes + 1) / 2))
	{
		enleverdebut(&file_portes, &porte_courante);
		int result_propager = t_porte_propager_signal(porte_courante);

		//Si le signal ne se propage pas, on remet la porte dans la file
		if (result_propager == FAUX)
			ajouterfin(&file_portes, porte_courante);

		nb_iterations++;
	}

	//Si la file est vide, le signal a réussi à se propager
	if (vide(&file_portes))
		return VRAI;
	
	return FAUX;
}

/********************************************************************/
int t_circuit_get_nb_portes(const t_circuit* circuit)
{
	return circuit->nb_portes;
}

/********************************************************************/
t_porte* t_circuit_get_porte(const t_circuit* circuit, int pos)
{
	//Retourner la sortie si la position est valide
	if (pos < CIRCUIT_MAX_PORTES && pos > -1)
		return circuit->portes[pos];

	return NULL;
}

/********************************************************************/
int t_circuit_get_nb_sorties(const t_circuit* circuit)
{
	return circuit->nb_sorties;
}

/********************************************************************/
t_sortie* t_circuit_get_sortie(const t_circuit* circuit, int pos)
{
	//Retourner la sortie si la position est valide
	if (pos < MAX_SORTIES && pos > -1)
		return circuit->sorties[pos];

	return NULL;
}

/********************************************************************/
int t_circuit_get_nb_entrees(const t_circuit* circuit)
{
	return circuit->nb_entrees;
}

/********************************************************************/
t_entree* t_circuit_get_entree(const t_circuit* circuit, int pos)
{
	//Retourner l'entree si la position est valide
	if (pos < MAX_ENTREES && pos > -1)
		return circuit->entrees[pos];

	return NULL;
}