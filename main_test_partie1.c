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


int main(void)
{
	//déclaration de variables
	t_entree* entree0;     //les 2 entrées
	t_entree* entree1;
	t_sortie* sortie0;     //les 2 sorties
	t_sortie* sortie1;
	t_pin_sortie* pin;     //pointeur vers un des pins de sortie (de E0 ou E1)
	t_pin_entree* pin_in;  //pointeur vers un des pins d'entrée (de S0 ou S1)

	//Créer tous les éléments dynamiques
	entree0 = t_entree_init(0, "E0");
	entree1 = t_entree_init(1, "E1");
	sortie0 = t_sortie_init(0, "S0");
	sortie1 = t_sortie_init(1, "S1");


	t_porte* porte_ou;	//les 4 portes
	porte_ou = t_porte_init(4, PORTE_NOT, "P0");

	char* resultat[20];
	t_entree_serialiser(entree0, resultat);
	printf("%s", resultat);

	char* resultat2[20];
	t_entree_serialiser(sortie0, resultat2);
	printf("%s", resultat2);

	char* resultat3[20];
	t_porte_serialiser(porte_ou, resultat3);
	printf("%s", resultat3);




	//on teste si les entrées/sorties sont reliées
	if (t_entree_est_reliee(entree0) == 0)
		printf("L'entree %s n'est pas reliee!\n", t_entree_get_nom(entree0));

	if (t_entree_est_reliee(entree1) == 0)
		printf("L'entree %s n'est pas reliee!\n", t_entree_get_nom(entree1));

	if (t_sortie_est_reliee(sortie0) == 0)
		printf("La sortie %s n'est pas reliee!\n", t_sortie_get_nom(sortie0));

	if (t_sortie_est_reliee(sortie1) == 0)
		printf("La sortie %s n'est pas reliee!\n", t_sortie_get_nom(sortie1));

	//on récupère une référence sur le pin de sortie de entree0
	pin = t_entree_get_pin(entree0);

	//on connecte entree0 à la sortie0
	t_sortie_relier(sortie0, t_entree_get_nom(entree0), pin);
	assert(t_entree_est_reliee(entree0) == 1);		//test unitaire rapide avec assert()
	assert(t_sortie_est_reliee(sortie0) == 1);		//test unitaire rapide avec assert()

	pin_in = t_sortie_get_pin(sortie0);
	printf("\nLa sortie %s est connectee a l'entree %s\n", t_sortie_get_nom(sortie0),
		t_pin_entree_get_lien(pin_in));

	//on connecte entree0 à la sortie1
	t_sortie_relier(sortie1, t_entree_get_nom(entree0), pin);
	assert(t_sortie_est_reliee(sortie1) == 1);		//test unitaire rapide avec assert()

	pin_in = t_sortie_get_pin(sortie1);
	printf("\nLa sortie %s est connectee a l'entree %s\n", t_sortie_get_nom(sortie1),
		t_pin_entree_get_lien(pin_in));

	//mettre le signal à 1 dans le pin de entree0 et propager le signal
	t_pin_sortie_set_valeur(pin, 1);
	t_entree_propager_signal(entree0);

	//TEST 1: on confirme la réception du signal (1) dans les deux sorties
	printf("\nTEST 1: %s (%d) -> %s et %s\n", t_entree_get_nom(entree0), t_entree_get_valeur(entree0),
		t_sortie_get_nom(sortie0), t_sortie_get_nom(sortie1));

	printf("Sortie %d = %d\n", t_sortie_get_id(sortie0), t_sortie_get_valeur(sortie0));
	printf("Sortie %d = %d\n", t_sortie_get_id(sortie1), t_sortie_get_valeur(sortie1));

	//on efface les valeurs des deux sorties
	t_sortie_reset(sortie0);
	assert(t_sortie_get_valeur(sortie0) == INACTIF);   //test unitaire rapide avec assert()

	t_sortie_reset(sortie0);
	assert(t_sortie_get_valeur(sortie0) == INACTIF);   //test unitaire rapide avec assert()

	//on récupère une référence sur le pin de sortie de entree1
	pin = t_entree_get_pin(entree1);

	//on connecte entree1 à la sortie1
	t_sortie_relier(sortie1, t_entree_get_nom(entree1), pin);
	assert(t_entree_est_reliee(entree1) == 1);		//test unitaire rapide avec assert()
	assert(t_sortie_est_reliee(sortie1) == 1);		//test unitaire rapide avec assert()

	pin_in = t_sortie_get_pin(sortie1);
	printf("\nLa sortie %s est connectee a l'entree %s\n", t_sortie_get_nom(sortie1),
		t_pin_entree_get_lien(pin_in));

	//mettre le signal à 1 dans le pin de entree1 et propager le signal
	t_pin_sortie_set_valeur(pin, 1);
	t_entree_propager_signal(entree1);

	//mettre le signal à -1 dans le pin de sortie de entree0
	t_entree_reset(entree0);
	assert(t_entree_get_valeur(entree0) == INACTIF);    //test unitaire rapide avec assert()

	//mettre le signal à 0 dans le pin de entree0 et propager le signal
	pin = t_entree_get_pin(entree0);
	t_pin_sortie_set_valeur(pin, 0);
	t_entree_propager_signal(entree0);

	//TEST 2: on confirme la réception du signal (1) dans S0 et (0) dans S1
	printf("\nTEST 2: %s (%d) -> %s, %s (%d) -> %s\n", t_entree_get_nom(entree0), t_entree_get_valeur(entree0),
		t_sortie_get_nom(sortie0),
		t_entree_get_nom(entree1), t_entree_get_valeur(entree1),
		t_sortie_get_nom(sortie1));

	printf("Sortie %d = %d\n", t_sortie_get_id(sortie0), t_sortie_get_valeur(sortie0));
	printf("Sortie %d = %d\n", t_sortie_get_id(sortie1), t_sortie_get_valeur(sortie1));

	//libérer les 4 allocations
	
	//t_entree_destroy(entree0);
	//t_entree_destroy(entree1);
	//t_sortie_destroy(sortie0);
	//t_sortie_destroy(sortie1);
	//system("pause");

	/***************************************************/

	//déclaration des variables
	int signal[3];		//les 3 valeurs pour les 3 entrées
	t_circuit* circuit;   //le circuit complet
	circuit = t_circuit_init();   //Création du circuit
	construire_circuit(circuit);

	//Vérification de la validité du circuit
	if (t_circuit_est_valide(circuit)) {
		printf("Circuit valide!\n");
	}
	else {
		printf("Circuit invalide!\n");
	}

	//On définit un signal de 3 bits (111)
	signal[0] = 1;
	signal[1] = 1;
	signal[2] = 1;
	t_circuit_reset(circuit);
	t_circuit_appliquer_signal(circuit, signal, 3);

	if (t_circuit_propager_signal(circuit)) {
		printf("Signal propage avec succes.\n");
		printf("Sortie 0: %d\n", t_sortie_get_valeur(sortie0));
		printf("Sortie 1: %d\n", t_sortie_get_valeur(sortie1));
	}
	else  printf("Erreur lors de la propagation du signal.\n");

	//TEST circuit_io_sauvegarder
	char* nom_fich = "test.txt";
	circuit_IO_sauvegarder(nom_fich, circuit);


	/*
	//TEST créer circuit
	t_circuit* circuit2 = t_circuit_init();
	circuit_IO_charger(nom_fich, circuit2);

	//TEST sauvegarder nouveau circuit dans nouveau fichier
	char* nom_fich2 = "test2.txt";
	circuit_IO_sauvegarder(nom_fich2, circuit2);

	t_circuit_destroy(circuit);
	t_circuit_destroy(circuit2);
	//system("pause");


	return EXIT_SUCCESS;
}