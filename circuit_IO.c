/*
Module: circuit_IO
Description: Contients des fonctions faisant la sauvegarde et la charge de circuits
	dans des fichiers.
Auteurs: Martin Rolo Dussault, Antoine St-Amour, Maxim Dmitriev
*/
#define _CRT_SECURE_NO_WARNINGS
#include "circuit_IO.h"

#define NB_CHAR_SERIALISER	10	//Nombre de caractères par ligne qu'on va sérialiser
#define NB_CHAR_COMPOSANT	2	//Nombre de caractères par nom de composant
#define CONVERT_ASCII		48	//Nombre pour faire la conversion entre int et ASCII

void circuit_IO_sauvegarder(const char* nom_fichier, const t_circuit* circuit)
{
	//Ouvrir le fichier
	FILE* fsortie;
	fsortie = fopen(nom_fichier, "a");

	//Chercher les nombres de composants
	char texte[NB_CHAR_SERIALISER];
	int position_texte = 0;

	position_texte += sprintf(texte, "%d ", circuit->nb_entrees);
	position_texte += sprintf(texte + position_texte, "%d ", circuit->nb_sorties);
	position_texte += sprintf(texte + position_texte, "%d", circuit->nb_portes);

	//Mettre le texte des nombres de composants dans le fichier
	fprintf(fsortie, "%s\n", texte);

	//Ajouter texte pour chaque entrée
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_serialiser(circuit->entrees[i], &texte);
		fprintf(fsortie, "%s", texte);
	}

	//Ajouter texte pour chaque sortie
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_serialiser(circuit->sorties[i], &texte);
		fprintf(fsortie, "%s", texte);
	}

	//Ajouter texte pour chaque porte
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_serialiser(circuit->portes[i], &texte);
		fprintf(fsortie, "%s", texte);
	}

	//
	//Sérialiser les liaisons
	//
	//D'abord, on parcourt toutes les portes 
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		int position_liaisons = 0;
		char texte_liaisons[NB_CHAR_SERIALISER];

		//Écrire nom porte
		position_liaisons += sprintf(texte_liaisons, "%s ", circuit->portes[i]->nom);

		//Écrire nom(s) de(s) liaison(s)
		for (int j = 0; j < circuit->portes[i]->nb_entrees; j++)
		{
			//Si le nom est vide:
			if (circuit->portes[i]->entrees[j]->nom_liaison == NULL)
				position_liaisons += sprintf(texte_liaisons + position_liaisons, "%s ", "XX");
			else
				position_liaisons += sprintf(texte_liaisons + position_liaisons, "%s ", 
					circuit->portes[i]->entrees[j]->nom_liaison);
		}
		
		//Ajouter la porte et ses liaisons au fichier
		fprintf(fsortie, "%s\n", texte_liaisons);
	}

	//Pour finir, on va sérialiser les sorties
	//
	//Écrire nom sorties
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		int position_sorties = 0;
		char texte_sorties[NB_CHAR_SERIALISER];

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
	FILE* fentree = fopen(chemin_acces, "r");

	//si le fichier est vide, on retourne faux
	if (fentree == NULL)
		return FAUX;

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
		int sortie_position;
		int liaison_position;

		//composants source
		t_entree* entree;
		t_sortie* sortie;
		t_porte* porte;
		t_porte* porte_source;	//Dans le cas où la porte-destination est liée à une porte

		//Tableaux de caractères contenant les noms de composants
		char nom_composant[NB_CHAR_COMPOSANT];	//Nom du composant
		char* dup_nom_composant = _strdup(nom_composant);

		char nom_liaison[NB_CHAR_COMPOSANT];	//Nom de la liaison
		char* dup_nom_liaison = _strdup(nom_liaison);

		//Lire nom de l'objet-destination
		fscanf(fentree, "%s", dup_nom_composant);
		printf("%c", dup_nom_composant[0]);
		printf("%c", dup_nom_composant[1]);

		//Si l'objet est une porte
		if (dup_nom_composant[0] == 'P')
		{
			//Le 2e caractère équivaut à la position de la porte
			porte_position = (int)dup_nom_composant[1] - CONVERT_ASCII;

			//On va chercher la porte et son nombre d'entrées
			porte = circuit->portes[porte_position];
			porte_nb_entrees = porte->nb_entrees;

			//Lire prochain nom(s) de liaison(s) dans le fichier, selon le nombre de pin d'entrées
			for (int j = 0; j < porte_nb_entrees; j++)
			{
				//Lire le composant source de la liaison
				fscanf(fentree, "%s", dup_nom_liaison);

				//Si c'est une entrée, on va la chercher et prendre son pin de sortie
				if (dup_nom_liaison[0] == 'E')
				{
					//on cherche la position de l'entrée afin de la trouver
					liaison_position = dup_nom_liaison[1] - CONVERT_ASCII;
					entree = circuit->entrees[liaison_position];

					//Chercher le pin de sortie de l'entrée source selon la position
					t_pin_sortie* source = t_entree_get_pin(entree);

					//Faire la liaison
					t_porte_relier(porte, j, dup_nom_liaison, source);
				}

				//Sinon, on va chercher la porte source et son pin de sortie
				else
				{
					//Chercher la position de la porte et la trouver dans le circuit
					liaison_position = dup_nom_liaison[1] - CONVERT_ASCII;
					porte_source = circuit->portes[liaison_position];

					//Chercher le pin de sortie de l'entrée source selon la position
					t_pin_sortie* source = t_porte_get_pin_sortie(porte);

					//Faire la liaison
					t_porte_relier(porte, j, dup_nom_liaison, source);
				}
			}
		}

		//Sinon, l'objet-destinaion est une sortie
		else if (dup_nom_composant[0] == 'S')
		{
			sortie_position = (int)dup_nom_composant[1] - CONVERT_ASCII;
			sortie = circuit->sorties[sortie_position];

			//Chercher le composant source de la liaison
			fscanf(fentree, "%s", dup_nom_liaison);
			liaison_position = (int)dup_nom_liaison[1] - CONVERT_ASCII;
			porte_source = circuit->portes[liaison_position];
		

			//relier la sortie à la porte
			t_sortie_relier(sortie, dup_nom_liaison, porte_source);
		}

		//sinon, skip
		else
		{

		}
	}

	fclose(fentree);
}