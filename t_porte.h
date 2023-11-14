/*
Module: T_PORTE
Description: Définit le type porte et fournit les fonctions pour manipuler une porte.
Note: Ce module a été conçu de sorte à ce qu'il soit facielement extensible pour traiter
      des portes peronnalisées (i.e. des circuits qu'on réutilise comme des portes dans 
	  d'autres circuits. Pour limiter le travail des étudiants, cette fonctionnalité a été
	  abandonnée mais il n'en demeure pas moins un point d'évolution potentiel du projet. 
      Les étudiants courageux sont encouragés à considérer, voir implémenter cette évolution.
Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2023-11-06
*/

#ifndef T_PORTE_H_
#define T_PORTE_H_

#include <string.h>
#include <stdio.h>
#include "t_pin_entree.h"
#include "t_pin_sortie.h"
#include "t_circuit.h"


typedef struct t_pin_entree t_pin_entree;
typedef struct t_pin_sortie t_pin_sortie;

#define MAX_ENTREES_PORTE  2    //Nombre maximales d'entrées pour une porte (AND, OR, XOR)
#define NOM_PORTE_TAILLE_MAX 3  //Taille maximale du nom d'une porte
								//en nombre de caractères

/*
Énumération: E_TYPES_PORTES
Description: Énumère les types de portes permis 
*/
typedef enum e_types_portes { PORTE_ET, PORTE_OU, PORTE_NOT, PORTE_XOR } e_types_portes;


/*
Définit le type t_porte qui permet de stocker l'information relative à une porte.
*/
typedef struct t_porte {
	int id;      //Identifiant numérique de la porte (doit être unique dans un circuit)

	char *nom;            //Nom de la porte construit à partir de l'identifiant (ex. "P1")

	e_types_portes type;  //Type énuméré de la porte (parmi les types énumérés)

	//Tableau statique de pointeurs vers des pins d’entrées. L'ensemble des pins d’entrées
	//représente les entrées de la porte.
	t_pin_entree *entrees[MAX_ENTREES_PORTE];

	t_pin_sortie *sortie;   //Pointeur vers le pin de sortie de la porte

	//Nombre d'entrées de la porte. Représente le nombre d'éléments effectifs
	//dans le tableau du champ "entrees[]"
	int nb_entrees;
} t_porte;



/*
Fonction: T_PORTE_INIT
Description: Crée une nouvelle porte du type spécifié en paramètre. Selon le type, la 
			 fonction initialise les pin_entrees nécessaires pour ce type de porte.

			 L'identifiant numérique ainsi que le nom reçu en paramètre doivent être unique 
			 dans le circuit. Ex. 1 et "P1"

Paramètres: 
- id: Entier représentant l'identifiant numérique de la porte (unique dans un circuit)
- type: Le type de porte à créer, selon la liste des types prédéfinis dans e_types_portes
- nom: Chaine de caractères représentant le nom de la porte (unique dans un circuit)
Retour: Pointeur vers la porte créée
Paramètres modifié: Aucun.
*/
t_porte *t_porte_init(int id, e_types_portes type, char *nom);

/*
Fonction: T_PORTE_DESTROY
Description: Libère la mémoire occupée par la porte et tous ses composants.
NDE: Ne pas oublier de détruire toutes les pin_entree et le pin_sortie appartenant à la porte.
Paramètres:
- porte: Pointeur vers la porte à détruire.
Retour: Aucun.
*/
void t_porte_destroy(t_porte *porte);

/*
Fonction: T_PORTE_CALCULER_SORTIES
Description: Calcule la valeur du pin de sortie de la porte, selon la valeur des pin_entree 
			 et le type de porte. Par exemple, si la porte est une porte ET, et que les deux
			 pin_entree de la porte ont une valeur de 1, la pin_sortie de la porte doit avoir
			 la valeur 1. 
NDE: 
- N'oubliez pas qu'il existe des opérateurs binaires en C. Utilisez-les!
- N'oubliez pas que, pour modifier la valeur d'un pin_sortie vous devez utiliser le
  mutateur correspondant (par exemple t_pin_sortie_set_valeur) et ne pas modifier la valeur
  du champ directement ici (car nous sommes à l'extérieur du module t_pin_sortie).
Paramètres:
- porte: Pointeur vers la porte dont on souhaite calculer la sortie  
		 (il n'existe qu'une seule sortie par porte).
Retour: Aucun.
*/
void t_porte_calculer_sorties(t_porte *porte);


/*
Fonction: T_PORTE_RELIER
Description: Relie une des entrées de la porte à un autre composant du circuit (une entrée ou une autre porte)
			 On note ici qu'on relie une des pin_entree de la porte vers une pin_sortie
			 d'un autre composant. Les seuls autres composants disposant de pin_sortie sont
			 les entrées du circuit et les autres portes. 

			 Si l'entrée de la porte en question a déjà été reliée, l'ancien lien est remplacé par le nouveau.
NDE: Pour faire la liaison, la fonction t_pin_entree_relier vous sera très utile!

Paramètres:
- porte: Pointeur vers la porte à relier.
- num_entree: l'indice de la pin_entree à relier dans le tableau des entrées. 
			  Si cet indice n'existe pas, la fonction retourne faux.  
- nom_sortie: Le nom du composant qui contient le pin de sortie à connecter.
- source: Le pin_sortie vers laquelle nous allons relier l'entrée de la porte. 
Retour: Booléen : Vrai si la liaison a bien été effectuée. Faux sinon. 
*/
int t_porte_relier(t_porte *dest, int num_entree, char* nom_sortie, const t_pin_sortie *source);

/*
Fonction: T_PORTE_EST_RELIEE
Description: Vérifie si une porte est entièrement reliée. Pour qu'elle soit entièrement
			 reliée, ses pin d'entrées et son pin de sortie doivent tous être reliées.
NDE: Il existe des fonctions dans t_pin_entree et t_pin_sortie qui vous permettent
     de vérifier si une pin est reliée. Utilisez-les!

Paramètres:
- porte: Pointeur vers la porte que l'on souhaite vérifier.
Retour: Booléen Vrai si la porte est entièrement reliée, faux sinon.
*/
int t_porte_est_reliee(t_porte *porte);

/*
Fonction: T_PORTE_RESET
Description: Réinitialise une porte. Pour réinitialiser une porte, il suffit
			 de ré-initialiser chacuns de ses pins (à INACTIF). 
NDE: Encore ici, il y'a des fonctions prêtes dans les modules t_pin_entree
	 et t_pin_sortie pour ré-initialiser tous les pins.

Paramètres:
- porte: Pointeur vers la porte à réinitialiser.
Retour: Aucun
*/
void t_porte_reset(t_porte *porte);

/*
Fonction: T_PORTE_PROPAGER_SIGNAL
Description: Propage le signal à partir de la porte passée en paramètre.
			 Pour que le signal puisse se propager, il faut que la porte
			 ait une valeur valide sur chacune de ses entrées (i.e. != -1).
			 Si c'est le cas, il suffit de calculer la sortie, puis de propager
			 le signal à partir du pin_sortie de la porte.
NDE: Une fois que vous avez calculé la valeur du pin de sortie,  
	 utilisez la fonction t_pin_sortie_propager_signal.

Paramètres:
- porte: Pointeur vers la porte dont on veut propager le signal.
Retour: Booléen: vrai si le signal a pu se propager (i.e. toutes les entrées ont
		réçu un signal, Faux sinon.
*/
int t_porte_propager_signal(t_porte *porte);

/************************** Les ACCESSEURS ************************************/

/*
Fonction: T_PORTE_GET_ID
Description: Retourne le id (numéro) de la porte.

Paramètres:
- porte: Pointeur vers la porte de circuit dont on veut connaitre son id
Retour: Entier: valeur de l'id de la porte (son numéro).
*/
int t_porte_get_id(const t_porte* porte);

/*
Fonction: T_PORTE_GET_NOM
Description: Retourne le nom de la porte.

Paramètres:
- porte: Pointeur vers la porte de circuit dont on veut connaitre son nom
Retour: String: valeur du nom de la porte.
*/
char * t_porte_get_nom(const t_porte* porte);

/*
Fonction: T_PORTE_GET_NB_ENTREES
Description: Retourne le nombre d'entrées de la porte (soit 1 ou 2).

Paramètres:
- porte: Pointeur vers la porte de circuit dont on veut connaitre son nb. d'entrées
Retour: Entier: valeur du nombre d'entrées de la porte.
*/
int t_porte_get_nb_entrees(const t_porte* porte);

/*
Fonction: T_PORTE_GET_TYPE
Description: Retourne le type logique de la porte.

Paramètres:
- porte: Pointeur vers la porte de circuit dont on veut connaitre son type
Retour: (e_types_portes) valeur du type logique de la porte.
*/
e_types_portes t_porte_get_type(const t_porte* porte);

/*
Fonction: T_PORTE_GET_PIN_ENTREE
Description: Accesseur - Retourne un pointeur vers un des t_pin_entree de la porte.

Paramètres:
- porte: Pointeur vers la porte de circuit dont on veut accéder à un de ses pins de sortie.
- num: Position de l'entrée désirée (soit 0 ou 1).
Retour: Pointeur vers le t_pin_sortie désiré de la porte.
*/
t_pin_entree* t_porte_get_pin_entree(const t_porte* porte, int num);

/*
Fonction: T_PORTE_GET_PIN_SORTIE
Description: Accesseur - Retourne un pointeur vers le t_pin_sortie de la porte.

Paramètres:
- porte: Pointeur vers la porte de circuit dont on veut accéder au pin de sortie.
Retour: Pointeur vers le t_pin_sortie de la porte.
*/
t_pin_sortie* t_porte_get_pin_sortie(const t_porte* porte);

/*
Fonction: T_PORTE_SERIALISER
Description: Transforme en texte les informations d'une porte.

Paramètres:
- porte: Pointeur vers la porte de circuit à sérialiser.
- resultat: Chaine de caractères dans laquelle on copie le texte généré.
*/
void t_porte_serialiser(const t_porte* porte, char* resultat);

#endif