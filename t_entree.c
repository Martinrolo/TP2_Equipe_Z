/*
Module: T_ENTREE
Description: Définit le type t_entree (Entrée de circuit) et fournit les
			 fonctions pour le manipuler.
Auteur: Martin Rolo Dussault & Antoine St-Amour
*/

#include "t_entree.h"

t_entree* t_entree_init(int id, char* nom)
{
	t_entree* entree = (t_entree*)malloc(sizeof(t_entree));

    entree->id = id;
	entree->nom = (char*)calloc(NOM_ENTREE_TAILLE_MAX, sizeof(char));

	return entree;
}

/********************************************************************/
void t_entree_destroy(t_entree* entree)
{
	//D'abord détruire le pin de sortie de l'entrée
	t_pin_sortie_destroy(entree->pin);

	free(entree->nom);
	free(entree);
}

/********************************************************************/
t_pin_sortie* t_entree_get_pin(t_entree* entree)
{
	return entree->pin;
}

/********************************************************************/
int t_entree_est_reliee(t_entree* entree)
{
	return t_pin_sortie_est_reliee(entree->pin);
}

/********************************************************************/
void t_entree_reset(t_entree* entree)
{
	t_pin_sortie_reset(entree->pin);
}

/********************************************************************/
int t_entree_propager_signal(t_entree* entree)
{
	t_pin_sortie_propager_signal(entree->pin);
}

/********************************************************************/
int t_entree_get_valeur(const t_entree* entree)
{
	t_pin_sortie_get_valeur(entree->pin);
}

/********************************************************************/
int t_entree_get_id(const t_entree* entree)
{
	return entree->id;
}


/********************************************************************/
char* t_entree_get_nom(const t_entree* entree)
{
	return entree->nom;
}

/********************************************************************/
void t_entree_serialiser(const t_entree* entree, char* resultat)
{
	//Afficher id
	printf("ID: %d", entree->id);

	//CONTINUER...
}