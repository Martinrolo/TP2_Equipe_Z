/*
Module: T_ENTREE
Description: Définit le type t_entree (Entrée de circuit) et fournit les 
			 fonctions pour le manipuler.
Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2023-11-12
*/

#ifndef ENTREE_H_
#define ENTREE_H_

#include "t_pin_sortie.h"


typedef struct t_pin_sortie t_pin_sortie;

typedef struct t_entree{
	int id;				//Identifiant numérique de l'entrée.
						//Doit être unique parmi les entrées du circuit
	char *nom;			//Nom de l'entrée (ex. "E1")
	t_pin_sortie *pin;  //Pin de sortie
} t_entree;


/*
Fonction: T_ENTREE_INIT
Description: Crée une nouvelle entrée de circuit. Le constrcuteur reçoit un 
			 identifiant numérique et un nom qui (on assume) sont uniques dans le circuit.
			 Ex. 1 et "E1"

Paramètres:
- id: Entier représentant l'identifiant numérique de l'entrée (unique dans un circuit)
- nom: Chaine de caractères représentant le nom de l'entrée (unique dans un circuit)
Retour: Pointeur vers l'entrée de circuit créée
Paramètres modifié: Aucun.
*/
t_entree *t_entree_init(int id, char *nom);

/*
Fonction: T_ENTREE_DESTROY
Description: Libère la mémoire occupée par l'entrée et tous ses composants (i.e. le pin).
NDE: Ne pas oublier de premièrement détruire le pin_sortie de l'entrée.

Paramètres:
- entree: Pointeur vers l'entrée à détruire.
Retour: Aucun.
*/
void t_entree_destroy(t_entree *entree);

/*
Fonction: T_ENTREE_GET_PIN
Description: Accesseur - Retourne un pointeur vers le t_pin_sortie de l'entrée

Paramètres:
- entree: Pointeur vers l'entrée de circuit dont on veut accéder au pin de sortie.
Retour: Pointeur vers le t_pin_sortie de l'entrée.
*/
t_pin_sortie *t_entree_get_pin(t_entree *entree);

/*
Fonction: T_ENTREE_EST_RELIEE
Description: Vérifie si une entrée de circuit est reliée. Pour qu'elle soit reliée,
			 son pin de sortie doit être relié.
NDE: Il existe une fonction dans t_pin_sortie qui vous permet
	 de vérifier si un pin est relié. Utilisez-la!

Paramètres:
- entree: Pointeur vers l'entrée que l'on souhaite vérifier.
Retour: Booléen Vrai si la porte est entièrement reliée, faux sinon.
*/
int t_entree_est_reliee(t_entree *entree);

/*
Fonction: T_ENTREE_RESET
Description: Réinitialise une entrée. Pour réinitialiser une entrée, il suffit
			 de ré-initialiser son pin_sortie.
NDE: Il y'a une fonction prête pour ça dans le module t_pin_sortie.

Paramètres:
- entree: Pointeur vers l'entrée de circuit à réinitialiser.
Retour: Aucun
*/
void t_entree_reset(t_entree *entree);

/*
Fonction: T_ENTREE_PROPAGER_SIGNAL
Description: Propage le signal à partir de l'entrée de circuit passée en paramètre.
			 Pour que le signal puisse se propager, il faut que le pin_sortie de
			 l'entrée ait une valeur valide (i.e. != -1).
NDE: Utilisez la fonction t_pin_sortie_propager_signal().

Paramètres:
- entree: Pointeur vers l'entrée de circuit dont on veut propager le signal.
Retour: Booléen: vrai si le signal a pu se propager (i.e. le pin_sortie a une
		valeur), Faux sinon.
*/
int t_entree_propager_signal(t_entree *entree);

/*
Fonction: T_ENTREE_GET_VALEUR
Description: Retourne la valeur du signal de l'entrée. Ceci correspond à la valeur
			 du signal de son pin_sortie.

Paramètres:
- entree: Pointeur vers l'entrée de circuit dont on veut connaitre la valeur.
Retour: Entier: valeur du signal à l'entrée du circuit. 
*/
int t_entree_get_valeur(const t_entree *entree);

/*
Fonction: T_ENTREE_GET_ID
Description: Retourne le id (numéro) de l'entrée.

Paramètres:
- entree: Pointeur vers l'entrée de circuit dont on veut connaitre son id
Retour: Entier: valeur de l'id de l'entrée (son numéro).
*/
int t_entree_get_id(const t_entree* entree);

/*
Fonction: T_ENTREE_GET_NOM
Description: Retourne le nom de l'entrée.

Paramètres:
- entree: Pointeur vers l'entrée de circuit dont on veut connaitre son nom
Retour: String: valeur du nom de l'entrée.
*/
char* t_entree_get_nom(const t_entree* entree);

/*
Fonction: T_ENTREE_SERIALISER_LIENS
Description: Transforme en texte les informations d'une entrée.

Paramètres:
- entree: Pointeur vers l'entrée de circuit à sérialiser.
- resultat: Chaine de caractères dans laquelle on copie le texte généré.
*/
void t_entree_serialiser(const t_entree* entree, char* resultat);     

#endif