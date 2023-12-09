/*PROGRAMME PRINCIPAL TP2: Les circuits combinatoires
Decription: Permet de créer des circuits contenant des entrées, sorties et portes logiques
	Dans ce programme principal, on demande à l'utilisateur comment il désire créer son circuit
	(soit manuellement ou bien par fichier
Auteurs: Martin Rolo Dussault, Maxim Dmitriev, Antoine St-Amour
*/

#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "t_entree.h"
#include "t_sortie.h"
#include "t_circuit.h"
#include "t_porte.h"
#include "circuit_IO.h"
#include "partie_bonus.h"
#include <math.h>

#define FICHIER				1	//Option de création de circuit avec fichier
#define MANUEL				2	//Option de création de circuit manuelle (exemple du prof)
#define MANUEL_PERSONNEL	3	//Option de création de circuit manuelle (notre circuit personnel)

//Fonction construire_circuit
//	Descripption: va construire le circuit d'exemple donné par le professeur
static void construire_circuit(t_circuit* circuit)
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

//Fonction construire_circuit_personnel
//	Descripption: va construire le circuit que nous avons conçu
/*****************************************************************************************/
static void construire_circuit_personnel(circuit)
{
	t_porte* porte_ou;	//les 3 portes
	t_porte* porte_et;
	t_porte* porte_not;
	t_entree* entree0;	//les 3 entrées
	t_entree* entree1;
	t_entree* entree2;
	t_sortie* sortie0;	//les 3 sorties
	t_sortie* sortie1;
	t_sortie* sortie2;

	//Ajout des entrées
	entree0 = t_circuit_ajouter_entree(circuit, 0, "E0");
	entree1 = t_circuit_ajouter_entree(circuit, 1, "E1");
	entree2 = t_circuit_ajouter_entree(circuit, 2, "E2");
	//Ajout des sorties
	sortie0 = t_circuit_ajouter_sortie(circuit, 0, "S0");
	sortie1 = t_circuit_ajouter_sortie(circuit, 1, "S1");
	sortie2 = t_circuit_ajouter_sortie(circuit, 2, "S2");
	//Ajout des portes
	porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU, 0, "P0");
	porte_et = t_circuit_ajouter_porte(circuit, PORTE_ET, 1, "P1");
	porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT, 2, "P2");

	//Ajout des liens
	t_porte_relier(porte_ou, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));
	t_porte_relier(porte_ou, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_not, 0, t_entree_get_nom(entree2), t_entree_get_pin(entree2));

	t_porte_relier(porte_et, 0, t_porte_get_nom(porte_ou), t_porte_get_pin_sortie(porte_ou));
	t_porte_relier(porte_et, 1, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));

	t_sortie_relier(sortie0, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
	t_sortie_relier(sortie1, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
	t_sortie_relier(sortie2, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
}


/*****************************************************************************************/
int main(void)
{
	int signal[MAX_ENTREES], 	 //les valeurs (0/1) pour les entrées du circuit
		i;
	t_circuit* circuit;   //le circuit complet
	circuit = t_circuit_init();   //Init le circuit SANS le construire

	//Demander à l'utilisateur le mode de création du circuit
	int option;
	int erreur;

	printf("Veuillez choisir un mode de creation de circuit:\n");
	printf("1 - a partir d'un fichier\n");
	printf("2 - creation manuelle (circuit du prof)\n");
	printf("3 - creation manuelle (notre circuit)\n");

	do {
		scanf("%d", &option);
		if (erreur = (option != MANUEL && option != FICHIER && option != MANUEL_PERSONNEL))
			printf("L'option n'est pas valide! Reessayez: ");
	} while (erreur);
	

	switch (option)
	{
		case FICHIER:
		{
			//Demander nom de fichier et vérifier s'il existe
			char nom_fichier[15];
			printf("Entrez le nom du fichier-texte source a lire: ");
			scanf("%s", nom_fichier);

			//Charger le circuit
			circuit_IO_charger(nom_fichier, circuit);

			//Afficher les composants qui ne sont PAS reliés
			int nb_entrees = t_circuit_get_nb_entrees(circuit);
			int nb_sorties = t_circuit_get_nb_sorties(circuit);
			int nb_portes = t_circuit_get_nb_portes(circuit);

			for (int i = 0; i < nb_entrees; i++)
			{
				t_entree* entree = t_circuit_get_entree(circuit, i);

				if (t_entree_est_reliee(entree) == 0)
					printf("L'entree %s n'est pas reliee!\n", t_entree_get_nom(entree));
			}

			for (int i = 0; i < nb_sorties; i++)
			{
				t_sortie* sortie = t_circuit_get_sortie(circuit, i);

				if (t_sortie_est_reliee(sortie) == 0)
					printf("La sortie %s n'est pas reliee!\n", t_sortie_get_nom(sortie));
			}

			for (int i = 0; i < nb_portes; i++)
			{
				t_porte* porte = t_circuit_get_porte(circuit, i);

				if (t_porte_est_reliee(porte) == 0)
					printf("La porte %s n'est pas reliee!\n", t_porte_get_nom(porte));
			}


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

			//SAUVEGARDER le circuit
			char* nom_fich[10];

			printf("Choisissez un nom de fichier ou vous voulez sauvegarder le circuit: ");
			scanf("%s", &nom_fich);

			circuit_IO_sauvegarder(nom_fich, circuit);
			printf("\nLe fichier [%s] a bien ete cree\n", nom_fich);

			break;
		}

		case MANUEL:
		{
			construire_circuit(circuit);	//On construit au préalable un exemple de circuit

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
				printf("\nSignal propage avec succes.\n");

				for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++)
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit, i)));
			}
			else  printf("\nErreur lors de la propagation du signal.\n");

			//SAUVEGARDER le circuit
			char* nom_fich[10];

			printf("\nChoisissez un nom de fichier ou vous voulez sauvegarder le circuit: ");
			scanf("%s", &nom_fich);

			circuit_IO_sauvegarder(nom_fich, circuit);
			printf("\nLe fichier [%s] a bien ete cree\n\n", nom_fich);

			break;
		}

		case MANUEL_PERSONNEL:
		{
			construire_circuit_personnel(circuit);	//On construit au préalable un exemple de circuit

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
				printf("\nSignal propage avec succes.\n");

				for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++)
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit, i)));
			}
			else  printf("\nErreur lors de la propagation du signal.\n");

			//SAUVEGARDER le circuit
			char* nom_fich[10];

			printf("\nChoisissez un nom de fichier ou vous voulez sauvegarder le circuit: ");
			scanf("%s", &nom_fich);

			circuit_IO_sauvegarder(nom_fich, circuit);
			printf("\nLe fichier [%s] a bien ete cree\n\n", nom_fich);

			break;
		}
	}

	//PARTIE BONUS
	int** matrice;
	matrice = t_circuit_tdv(circuit);

	printf("Table de verite:\n");
	int nb_entrees = t_circuit_get_nb_entrees(circuit);
	int nb_sorties = t_circuit_get_nb_sorties(circuit);

	//Afficher les noms de composants
	for (int i = 0; i < nb_entrees + nb_sorties; i++)
	{
		if (i < nb_entrees)
			printf("%s ", t_entree_get_nom(t_circuit_get_entree(circuit, i)));
		else
			printf("%s ", t_sortie_get_nom(t_circuit_get_sortie(circuit, i - nb_entrees)));
	}
	printf("\n");

	//Afficher la table
	for (int i = 0; i < pow(2, nb_entrees); i++)
	{
		for (int j = 0; j < nb_entrees + nb_sorties; j++)
		{
			printf("%d  ", matrice[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	//Supprimer la matrice et le circuit
	t_circuit_tdv_destroy(circuit, matrice);
	t_circuit_destroy(circuit);

	system("pause");

	return EXIT_SUCCESS;
}