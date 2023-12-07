/*
TESTER LES ENTREES ET LES SORTIES
Auteur: Eric Thé, 13-11-2023

Programme qui teste l'utilisation des librairies de circuits logique "t_entree"
(avec "t_pin_sortie") et "t_sortie".  Plusieurs tests unitaires sont faits avec "assert()"
*/
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "t_entree.h"
#include "t_sortie.h"
#include "t_circuit.h"
#include "t_porte.h"
#include "circuit_IO.h"


void construire_circuit(t_circuit* circuit)
{  //variables locales pour les composantes du circuit
	t_porte* porte_ou;	//les 4 portes
	t_porte* porte_et;
	t_porte* porte_not;
	t_porte* porte_xor;
	t_entree* entree0;	//les 3 entrées
	t_entree* entree1;
	t_entree* entree2;
	t_sortie* sortie0;	//les 2 sorties
	t_sortie* sortie1;

	//Ajout des entrées
	entree0 = t_circuit_ajouter_entree(circuit, 0, "E0");
	entree1 = t_circuit_ajouter_entree(circuit, 1, "E1");
	entree2 = t_circuit_ajouter_entree(circuit, 2, "E2");
	//Ajout des sorties
	sortie0 = t_circuit_ajouter_sortie(circuit, 0, "S0");
	sortie1 = t_circuit_ajouter_sortie(circuit, 1, "S1");
	//Ajout des portes
	porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU, 0, "P0");
	porte_et = t_circuit_ajouter_porte(circuit, PORTE_ET, 1, "P1");
	porte_xor = t_circuit_ajouter_porte(circuit, PORTE_XOR, 2, "P2");
	porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT, 3, "P3");
	//Ajout des liens
	t_porte_relier(porte_ou, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));
	t_porte_relier(porte_ou, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 0, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 1, t_entree_get_nom(entree2), t_entree_get_pin(entree2));
	t_porte_relier(porte_not, 0, t_porte_get_nom(porte_ou), t_porte_get_pin_sortie(porte_ou));
	t_porte_relier(porte_xor, 0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_porte_relier(porte_xor, 1, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
	t_sortie_relier(sortie0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_sortie_relier(sortie1, t_porte_get_nom(porte_xor), t_porte_get_pin_sortie(porte_xor));
}


/*****************************************************************************************/
int main(void)
{
	int signal[MAX_ENTREES], 	 //les valeurs (0/1) pour les entrées du circuit
		i;
	t_circuit* circuit;   //le circuit complet
	circuit = t_circuit_init();   //Création du circuit
	construire_circuit(circuit);

	//Choisir mode de création du circuit
	int option;
	int erreur;

	printf("Veuillez choisir un mode de creation de circuit:\n");
	printf("1 - creation manuelle\n");
	printf("2 - a partir d'un fichier\n");
	do {
		scanf("%d", &option);
		if (erreur = (option != 1 && option != 2))
			printf("L'option n'est pas valide! Reessayez: ");
	} while (erreur);
	

	//Si l'option est 1,


	//Vérification de la validité du circuit
	if (t_circuit_est_valide(circuit)) {
		printf("Circuit valide!\n");
	}
	else {
		printf("Circuit invalide!\n");
	}

	//On définit un signal de 3 bits (eg. 111)
	for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++) {
		printf("Quel est la valeur du signal de l'entree %d (0 ou 1) ? ", i);
		scanf("%d", &signal[i]);		//assignation du signal d'entrée pour l'entrée #i
	}
	t_circuit_reset(circuit);
	t_circuit_appliquer_signal(circuit, signal, t_circuit_get_nb_entrees(circuit));

	if (t_circuit_propager_signal(circuit)) {
		printf("Signal propage avec succes.\n");

		for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++)
			printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit, i)));
	}
	else  printf("Erreur lors de la propagation du signal.\n");

	circuit_IO_sauvegarder("TEST.txt", circuit);

	t_circuit_destroy(circuit);
	system("pause");

	return EXIT_SUCCESS;
}