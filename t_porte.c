/*
Module: T_PORTE
Description: Définit le type t_entree (Entrée de circuit) et fournit les
			 fonctions pour le manipuler.
Auteurs: Martin Rolo Dussault, Maxim Dmitriev & Antoine St-Amour
*/
#define _CRT_SECURE_NO_WARNINGS
#include "t_porte.h"

//FONCTION static définir nb_entrees
static void creer_entrees(e_types_portes type, t_porte* porte)
{
	if (type == PORTE_NOT)
	{
		porte->nb_entrees = 1;
		porte->entrees[0] = t_pin_entree_init();
	}

	else
	{
		porte->nb_entrees = MAX_ENTREES_PORTE;

		for (int i = 0; i < MAX_ENTREES_PORTE; i++)
			porte->entrees[i] = t_pin_entree_init();
	}
}

/********************************************************************/
t_porte* t_porte_init(int id, e_types_portes type, char* nom)
{
	//Créer la sortie (t_pin_sortie_init)
	t_porte* nouvelle_porte;

	nouvelle_porte = (t_porte*)malloc(sizeof(t_porte));

	//Assigner les valeurs des paramètres
	nouvelle_porte->id = id;
	nouvelle_porte->nom = _strdup(nom);
	nouvelle_porte->type = type;

	//Crées la/les entrées
	creer_entrees(type, nouvelle_porte);

	//Créer la sortie de la porte
	nouvelle_porte->sortie = t_pin_sortie_init();

	return nouvelle_porte;
}

/********************************************************************/
void t_porte_destroy(t_porte* porte)
{
	//Libérer le/les entrées et la sortie en 1er
	for (int i = 0; i < porte->nb_entrees; i++)
		t_pin_entree_destroy(porte->entrees[i]);
	t_pin_sortie_destroy(porte->sortie);

	//Libérer la porte elle-même
	free(porte->nom);
	free(porte);
}

/********************************************************************/
void t_porte_calculer_sorties(t_porte* porte)
{
	int val_entree0, val_entree1;
	int resultat;

	//Récupérer les valeurs aux entrées avec t_pin_entree_get_valeur()
	val_entree0 = t_pin_entree_get_valeur(porte->entrees[0]);
	if (porte->type != PORTE_NOT)
		val_entree1 = t_pin_entree_get_valeur(porte->entrees[1]);

	//	Attribuer la valeur de sortie selon le calcul du type, avec t_pin_sortie_set_valeur()
	switch (porte->type)
	{
	case PORTE_ET:
		resultat = (val_entree0 & val_entree1);
		break;

	case PORTE_OU:
		resultat = (val_entree0 | val_entree1);
		break;

	case PORTE_XOR:
		resultat = (val_entree0 ^ val_entree1);
		break;

	case PORTE_NOT:
		resultat = !val_entree0;
		break;
	}

	t_pin_sortie_set_valeur(porte->sortie, resultat);
}

/********************************************************************/
int t_porte_relier(t_porte* dest, int num_entree, char* nom_sortie, t_pin_sortie* source)
{
	//Valider "num_entree" reçu selon le nb_entrees de la porte
	if (num_entree > (dest->nb_entrees) - 1)
		return FAUX;

	//Si OK: On relie la source à l'entrée de l'indice num_entree avec t_pin_entree_relier
	t_pin_entree_relier(dest->entrees[num_entree], nom_sortie, source);
	return VRAI;
}

/********************************************************************/
int t_porte_est_reliee(t_porte* porte)
{
	//Vérifier le(s) entrée(s) avec t_pin_entree_est_reliee
	for (int i = 0; i < porte->nb_entrees; i++)
	{
		if (t_pin_entree_est_reliee(porte->entrees[i]) == FAUX)
			return FAUX;
	}

	//Vérifier la sortie avec t_pin_sortie_est_reliee
	if (t_pin_sortie_est_reliee(porte->sortie) == FAUX)
		return FAUX;

	//Si tout va bien jusqu'ici, notre porte est bien reliée.
	return VRAI;
}

/********************************************************************/
void t_porte_reset(t_porte* porte)
{
	//Mettre les entrées et sorties à INACTIF avec t_pin_entree_set_valeur et t_pin_sortie_set_valeur.
	for (int i = 0; i < porte->nb_entrees; i++)
	{
		t_pin_entree_set_valeur(porte->entrees[i], INACTIF);
	}

	t_pin_sortie_set_valeur(porte->sortie, INACTIF);
}

/********************************************************************/
int t_porte_propager_signal(t_porte* porte)
{
	//Si une des entrées est INACTIF, return 0
	for (int i = 0; i < porte->nb_entrees; i++)
	{
		if (t_pin_entree_get_valeur(porte->entrees[i]) == INACTIF)
			return FAUX;
	}

	//Sinon, on calcule la sortie et on propage le signal
	t_porte_calculer_sorties(porte);
	return t_pin_sortie_propager_signal(porte->sortie);
}

/********************************************************************/
int t_porte_get_id(const t_porte* porte)
{
	return porte->id;
}

/********************************************************************/
char* t_porte_get_nom(const t_porte* porte)
{
	return porte->nom;
}

/********************************************************************/
int t_porte_get_nb_entrees(const t_porte* porte)
{
	return porte->nb_entrees;
}

/********************************************************************/
e_types_portes t_porte_get_type(const t_porte* porte)
{
	return porte->type;
}

/********************************************************************/
t_pin_entree* t_porte_get_pin_entree(const t_porte* porte, int num)
{
	return porte->entrees[num];
}

/********************************************************************/
t_pin_sortie* t_porte_get_pin_sortie(const t_porte* porte)
{
	return porte->sortie;
}

/********************************************************************/
void t_porte_serialiser(const t_porte* porte, char* resultat)
{
	sprintf(resultat, "%d %d %s\n", t_porte_get_id(porte), t_porte_get_type(porte), t_porte_get_nom(porte));
}
