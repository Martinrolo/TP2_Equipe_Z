/*
Module: T_PIN_SORTIE
Description: Définit le type t_pin_entree. Un t_pin_entree est un point de connexion appartenant
			 à un élément du circuit qui reçoit un signal (mais n'en émet pas).
			 Les éléments d'un circuit ayant un pin d'entrée de signal sont les portes (les entrées
			 des portes) ainsi que les sorties du circuit.

			 Si un pin d'entrée reçoit un signal, ce signal est stocké dans le champs valeur. Un
			 t_pin_entree qui est inactif (pas alimenté) a la valeur -1.

			 Un pin d'entree permet de relier le composant auquel il appartient à un autre composant.
			 Il doit être relié à un "pin de sortie" du composant auquel on souhaite se connecter.

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