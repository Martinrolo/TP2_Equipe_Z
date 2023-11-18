/*
Module: T_ENTREE
Description: D�finit le type t_entree (Entr�e de circuit) et fournit les
			 fonctions pour le manipuler.
Auteur: Martin Rolo Dussault & Antoine St-Amour
*/

#include "t_entree.h"

t_entree* t_entree_init(int id, char* nom)
{
	t_entree* entree = (t_entree*)malloc(sizeof(t_entree));

    entree->id = id;
	entree->nom = *nom;

	return entree;
}

/********************************************************************/
void t_entree_destroy(t_entree* entree)
{

}

/********************************************************************/
t_pin_sortie* t_entree_get_pin(t_entree* entree)
{

}

/********************************************************************/
int t_entree_est_reliee(t_entree* entree)
{

}

/********************************************************************/
void t_entree_reset(t_entree* entree)
{

}

/********************************************************************/
int t_entree_propager_signal(t_entree* entree)
{

}

/********************************************************************/
int t_entree_get_valeur(const t_entree* entree)
{

}

/********************************************************************/
int t_entree_get_id(const t_entree* entree)
{

}


/********************************************************************/
char* t_entree_get_nom(const t_entree* entree)
{

}

/********************************************************************/
void t_entree_serialiser(const t_entree* entree, char* resultat)
{

}