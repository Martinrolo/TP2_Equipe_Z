/*
Module: T_PIN_ENTREE
Description: Définit le type t_pin_entree. Un t_pin_entree est un point de connexion appartenant 
		     à un élément du circuit qui reçoit un signal (mais n'en émet pas). 
			 Les éléments d'un circuit ayant un pin d'entrée de signal sont les portes (les entrées
			 des portes) ainsi que les sorties du circuit.

			 Si un pin d'entrée reçoit un signal, ce signal est stocké dans le champs valeur. Un 
			 t_pin_entree qui est inactif (pas alimenté) a la valeur -1. 

			 Un pin d'entree permet de relier le composant auquel il appartient à un autre composant. 
			 Il doit être relié à un "pin de sortie" du composant auquel on souhaite se connecter.

Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2023-11-12
*/

#ifndef T_PIN_ENTREE_H_
#define T_PIN_ENTREE_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t_pin_sortie.h"

#define NOM_ENTREE_TAILLE_MAX 3  	//Taille maximale du nom de l'entrée
#define INACTIF    -1				//Indique qu'un composant (entree/sortie) est inactif

typedef struct t_pin_sortie t_pin_sortie;

//Définit le type t_pin_entree
typedef struct t_pin_entree {
	int valeur;		//Valeur du signal reçu par le pin d'entree. -1 si le pin est inactif.
	char *nom_liaison;      //le nom de la liaison vers le pin de sortie
	t_pin_sortie *liaison;	//Pointeur vers le pin de sortie
							//à laquelle ce pin est connecté
} t_pin_entree;


/*
Fonction: T_PIN_ENTREE_INIT (constructeur)
Description: Crée un nouveau pin entrée qui contient aucune valeur et pas de liaison.

Paramètres: Aucun
Retour: Pointeur vers le pin d'entrée qui a été créée
Paramètres modifié: N/A.
*/
t_pin_entree *t_pin_entree_init();

/*
Fonction: T_PIN_ENTREE_DESTROY (Destructeur)
Description: Libère la mémoire occupée par le pin d'entree.

Paramètres:
- pin: Pointeur vers le pin d'entrée à détruire.
Retour: Aucun.
Paramètres modifié: pin
*/
void t_pin_entree_destroy(t_pin_entree *pin);

/*
Fonction: T_PIN_ENTREE_GET_VALEUR (Accesseur)
Description: Accesseur du champs valeur.

Paramètres:
- pin: Pointeur vers le pin d'entrée.
Retour: (entier) Valeur du pin : 0, 1 ou -1.
Paramètres modifié: aucun
*/
int t_pin_entree_get_valeur(const t_pin_entree *pin);

/*
Fonction: T_PIN_ENTREE_GET_LIEN (Accesseur)
Description: Accesseur du champs liaison.

Paramètres:
- pin: Pointeur vers le pin d'entrée.
Retour: (char *) le nom de la liaison de sortie.
Paramètres modifié: aucun
*/
char * t_pin_entree_get_lien(const t_pin_entree* pin);

/*
Fonction: T_PIN_ENTREE_SET_VALEUR (Mutateur)
Description: Mutateur du champs valeur.

Paramètres:
- pin: Pointeur vers le pin d'entrée.
- valeur: nouvelle valeur du pin d'entrée (doit obligatoirement être -1, 0 ou 1)
Retour: Aucun
Paramètres modifié: pin
*/
void t_pin_entree_set_valeur(t_pin_entree *pin, int valeur);

/*
Fonction: T_PIN_ENTREE_RELIER
Description: Relie le pin d'entrée à un pin de sortie. Cette fonction permet de relier le composant, auquel 
			 apparatien le pin d'entrée, à un autre composant, auquel appartient le pin de sortie.

			 Cette fonction s'assure que la relation est bi-directionnelle: le pin de sortie aura le pin d'entrée
			 comme un des pins auxquels il est relié (fait en utilisant la fontion t_pin_sortie_ajouter_lien)

Paramètres:
- pin_entree: le pin d'entrée à relier
- pin_sortie: Le pin de sortie à lequel le pin d'entrée sera relié.
Retour: Aucun
*/
void t_pin_entree_relier(t_pin_entree *pin_entree, char * nom_sortie, const t_pin_sortie *pin_sortie);


/*
Fonction: T_PIN_ENTREE_EST_RELIEE
Description: Permet de vérifier si un pin d'entrée est reliée à un pin de sortie.

Paramètres:
- pin_entree: le pin d'entrée dont on veut vérifier la liaison
Retour: Booléen: Vrai si le pin d'entrée est reliée, Faux sinon.
*/
int t_pin_entree_est_reliee(t_pin_entree *pin);

/*
Fonction: T_PIN_ENTREE_RESET
Description: Ré-initialise la valeur du pin d'entree à INACTIF

Parametre: 
- pin_entree: le pin d'entrée dont on veut réinitialiser la valeur
Retour: Aucun.
*/
void t_pin_entree_reset(t_pin_entree *pin);


#endif