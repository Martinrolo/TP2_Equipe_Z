/*
Module: T_SORTIE
Description: Définit le type t_sortie (sortie de circuit) et fournit les
			 fonctions pour le manipuler.
Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2023-11-12
*/


#ifndef SORTIE_H_
#define SORTIE_H_

#include "t_pin_entree.h"

typedef struct t_pin_entree t_pin_entree;

#define NOM_SORTIE_TAILLE_MAX 3 	//Taille maximale du nom de la sortie

typedef struct t_sortie{
	int id;				//Identifiant numérique de la sortie de circuit.
						//Doit être unique parmi les sorties du circuit
	char *nom;			//Nom de la sortie (ex. "S1")
	t_pin_entree *pin;  //Pin de la sortie
} t_sortie;


/*
Fonction: T_SORTIE_INIT
Description: Crée une nouvelle sortie de circuit. Le constrcuteur reçoit un
			 identifiant numérique et un nom qui (on assume) sont uniques dans le circuit.
			 Ex. 1 et "S1"
		
Paramètres:
- id: Entier représentant l'identifiant numérique de la sortie (unique dans un circuit)
- nom: Chaine de caractères représentant le nom de l'entrée (unique dans un circuit)
Retour: Pointeur vers la sortie de circuit créée
Paramètres modifié: Aucun.
*/
t_sortie *t_sortie_init(int id, char *nom);

/*
Fonction: T_SORTIE_DESTROY
Description: Libère la mémoire occupée par la sortie et tous ses composants (i.e. le pin).
NDE: Ne pas oublier de premièrement détruire le pin_entrée de la sortie.

Paramètres:
- sortie: Pointeur vers la sortie à détruire.
Retour: Aucun.
*/
void t_sortie_destroy(t_sortie *sortie);

/*
Fonction: T_SORTIE_GET_PIN
Description: Accesseur - Retourne un pointeur vers le pin_entree de la sortie de circuit.

Paramètres:
- sortie: Pointeur vers la sortie de circuit dont on veut accéder au pin_entree.
Retour: Pointeur vers le pin_entree de la sortie de circuit.
*/
t_pin_entree *t_sortie_get_pin(t_sortie *sortie);


/*
Fonction: T_SORTIE_RELIER
Description: Relie une sortie de circuit à un autre composant du circuit (une entrée ou une porte)
			 On note ici qu'on relie le pin_entree de la sortie vers un pin_sortie
			 d'un autre composant. Les seuls autres composants disposant d'un pin_sortie sont
			 les entrées et les portes du circuit. 
			 Si la sortie a déjà été reliée, le nouveau lien va écraser l'ancien. 
NDE: Pour faire la liaison, la fonction t_pin_entree_relier() vous sera très utile!

Paramètres:
- dest: Pointeur vers la sortie de circuit à relier.
- nom_composant: Le nom du composant de circuit à lequel ont relie la sortie.
- source: Le pin_sortie vers lequel nous allons relier la sortie de circuit. 
Retour: Booléen : Vrai si la liaison a bien été effectuée. Faux sinon. 
*/
int t_sortie_relier(t_sortie *dest, char* nom_composant, const t_pin_sortie *source);

/*
Fonction: T_SORTIE_EST_RELIEE
Description: Vérifie si une sortie de circuit est reliée. Pour qu'elle soit reliée,
			 son pin_entree doit être relié.
NDE: Il existe une fonction dans t_pin_entree qui vous permet
	 de vérifier si un pin est relié. Utilisez-la!

Paramètres:
- sortie: Pointeur vers la sortie que l'on souhaite vérifier.
Retour: Booléen Vrai si la porte est entièrement reliée, Faux sinon.
*/
int t_sortie_est_reliee(t_sortie *sortie);

/*
Fonction: T_SORTIE_RESET
Description: Réinitialise une sortie. Pour réinitialiser une sortie, il suffit
de ré-initialiser son pin_entree.
NDE: Il y'a une fonction prête pour ça dans le module t_pin_entree.

Paramètres:
- sortie: Pointeur vers la sortie de circuit à réinitialiser.
Retour: Aucun
*/
void t_sortie_reset(t_sortie *sortie);

/*
Fonction: T_SORTIE_GET_VALEUR
Description: Retourne la valeur du signal de la sortie. Ceci correspond à la valeur
			 du signal de son pin_entree.
NDE: Il y'a une fonction prête pour ça dans le module t_pin_entree.

Paramètres:
- sortie: Pointeur vers la sortie de circuit dont on veut connaitre la valeur.
Retour: Entier: valeur du signal à la sortie
*/
int t_sortie_get_valeur(const t_sortie *sortie);

/*
Fonction: T_SORTIE_GET_ID
Description: Retourne le id (numéro) de la sortie.

Paramètres:
- sortie: Pointeur vers la sortie de circuit dont on veut connaitre son id
Retour: Entier: valeur de l'id de la sortie (son numéro).
*/
int t_sortie_get_id(const t_sortie* sortie);

/*
Fonction: T_SORTIE_GET_NOM
Description: Retourne le nom de la sortie.

Paramètres:
- sortie: Pointeur vers la sortie de circuit dont on veut connaitre son nom
Retour: String: valeur du nom de la sortie.
*/
char* t_sortie_get_nom(const t_sortie* sortie);

/*
Fonction: T_SORTIE_SERIALISER_LIENS
Description: Transforme en texte les informations d'une sortie.

Paramètres:
- sortie: Pointeur vers la sortie de circuit à sérialiser.
- resultat: Chaine de caractères dans laquelle on copie le texte généré.
*/
void t_sortie_serialiser(const t_sortie* sortie, char* resultat);   


#endif