/*
Module: circuit_IO
Description: Contients des fonctions faisant la sauvegarde et la charge de circuits
	dans des fichiers.
Auteurs: Martin Rolo Dussault, Antoine St-Amour, Maxim Dmitriev
*/
#define _CRT_SECURE_NO_WARNINGS
#include "circuit_IO.h"

#define NB_CHAR_TAMPON		30	//Nombre de caract�res par ligne qu'on va s�rialiser
#define NB_CHAR_COMPOSANT	2	//Nombre de caract�res par nom de composant
#define CONVERT_ASCII		48	//Nombre pour faire la conversion entre int et ASCII

static void ecrire_entrees(FILE*, int, t_circuit*);
static void ecrire_sorties(FILE*, int, t_circuit*);
static void ecrire_portes(FILE*, int, t_circuit*);
static void ecrire_liens(FILE*, t_circuit*);

static void lire_entrees(FILE*, int, t_circuit*);
static void lire_sorties(FILE*, int, t_circuit*);
static void lire_portes(FILE*, int, t_circuit*);
static void lire_liens(FILE*, t_circuit*);

/**********************************************************************************/
/*                     FONCTIONS PRIV�ES CIRCUIT_IO_SAUVEGARDER					  */
/**********************************************************************************/
static void ecrire_entrees(FILE* fichier, int nb_entrees, t_circuit* circuit)
{
	//Espace tampon pour texte
	char tampon[NB_CHAR_TAMPON];

	//Ajouter texte pour chaque entr�e
	for (int i = 0; i < nb_entrees; i++)
	{
		//CHANGER: mettre accesseurs
		t_entree_serialiser(circuit->entrees[i], tampon);
		fprintf(fichier, "%s", tampon);
	}
}

static void ecrire_sorties(FILE* fichier, int nb_sorties, t_circuit* circuit)
{
	//Espace tampon pour texte
	char tampon[NB_CHAR_TAMPON];

	//Ajouter texte pour chaque sortie
	for (int i = 0; i < nb_sorties; i++)
	{
		t_sortie_serialiser(circuit->sorties[i], tampon);
		fprintf(fichier, "%s", tampon);
	}
}

static void ecrire_portes(FILE* fichier, int nb_portes, t_circuit* circuit)
{
	//Espace tampon pour texte
	char tampon[NB_CHAR_TAMPON];

	//Ajouter texte pour chaque sortie
	for (int i = 0; i < nb_portes; i++)
	{
		t_porte_serialiser(circuit->portes[i], tampon);
		fprintf(fichier, "%s", tampon);
	}
}

static void ecrire_liens(FILE* fichier, t_circuit* circuit)
{
	//D'abord, on parcourt toutes les portes 
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte* porte = t_circuit_get_porte(circuit, i);

		//�crire nom porte
		fprintf(fichier, "%s ", t_porte_get_nom(porte));

		//�crire nom(s) de(s) liaison(s)
		for (int j = 0; j < t_porte_get_nb_entrees(porte); j++)
		{
			//Si le nom de la liaison est vide:
			if (strcmp(porte->entrees[j]->nom_liaison, "") == 0)
				fprintf(fichier, "%s ", "XX");

			//Sinon, on affiche le nom de la liaison
			else
			{
				fprintf(fichier, "%s ", porte->entrees[j]->nom_liaison);
				printf(porte->entrees[j]->nom_liaison);
			}
		}
		//Saut de ligne
		fprintf(fichier, "%c", '\n');
	}

	//�crire nom sorties
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie* sortie = t_circuit_get_sortie(circuit, i);

		//�crire nom sortie
		fprintf(fichier, "%s ", t_sortie_get_nom(sortie));

		//�crire nom liaison de la sortie
		fprintf(fichier, "%s ", sortie->pin->nom_liaison);

		//Saut de ligne
		fprintf(fichier, "%c", '\n');
	}
}

/**********************************************************************************/

void circuit_IO_sauvegarder(const char* nom_fichier, const t_circuit* circuit)
{
	//Ouvrir le fichier
	FILE* fsortie;
	fsortie = fopen(nom_fichier, "w");

	//get les nombre de composants
	int nb_entrees = t_circuit_get_nb_entrees(circuit);
	int nb_sorties = t_circuit_get_nb_sorties(circuit);
	int nb_portes = t_circuit_get_nb_portes(circuit);

	//afficher chaque nombre de composant
	fprintf(fsortie, "%d %d %d\n", nb_entrees, nb_sorties, nb_portes);

	//AJOUTER DES PRINTF � CHAQUE AJOUT DANS LE FICHIER
	//�crire les entr�es
	ecrire_entrees(fsortie, nb_entrees, circuit);

	//�crire les sorties
	ecrire_sorties(fsortie, nb_sorties, circuit);

	//�crire les portes
	ecrire_portes(fsortie, nb_portes, circuit);

	//�crire les liens
	ecrire_liens(fsortie, circuit);

	fclose(fsortie);
}













/**********************************************************************************/
/*                      FONCTIONS PRIV�ES CIRCUIT_IO_CHARGER					  */	
/**********************************************************************************/
static void lire_entrees(FILE* fichier, int nb_entrees, t_circuit* circuit)
{
	//Espace tampon pour le nom et variable pour l'ID
	char nom[NB_CHAR_TAMPON];
	int id = 0;

	//Faire la lecture de l'id et du nom et les mettre pour chaque entr�e
	for (int i = 0; i < nb_entrees; i++)
	{
		//Lire l'ID et le nom afin d'initialiser l'entr�e et l'ajouter au circuit
		fscanf(fichier, "%d%s\n", &id, nom);
		t_circuit_ajouter_entree(circuit, id, nom);
	}
}

/**********************************************************************************/
static void lire_sorties(FILE* fichier, int nb_sorties, t_circuit* circuit)
{
	//Espace tampon pour le nom et variable pour l'ID
	char nom[NB_CHAR_TAMPON];
	int id = 0;

	//Faire la lecture de l'id et du nom et les mettre pour chaque entr�e
	for (int i = 0; i < nb_sorties; i++)
	{
		//Lire l'ID et le nom afin d'initialiser l'entr�e et l'ajouter au circuit
		fscanf(fichier, "%d%s\n", &id, nom);
		t_circuit_ajouter_sortie(circuit, id, nom);
	}
}

/**********************************************************************************/
static void lire_portes(FILE* fichier, int nb_portes, t_circuit* circuit)
{
	//Espace tampon pour le nom et variable pour l'ID
	char nom[NB_CHAR_TAMPON];
	int id = 0;
	e_types_portes type;

	//Faire la lecture de l'id et du nom et les mettre pour chaque entr�e
	for (int i = 0; i < nb_portes; i++)
	{
		//Lire l'ID et le nom afin d'initialiser l'entr�e et l'ajouter au circuit
		fscanf(fichier, "%d%d%s\n", &id, &type, nom);
		t_circuit_ajouter_porte(circuit, type, id, nom);
	}
}

/**********************************************************************************/
static void lire_liens(FILE* fichier, t_circuit* circuit)
{
	//Lire les liaisons
	while (!feof(fichier))
	{
		int porte_nb_entrees;
		int porte_position;
		int sortie_position;
		int liaison_position;

		//composants source
		t_entree* entree;
		t_sortie* sortie;
		t_porte* porte;
		t_porte* porte_source;	//Dans le cas o� la porte-destination est li�e � une porte

		//Tableaux de caract�res contenant les noms de composants
		char nom_composant[NB_CHAR_COMPOSANT];	//Nom du composant

		char nom_liaison[NB_CHAR_COMPOSANT];	//Nom de la liaison

		//Lire nom de l'objet-destination
		fscanf(fichier, "%s", nom_composant);
		printf("%c", nom_composant[0]);
		printf("%c", nom_composant[1]);

		//Si l'objet est une porte
		if (nom_composant[0] == 'P')
		{
			//Le 2e caract�re �quivaut � la position de la porte
			porte_position = (int)nom_composant[1] - CONVERT_ASCII;

			//On va chercher la porte et son nombre d'entr�es
			porte = circuit->portes[porte_position];
			porte_nb_entrees = porte->nb_entrees;

			//Lire prochain nom(s) de liaison(s) dans le fichier, selon le nombre de pin d'entr�es
			for (int j = 0; j < porte_nb_entrees; j++)
			{
				//Lire le composant source de la liaison
				fscanf(fichier, "%s", nom_liaison);

				//Si c'est une entr�e, on va la chercher et prendre son pin de sortie
				if (nom_liaison[0] == 'E')
				{
					//on cherche la position de l'entr�e afin de la trouver
					liaison_position = nom_liaison[1] - CONVERT_ASCII;
					entree = circuit->entrees[liaison_position];

					//Chercher le pin de sortie de l'entr�e source selon la position
					t_pin_sortie* source = t_entree_get_pin(entree);

					//Faire la liaison
					t_porte_relier(porte, j, nom_liaison, source);
				}

				//Sinon, on va chercher la porte source et son pin de sortie
				else
				{
					//Chercher la position de la porte et la trouver dans le circuit
					liaison_position = nom_liaison[1] - CONVERT_ASCII;
					porte_source = circuit->portes[liaison_position];

					//Chercher le pin de sortie de l'entr�e source selon la position
					t_pin_sortie* source = t_porte_get_pin_sortie(porte);

					//Faire la liaison
					t_porte_relier(porte, j, nom_liaison, source);
				}
			}
		}

		//Sinon, l'objet-destinaion est une sortie
		else if (nom_composant[0] == 'S')
		{
			sortie_position = (int)nom_composant[1] - CONVERT_ASCII;
			sortie = circuit->sorties[sortie_position];

			//Chercher le composant source de la liaison
			fscanf(fichier, "%s", nom_liaison);
			liaison_position = (int)nom_liaison[1] - CONVERT_ASCII;
			porte_source = circuit->portes[liaison_position];


			//relier la sortie � la porte
			t_sortie_relier(sortie, nom_liaison, porte_source);
		}
	}
}


/**********************************************************************************/
void circuit_IO_charger(const char* chemin_acces, t_circuit* circuit)
{
	FILE* fentree = fopen(chemin_acces, "r");

	//si le fichier n'existe pas, on retourne faux
	if (fentree == NULL)
		return FAUX;

	//Variables des noms de composants
	int nb_entrees;
	int nb_sorties;
	int nb_portes;

	//Faire la lecture du nombre de composants
	fscanf(fentree, "%d", &nb_entrees);
	fscanf(fentree, "%d", &nb_sorties);
	fscanf(fentree, "%d", &nb_portes);

	//Lire les entr�es
	lire_entrees(fentree, nb_entrees, circuit);

	//Lire les sorties
	lire_sorties(fentree, nb_sorties, circuit);

	//Lire les portes
	lire_portes(fentree, nb_portes, circuit);

	//Lire les liens
	lire_liens(fentree, circuit);

	fclose(fentree);
}