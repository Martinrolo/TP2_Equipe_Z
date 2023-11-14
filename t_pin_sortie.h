/*
Module: T_PIN_SORTIE
Description: Définit le type t_pin_sortie. Un t_pin_sortie est un point de connexion appartenant
			 à un élément du circuit qui émet un signal (mais n'en reçoit pas).
			 Les éléments d'un circuit ayant une pin sortie sont les portes (les sorties des portes) 
			 ainsi que les entrées du circuit.

			 Pour qu'un pin de sortie émette un signal, ce signal doit être stocké dans le champs valeur. 
			 Un t_pin_sortie qui est inactif (pas alimentée) aura la valeur -1.

			 Un pin de sortie permet de relier le composant auquel il appartient à d'autres composants.
			 Il doit être reliée à des "pin d'entrée" des composants auquel on souhaite se connecter.

			 Note: Contrairement à un pin d'entrée, un pin de sortie peut être reliée à plusieurs 
			 pins d'entrées : Ceci permet d'émettre le même signal à plusieurs composants.

Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2023-11-12
*/

#ifndef T_PIN_SORTIE_H_
#define T_PIN_SORTIE_H_

#include "t_pin_entree.h"

//Le nombre maximal de pins d'entrées auquels une sortie peut être connectée
#define SORTIE_MAX_LIAISONS 10

typedef struct t_pin_entree t_pin_entree;
typedef struct t_circuit t_circuit;


//Définit le type t_pin_sortie
typedef struct t_pin_sortie {
	int valeur;		//Valeur du signal reçu par le pin d'entrée. -1 si le pin est inactif.

	//Tableau de pointeurs vers les pins d'entrées auquel ce pin sortie est connecté
	t_pin_entree *liaisons[SORTIE_MAX_LIAISONS];

	//Nombre de pins d'entrées vers lesquels ce pin de sortie est connecté.
	//Ce champ représente le nombre d'éléments effectifs du tableau "liaisons[]".
	int nb_liaisons;
} t_pin_sortie;


/*
Fonction: T_PIN_SORTIE_INIT (constructeur)
Description: Crée un nouveau pin de sortie qui contient aucune valeur et aucune liaison.

Paramètres: Aucun
Retour: Pointeur vers le pin de sortie qui a été créée
Paramètres modifié: N/A.
*/
t_pin_sortie *t_pin_sortie_init(void);

/*
Fonction: T_PIN_SORTIE_DESTROY (Destructeur)
Description: Libère la mémoire occupée par le pin de sortie.

Paramètres:
- pin: Pointeur vers le pin de sortie à détruire.
Retour: Aucun.
Paramètres modifié: pin
*/
void t_pin_sortie_destroy(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_GET_VALEUR (Accesseur)
Description: Accesseur du champs valeur.

Paramètres:
- pin: Pointeur vers le pin de sortie.
Retour: (entier) Valeur du pin : 0, 1 ou -1.
Paramètres modifié: aucun
*/
int t_pin_sortie_get_valeur(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_SET_VALEUR (Mutateur)
Description: Mutateur du champs valeur.

Paramètres:
- pin: Pointeur vers le pin de sortie.
- valeur: nouvelle valeur du pin de sortie 
          (doit obligatoirement être -1, 0 ou 1, sinon aucun changement)
Retour: Aucun
Paramètres modifié: pin
*/
void t_pin_sortie_set_valeur(t_pin_sortie *pin, int valeur);

/*
Fonction: T_PIN_SORTIE_AJOUTER_LIEN
Description: Relie le pin de sortie à un pin d'entrée. Cette fonction permet de relier le composant, 
			 auquel apparatien le pin de sortie, à un autre composant, auquel appartient le pin d'entrée.

			 La fonction doit vérifier qu'on excède pas le nombre maximal de liens autorisés 
			 (SORTIE_MAX_LIAISONS)

Paramètres:
- pin_sortie: le pin de sortie à relier
- pin_entree: Le pin d'entrée à laquel le pin de sortie sera relié.
Retour: Vrai si le lien a bien été ajouté, faux sinon.
*/
int t_pin_sortie_ajouter_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree);

/*
Fonction: T_PIN_SORTIE_SUPPRIMER_LIEN
Description: Supprime un lien existant entre le pin de sortie et un pin d'entree reçu en paramètre.
			 Si il n'existe aucun lien entre ces deux pins, la fonction n'aura aucun effet.
			 Si ce lien a été retrouvé, on le supprime en le remplaçant par le lien suivant dans la
			 liste des liens. On décale toutes les liaisons suivantes vers la gauche également.

Paramètres:
- pin_sortie: le pin de sortie dont on veut supprimer le lien
- pin_entree: Le pin d'entrée vers laquelle le pin de sortie est lié.
Retour: Aucun
*/
void t_pin_sortie_supprimer_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree);


/*
Fonction: T_PIN_SORTIE_EST_RELIEE
Description: Permet de vérifier si un pin de sortie est relié à au moins un pin d'entrée.

Paramètres:
- pin_sortie: le pin de sortie dont on veut vérifier la liaison
Retour: Booléen: Vrai si le pin de sortie est reliée, Faux sinon.
*/
int t_pin_sortie_est_reliee(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_PROPAGER_SIGNAL
Description: Fonction qui propage le signal du pin de sortie vers toutes les pins d'entrées 
			 avec lesquels il est relié.

			 Le pin ne doit pas être inactif (valeur == -1) et le nombre de liaisons doit être
			 non-zéro pour que le signal puisse se propager.

Paramètres:
- pin_sortie: le pin de sortie dont on veut propager le signal
Retour: (Booléen) Vrai si le signal s'est bien propagé, faux sinon. Le signal ne peut se propager
	    si le pin est inactif ou si il n'est relié à aucun pin d'entrée.
*/
int t_pin_sortie_propager_signal(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_RESET
Description: Ré-initialise la valeur du pin de sortie à INACTIF

Parametre:
- pin_entree: Le pin d'entrée dont on veut réinitialiser la valeur
Retour: Aucun.
*/
void t_pin_sortie_reset(t_pin_sortie *pin);

#endif