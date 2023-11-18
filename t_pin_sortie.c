/*
Module: T_PIN_SORTIE
Description: D�finit le type t_pin_entree. Un t_pin_entree est un point de connexion appartenant
			 � un �l�ment du circuit qui re�oit un signal (mais n'en �met pas).
			 Les �l�ments d'un circuit ayant un pin d'entr�e de signal sont les portes (les entr�es
			 des portes) ainsi que les sorties du circuit.

			 Si un pin d'entr�e re�oit un signal, ce signal est stock� dans le champs valeur. Un
			 t_pin_entree qui est inactif (pas aliment�) a la valeur -1.

			 Un pin d'entree permet de relier le composant auquel il appartient � un autre composant.
			 Il doit �tre reli� � un "pin de sortie" du composant auquel on souhaite se connecter.

Auteurs: Martin Rolo Dussault, Antoine St-Amour
*/

#include "t_pin_sortie.h"

/************************************************************/
t_pin_sortie* t_pin_sortie_init(void)
{
	t_pin_sortie* nouv_pin;

	nouv_pin = (t_pin_sortie*)malloc(sizeof(t_pin_sortie));

	//Ce pin contient aucune valeur et pas de liaison.
	nouv_pin->valeur = INACTIF;
	nouv_pin->nb_liaisons = NULL;
	nouv_pin->liaisons[0] = (t_pin_entree*)malloc(SORTIE_MAX_LIAISONS * sizeof(t_pin_entree));

	return nouv_pin;
}

/************************************************************/
void t_pin_sortie_destroy(t_pin_sortie* pin)
{
	free(pin->liaisons);
	free(pin);
}

/************************************************************/
int t_pin_sortie_get_valeur(t_pin_sortie* pin)
{
	return pin->valeur;
}

/************************************************************/
void t_pin_sortie_set_valeur(t_pin_sortie* pin, int valeur)
{
	if (valeur < INACTIF || valeur > 1) {
		//Valeur erron�e
		return;
	}
	pin->valeur = valeur;
}

/************************************************************/
int t_pin_sortie_ajouter_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{
	if (pin_sortie->nb_liaisons <= SORTIE_MAX_LIAISONS)
	{

		return VRAI;
	}
	
	return FAUX;
}