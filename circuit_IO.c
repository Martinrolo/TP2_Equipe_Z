/*
Module: circuit_IO
Description: Contients des fonctions faisant la sauvegarde et la charge de circuits
	dans des fichiers.
Auteurs: Martin Rolo Dussault, Antoine St-Amour, Maxim Dmitriev
*/
#define _CRT_SECURE_NO_WARNINGS
#include "circuit_IO.h"

#define NB_CHAR_TAMPON		80	//Nombre de caractères tampon pour générer des strings
#define NB_CHAR_COMPOSANT	2	//Nombre de caractères par nom de composant
#define CONVERT_ASCII		48	//Nombre pour faire la conversion entre int et ASCII

void circuit_IO_sauvegarder(const char* nom_fichier, const t_circuit* circuit)
{
	//Ouvrir le fichier
	FILE* fsortie;
	fsortie = fopen(nom_fichier, "w");

	//Espace tampon pour strings
	char tampon[NB_CHAR_TAMPON];

	if (fsortie == NULL)
	{
		printf("Erreur à l'ouverture du fichier!");
		return FAUX;
	}

	//afficher chaque nombre de composant
	fprintf(fsortie, "%d ", circuit->nb_entrees);
	fprintf(fsortie, "%d ", circuit->nb_sorties);
	fprintf(fsortie, "%d\n", circuit->nb_portes);

	//Ajouter texte pour chaque entrée
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_serialiser(circuit->entrees[i], tampon);
		fprintf(fsortie, "%s", tampon);
	}

	//Ajouter texte pour chaque sortie
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_serialiser(circuit->sorties[i], tampon);
		fprintf(fsortie, "%s", tampon);
	}

	//Ajouter texte pour chaque porte
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_serialiser(circuit->portes[i], tampon);
		fprintf(fsortie, "%s", tampon);
	}

	
	//
	//Sérialiser les liaisons
	//
	//D'abord, on parcourt toutes les portes 
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		int position_liaisons = 0;	//Position sur une ligne où on écrit
		char texte_liaisons[NB_CHAR_TAMPON];

		//Écrire nom porte
		position_liaisons += sprintf(texte_liaisons, "%s ", circuit->portes[i]->nom);

		//Écrire nom(s) de(s) liaison(s)
		for (int j = 0; j < circuit->portes[i]->nb_entrees; j++)
		{
			//Si le nom de la liaison est vide:
			if (strcmp(circuit->portes[i]->entrees[j]->nom_liaison, "") == 0)
				position_liaisons += sprintf(texte_liaisons + position_liaisons, "%s ", "XX");

			//Sinon, on affiche le nom de la liaison
			else
			{
				position_liaisons += sprintf(texte_liaisons + position_liaisons, "%s ",
					circuit->portes[i]->entrees[j]->nom_liaison);
				printf(circuit->portes[i]->entrees[j]->nom_liaison);
			}		
		}
		
		//Ajouter la porte et ses liaisons au fichier
		fprintf(fsortie, "%s\n", texte_liaisons);
	}

	//Pour finir, on va sérialiser les sorties
	//
	//Écrire nom sorties
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		int position_sorties = 0;	//Position sur une ligne où on écrit
		char texte_sorties[NB_CHAR_TAMPON];

		//Écrire nom sortie
		position_sorties += sprintf(texte_sorties, "%s ", circuit->sorties[i]->nom);

		//Écrire nom liaison de la sortie
		position_sorties += sprintf(texte_sorties + position_sorties, "%s ", 
			circuit->sorties[i]->pin->nom_liaison);

		//Ajouter la porte et ses liaisons au fichier
		fprintf(fsortie, "%s\n", texte_sorties);
	}
	
	fclose(fsortie);
}

/**********************************************************************************/
void circuit_IO_charger(const char* chemin_acces, t_circuit* circuit)
{
	/*
	FILE* fentree = fopen(chemin_acces, "r");

	//si le fichier est vide, on retourne faux
	if (fentree == NULL)
	{
		printf("Erreur à l'ouverture du fichier!");
		return FAUX;
	}

	//Faire la lecture du nombre de composants
	fscanf(fentree, "%d", &circuit->nb_entrees);
	fscanf(fentree, "%d", &circuit->nb_sorties);
	fscanf(fentree, "%d", &circuit->nb_portes);

	//Faire la lecture de l'id et du nom et les mettre pour chaque entrée
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		int id = NULL;
		char nom_composant[NB_CHAR_COMPOSANT];
		char* nom = _strdup(nom_composant);		//Allouer mémoire pour chaque nom

		//Lire l'ID et le nom afin d'initialiser l'entrée et l'ajouter au circuit
		fscanf(fentree, "%d%s\n", &id, nom);
		circuit->entrees[i] = t_entree_init(id, nom);
	}

	//Faire la lecture de l'id et du nom et les mettre pour chaque sortie
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		int id = NULL;
		char nom_composant[NB_CHAR_COMPOSANT];
		char* nom = _strdup(nom_composant);		//Allouer mémoire pour chaque nom

		//Lire l'ID et le nom afin d'initialiser la sortie et l'ajouter au circuit
		fscanf(fentree, "%d%s\n", &id, nom);
		circuit->sorties[i] = t_sortie_init(id, nom);
	}

	//Faire la lecture de l'id et du nom et les mettre pour chaque porte
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		int id = NULL;
		e_types_portes type = 0;
		char nom_composant[NB_CHAR_COMPOSANT];
		char* nom = _strdup(nom_composant);		//Allouer mémoire pour chaque nom

		//Lire l'ID et le nom afin d'initialiser la porte et l'ajouter au circuit
		fscanf(fentree, "%d%d%s\n", &id, &type, nom);
		circuit->portes[i] = t_porte_init(id, type, nom);
	}

	//Lire les liaisons
	while (!feof(fentree))
	{
		int porte_nb_entrees;
		int porte_position;
		int liaison_position;

		char nom_composant[NB_CHAR_COMPOSANT];	//Nom du composant
		char nom_liaison[NB_CHAR_COMPOSANT];	//Nom de la liaison

		//Lire nom de l'objet-destination
		fscanf(fentree, "%s", nom_composant);
		printf("%c", nom_composant[0]);
		printf("%c", nom_composant[1]);

		//Si l'objet est une porte
		if (nom_composant[0] == 'P')
		{
			//Le 2e caractère équivaut à la position de la porte
			porte_position = (int)nom_composant[1] - CONVERT_ASCII;
			porte_nb_entrees = circuit->portes[porte_position]->nb_entrees;

			//Lire prochain nom(s) de liaison(s) dans le fichier, selon le nombre de pin d'entrées
			for (int j = 0; j < porte_nb_entrees; j++)
			{
				fscanf(fentree, "%s", nom_liaison);

				//Pin de sortie de la source de la liaison
				t_pin_sortie* source = NULL;

				//Si c'est une entrée, on va la chercher et prendre son pin de sortie
				if (nom_liaison[0] == 'E')
				{
					liaison_position = nom_liaison[1] - CONVERT_ASCII;

					//Chercher le pin de sortie de l'entrée source selon la position
					t_pin_sortie* source = t_entree_get_pin(circuit->entrees[liaison_position]);
				}

				//Sinon, on va chercher la porte source et son pin de sortie
				else
				{
					liaison_position = nom_liaison[1] - CONVERT_ASCII;

					//Chercher le pin de sortie de l'entrée source selon la position
					t_pin_sortie* source = t_porte_get_pin_sortie(circuit->portes[liaison_position]);
				}

				//Faire la liaison
				t_porte_relier(circuit->portes[porte_position], j, nom_liaison, source);
			}
		}


	}

	fclose(fentree);
	*/
}