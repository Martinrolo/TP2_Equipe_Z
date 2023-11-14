/*
Module: T_CIRCUIT
Description: Définit le type circuit et fournit les fonctions pour manipuler un circuit.
Auteur: Anis Boubaker
Dernière modification: Eric Thé, 2023-11-06
*/


#ifndef CIRCUIT_H_
#define CIRCUIT_H_


#define MAX_ENTREES 10			//Nombre maximal d'entrées que peut contenir le circuit
#define MAX_SORTIES 10			//Nombre maximal de sorties que peut contenir le circuit
#define CIRCUIT_MAX_PORTES 10	//Nombre maximal de portes que peut contenir le circuit

#include "t_entree.h"
#include "t_porte.h"
#include "t_sortie.h"


typedef struct t_entree t_entree; 
typedef struct t_porte t_porte;
typedef struct t_sortie t_sortie;
typedef enum e_types_portes e_types_portes;


/*
Définit le type t_circuit qui permet de stocker l'information relative à un circuit. 
*/
typedef struct t_circuit {
	//Tableau statique qui stocke des pointeurs vers les entrées incluses dans le circuit
	t_entree *entrees[MAX_ENTREES];
	
	//Tableau statique qui stocke des pointeurs vers les sorties incluses dans le circuit
	t_sortie *sorties[MAX_SORTIES];
	
	//Tableau statique qui stocke des pointeurs vers les portes incluses dans le circuit
	t_porte *portes[CIRCUIT_MAX_PORTES];

	int nb_entrees;    //Nombre d'entrées dans le tableau d'entrées du circuit
	int nb_sorties;    //Nombre de sorties dans le tableau de sorties du circuit
	int nb_portes;     //Nombre de portes dans le tableau de portes du circuit
} t_circuit;


/*
Fonction: T_CIRCUIT_INIT
Description: Crée un nouveau circuit vide. 

Paramètres: Aucun
Retour: Pointeur vers le circuit créé
Paramètres modifié: Aucun.
*/
t_circuit* t_circuit_init(void);

/*
Fonction: T_CIRCUIT_DESTROY
Description: Libère la mémoire occupée par le circuit et tous ses composants.

Paramètres: 
- circuit: Pointeur vers le circuit à détruire. 
Retour: Aucun.
Paramètres modifié: circuit
*/
void t_circuit_destroy(t_circuit *circuit);

/*
Fonction: T_CIRCUIT_AJOUTER_PORTE
Description: Crée une nouvelle porte et l'ajoute au circuit. 
NDE: Il faut s'assurer qu'on ne dépasse pas le nombre de portes permis (CIRCUIT_MAX_PORTES).

Paramètres:
- circuit: Pointeur vers le circuit auquel la porte sera ajoutée
- type: Type de la porte créée parmi les types de portes prédéfinis (e_type_porte, voir t_porte.h)
Retour: Pointeur vers la nouvelle porte créée s'il a été possible de la créer. NULL sinon.
*/
t_porte* t_circuit_ajouter_porte(t_circuit *circuit, e_types_portes le_type, int id, char *nom);

/*
Fonction: T_CIRCUIT_AJOUTER_ENTREE
Description: Crée une nouvelle entrée de circuit et l'ajoute au circuit.
NDE: Il faut s'assurer qu'on ne dépasse pas le nombre d'entrées permis (MAX_ENTREES).

Paramètres:
- circuit: Pointeur vers le circuit auquel l'entrée sera ajoutée
Retour: Pointeur vers l'entrée créée s'il a été possible de la créer. NULL sinon.
*/
t_entree* t_circuit_ajouter_entree(t_circuit * circuit, int id, char *nom);

/*
Fonction: T_CIRCUIT_AJOUTER_SORTIE
Description: Crée une nouvelle sortie de circuit et l'ajoute au circuit.
NDE: Il faut s'assurer qu'on ne dépasse pas le nombre d'sorties permis (MAX_ENTREES).

Paramètres:
- circuit: Pointeur vers le circuit auquel l'sortie sera ajoutée
Retour: Pointeur vers la sortie créée s'il a été possible de la créer. NULL sinon.
*/
t_sortie* t_circuit_ajouter_sortie(t_circuit * circuit, int id, char *nom);

/*
Fonction: T_CIRCUIT_EST_VALIDE
Description: Vérifie si un circuit donné est un circuit valide. Pour qu'un circuit soit valide
			 toutes les entrées, portes et sorties du circuit doivent être reliées. 
NDE: Vous utiliserez les fonctions t_entree_est_reliee, t_sortie_est_reliee et t_porte_est_reliee. 

Paramètres:
- circuit: Pointeur vers le circuit dont on veut vérifier la validité
Retour: (Booléen) Vrai si le circuit est valide, faux sinon.
*/
int t_circuit_est_valide(t_circuit *circuit);

/*
Fonction: T_CIRCUIT_APPLIQUER_SIGNAL
Description: Alimente le circuit avec le signal "signal" passé en paramètre. Le signal est un ensemble
		     de bits (entiers qui valent 0 ou 1) qui sont appliqués aux entrées du circuit. 
			 Les bits seront appliqués par ordre aux différentes entrées du circuit (le premier bit
			 du tableau à l'entrée 0 du circuit, le 2e bit à l'entrée 1, etc.)
NDE: 
- Vous devez vous assurer que le nombre de bits du signal est suffisant pour alimenter tout le circuit.
  (donc le nombre de bits doit être égal au nombre d'entrées du circuit)
- Pour appliquer un bit à une entrée, il faut changer la valeur du pin de sortie de l'entree 
  (champ pin dans un t_entree).

Paramètres:
- circuit: Pointeur vers le circuit auquel on souhaite appliquer le signal
- signal[]: Tableau de bits qui constituent le signal à appliquer au circuit
- nb_bits: Nombre de bits dans le tableau signal[]. 
Retour: (Booléen) Vrai si il a été possible d'appliquer le signal (i.e. assez de bits), faux sinon.
*/
int t_circuit_appliquer_signal(t_circuit * circuit, int signal[], int nb_bits);

/*
Fonction: T_CIRCUIT_RESET
Description: Réinitialise un circuit en "désalimentant" tous ses composants (entrées, sorties et portes)
			 Cette fonction fait appel aux fonctions de reset des diverses composants du circuit: 
			 t_entree_reset, t_sortie_reset et t_porte_reset.

Paramètres:
- circuit: Pointeur vers le circuit à réinitialiser.
Retour: Aucun.
*/
void t_circuit_reset(t_circuit *circuit);

/*
Fonction: T_CIRCUIT_PROPAGER_SIGNAL
Description: Propage le signal appliqué aux entrée du circuit à tous les composants. Le signal est propagé
			 de proche en proche: on part des entrées et on envoie leur signal aux pins auquelles elles sont
			 connectées. Si l'entrée est connectée à une porte, la porte calcule sa sortie puis envoie son 
			 signal au pin à lequel elle est connectée, etc. jusqu'à ce que toutes les sorties reçoivent un signal. 

			 Avant d'appeler cette fonction, on doit avoir préalablement appliqué un signal au circuit 
			 (fonction t_circuit_appliquer_signal). La propagation du signal ne sera faite que si le circuit est valide.
			 
			 La fonction retourne faux s'il a été impossible de propager un signal dans l'un des cas suivants:
			 - Le circuit est invalide (voir t_circuit_est_valide)
			 - Le circuit n'a pas été préalablement alimenté (voir t_circuit_appliquer_signal)
			 - En cas de présence de boucles dans le circuit
NDE: Pour propager le signal de proche en proche, vous utiliserez l'algorithme décrit dans l'énoncé qui utilise 
     une file de portes (module file_portes)

Paramètres:
- circuit: Pointeur vers le circuit à réinitialiser.
Retour: Booléen vrai si le signal s'est correctement propagé jusqu'aux sorties. Faux sinon. 
*/
int t_circuit_propager_signal(t_circuit *circuit);

/************************** Les ACCESSEURS ************************************/

/*
Fonction: T_CIRCUIT_GET_NB_PORTES
Description: Retourne le nombre de portes dans le circuit. 

Paramètres:
- circuit: Pointeur vers le circuit
Retour: Entier: le nombre de portes du circuit.
*/
int t_circuit_get_nb_portes(const t_circuit* circuit);

/*
Fonction: T_CIRCUIT_GET_PORTE
Description: Retourne une des portes dans le circuit.

Paramètres:
- circuit: Pointeur vers le circuit
- pos: la position de la porte désirée
Retour: Pointeur vers la porte désirée si "pos" est valide. NULL sinon.
*/
t_porte* t_circuit_get_porte(const t_circuit* circuit, int pos);

/*
Fonction: T_CIRCUIT_GET_NB_SORTIES
Description: Retourne le nombre de sorties dans le circuit.

Paramètres:
- circuit: Pointeur vers le circuit
Retour: Entier: le nombre de sorties du circuit.
*/
int t_circuit_get_nb_sorties(const t_circuit* circuit);

/*
Fonction: T_CIRCUIT_GET_SORTIE
Description: Retourne une des sorties dans le circuit.

Paramètres:
- circuit: Pointeur vers le circuit
- pos: la position de la sortie désirée
Retour: Pointeur vers la sortie désirée si "pos" est valide. NULL sinon.
*/
t_sortie* t_circuit_get_sortie(const t_circuit* circuit, int pos);

/*
Fonction: T_CIRCUIT_GET_NB_ENTREES
Description: Retourne le nombre d'entrées vers le circuit.

Paramètres:
- circuit: Pointeur vers le circuit
Retour: Entier: le nombre d'entrées du circuit.
*/
int t_circuit_get_nb_entrees(const t_circuit* circuit);

/*
Fonction: T_CIRCUIT_GET_ENTREE
Description: Retourne une des entrées vers le circuit.

Paramètres:
- circuit: Pointeur vers le circuit
- pos: la position de l'entrée désirée
Retour: Pointeur vers l'entrée désirée si "pos" est valide. NULL sinon.
*/
t_entree* t_circuit_get_entree(const t_circuit* circuit, int pos);

#endif