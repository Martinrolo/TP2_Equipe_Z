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
	free(pin->liaisons[0]);
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
		//Valeur erronée
		return;
	}

	pin->valeur = valeur;
}

/************************************************************/
int t_pin_sortie_ajouter_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{
	if (pin_sortie->nb_liaisons < SORTIE_MAX_LIAISONS)
	{
		//Ajouter le pointeur pin_entree au tableau liaisons
		pin_sortie->liaisons[pin_sortie->nb_liaisons] = pin_entree;
		pin_sortie->nb_liaisons++;

		return VRAI;
	}
	
	return FAUX;
}

/************************************************************/
void t_pin_sortie_supprimer_lien(t_pin_sortie* pin_sortie, const t_pin_entree* pin_entree)
{
	int i, j;
	
	for (i = 0; i < SORTIE_MAX_LIAISONS; i++)
	{
		//Si le lien existe, on l'enlève et on décale tous les autres liens suivants
		if (pin_sortie->liaisons[i] == pin_entree)
		{
			for (j = i; j < SORTIE_MAX_LIAISONS - 1; j++)
			{
				pin_sortie->liaisons[j] == pin_sortie->liaisons[j + 1];
			}

			pin_sortie->nb_liaisons--;
			break; //plus besoin de continuer, on a trouvé le lien
		}

	}
}

/************************************************************/
int t_pin_sortie_est_reliee(t_pin_sortie* pin)
{
	return pin->nb_liaisons != NULL;
}

/************************************************************/
int t_pin_sortie_propager_signal(t_pin_sortie* pin)
{
	int i;

	/*Propagation échouée si on a pas de liaison ou bien si
	la sortie est inactive*/
	if (pin->valeur == INACTIF || pin->nb_liaisons == 0)
		return FAUX;

	//Sinon, ça veut dire qu'on a au moins une liaison
	for (i = 0; i < pin->nb_liaisons; i++)
	{
		/*pour chaque pin d'entrée connecté à ce pin de sortie,
		on transmet la valeur du pin de sortie au pin d'entrée*/
		(pin->liaisons[i])->valeur = pin->valeur;
	}

	return VRAI;
}

/************************************************************/
void t_pin_sortie_reset(t_pin_sortie* pin)
{
	pin->valeur = INACTIF;
}