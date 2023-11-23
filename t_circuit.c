/*
Module: T_CIRCUIT
Description: D�finit le type t_entree (Entr�e de circuit) et fournit les
			 fonctions pour le manipuler.
Auteurs: Martin Rolo Dussault, Maxim Dmitriev & Antoine St-Amour
*/

#include "t_circuit.h"

t_circuit* t_circuit_init(void)
{
	//Cr�er un nouveau circuit
	t_circuit* nouveau_circuit;
	nouveau_circuit = (t_circuit*)malloc(sizeof(t_circuit));

	//Mettre tous les nombres d'�l�ments � 0
	nouveau_circuit->nb_entrees = 0;
	nouveau_circuit->nb_sorties = 0;
	nouveau_circuit->nb_portes = 0;

	//Mettre tous les �l�ments des tableaux � NULL
	for (int i = 0; i < MAX_ENTREES; i++)
	{
		nouveau_circuit->nb_entrees = NULL;
	}

	for (int i = 0; i < MAX_SORTIES; i++)
	{
		nouveau_circuit->nb_sorties = NULL;
	}

	for (int i = 0; i < CIRCUIT_MAX_PORTES; i++)
	{
		nouveau_circuit->nb_portes = NULL;
	}

	return nouveau_circuit;
}

/********************************************************************/
void t_circuit_destroy(t_circuit* circuit)
{
	free(circuit);
}

/********************************************************************/
t_porte* t_circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type, int id, char* nom)
{
	if (circuit->nb_portes == CIRCUIT_MAX_PORTES)
		return NULL; //On ne peut pas cr�er une nouvelle porte

	//Sinon, cr�er la porte
	t_porte* porte;
	porte = t_porte_init(id, le_type, nom);

	//Ajouter la porte � l'indice du nombre de portes
	circuit->portes[circuit->nb_portes] = porte;
	circuit->nb_portes++;

	return porte;

}

/********************************************************************/
t_entree* t_circuit_ajouter_entree(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_entrees == MAX_ENTREES)
		return NULL; //On ne peut pas cr�er une nouvelle entr�e

	//Sinon, cr�er l'entr�e
	t_entree* entree;
	entree = t_entree_init(id, nom);

	//Ajouter la porte � l'indice du nombre de portes
	circuit->entrees[circuit->nb_entrees] = entree;
	circuit->nb_entrees++;

	return entree;
}

/********************************************************************/
t_sortie* t_circuit_ajouter_sortie(t_circuit* circuit, int id, char* nom)
{
	if (circuit->nb_sorties == MAX_SORTIES)
		return NULL; //On ne peut pas cr�er une nouvelle sortie

	//Sinon, cr�er l'entr�e
	t_sortie* sortie;
	sortie = t_sortie_init(id, nom);

	//Ajouter la porte � l'indice du nombre de portes
	circuit->sorties[circuit->nb_sorties] = sortie;
	circuit->nb_sorties++;

	return sortie;
}

/********************************************************************/
int t_circuit_est_valide(t_circuit* circuit)
{

}

/********************************************************************/
int t_circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{

}

/********************************************************************/
void t_circuit_reset(t_circuit* circuit)
{

}

/********************************************************************/
int t_circuit_propager_signal(t_circuit* circuit)
{

}

/********************************************************************/
int t_circuit_get_nb_portes(const t_circuit* circuit)
{

}

/********************************************************************/
t_porte* t_circuit_get_porte(const t_circuit* circuit, int pos)
{

}

/********************************************************************/
int t_circuit_get_nb_sorties(const t_circuit* circuit)
{

}

/********************************************************************/
t_sortie* t_circuit_get_sortie(const t_circuit* circuit, int pos)
{

}

/********************************************************************/
int t_circuit_get_nb_entrees(const t_circuit* circuit)
{

}

/********************************************************************/
t_entree* t_circuit_get_entree(const t_circuit* circuit, int pos)
{

}