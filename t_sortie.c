/*
Module: T_SORTIE
Description: Définit le type t_sortie (sortie de circuit) et fournit les
			 fonctions pour le manipuler.
Auteurs: Martin Rolo Dussault, Maxim Dmitriev & Antoine St-Amour
*/

#include "t_sortie.h"

t_sortie* t_sortie_init(int id, char* nom)
{
	t_sortie* sortie = (t_sortie*)malloc(sizeof(t_sortie));

	sortie->id = id;
	sortie->nom = nom;
	sortie->pin = t_pin_entree_init();

	return sortie;
}

/***************************************************************************/
void t_sortie_destroy(t_sortie* sortie)
{
	//D'abord détruire le pin d'entrée de la sortie
	t_pin_entree_destroy(sortie->pin);

	free(sortie);
}

/***************************************************************************/
t_pin_entree* t_sortie_get_pin(t_sortie* sortie)
{
	return sortie->pin;
}

/***************************************************************************/
int t_sortie_relier(t_sortie* dest, char* nom_composant, const t_pin_sortie* source)
{
	t_pin_entree_relier(dest->pin, nom_composant, source);

	//S'il n'y a aucune source, on retourne faux
	if (source == NULL)
		return FAUX;

	return VRAI;
}

/***************************************************************************/
int t_sortie_est_reliee(t_sortie* sortie)
{
	return t_pin_entree_est_reliee(sortie->pin);
}

/***************************************************************************/
void t_sortie_reset(t_sortie* sortie)
{
	t_pin_entree_reset(sortie->pin);
}

/***************************************************************************/
int t_sortie_get_valeur(const t_sortie* sortie)
{
	return t_pin_entree_get_valeur(sortie->pin);
}

/***************************************************************************/
int t_sortie_get_id(const t_sortie* sortie)
{
	return sortie->id;
}

/***************************************************************************/
char* t_sortie_get_nom(const t_sortie* sortie)
{
	return sortie->nom;
}

/***************************************************************************/
void t_sortie_serialiser(const t_sortie* sortie, char* resultat)
{
	sprintf(resultat, "%d %s\n", t_sortie_get_id(sortie), t_sortie_get_nom(sortie));
}

