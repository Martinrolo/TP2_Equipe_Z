/*
Module: T_SORTIE
Description: Définit le type t_sortie (sortie de circuit) et fournit les
			 fonctions pour le manipuler.
Auteur: Martin Rolo Dussault & Antoine St-Amour
*/

#include "t_sortie.h"

t_sortie* t_sortie_init(int id, char* nom)
{
	t_sortie* sortie = (t_sortie*)malloc(sizeof(t_sortie));

	entree->id = id;
	entree->nom = (char*)calloc(NOM_ENTREE_TAILLE_MAX, sizeof(char));

	return entree;
}

/***************************************************************************/
void t_sortie_destroy(t_sortie* sortie)
{

}

/***************************************************************************/
t_pin_entree* t_sortie_get_pin(t_sortie* sortie)
{

}

/***************************************************************************/
int t_sortie_relier(t_sortie* dest, char* nom_composant, const t_pin_sortie* source)
{

}

/***************************************************************************/
int t_sortie_est_reliee(t_sortie* sortie)
{

}

/***************************************************************************/
void t_sortie_reset(t_sortie* sortie)
{

}

/***************************************************************************/
int t_sortie_get_valeur(const t_sortie* sortie)
{

}

/***************************************************************************/
int t_sortie_get_id(const t_sortie* sortie)
{

}

/***************************************************************************/
char* t_sortie_get_nom(const t_sortie* sortie)
{

}

/***************************************************************************/
void t_sortie_serialiser(const t_sortie* sortie, char* resultat)
{

}
