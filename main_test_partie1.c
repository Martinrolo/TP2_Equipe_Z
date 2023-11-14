/*
TESTER LES ENTREES ET LES SORTIES
Auteur: Eric Thé, 13-11-2023

Programme qui teste l'utilisation des librairies de circuits logique "t_entree" 
(avec "t_pin_sortie") et "t_sortie".  Plusieurs tests unitaires sont faits avec "assert()"
*/
#include <assert.h>
#include "t_entree.h"
#include "t_sortie.h"

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
	system("pause");

	//libérer les 4 allocations
	t_entree_destroy(entree0);
	t_entree_destroy(entree1);
	t_sortie_destroy(sortie0);
	t_sortie_destroy(sortie1);
	return 0;
}