/*
Module: circuit_IO
Description: Contients des fonctions faisant la sauvegarde et la charge de circuits
	dans des fichiers.
Auteurs: Martin Rolo Dussault, Antoine St-Amour, Maxim Dmitriev
*/
#define _CRT_SECURE_NO_WARNINGS
#include "circuit_IO.h"

#define NB_CHAR_SERIALISER 10 //Nombre de caractères par ligne qu'on va sérialiser

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
				position_liaisons += sprintf(texte_liaisons + position_liaisons, "%s ", circuit->portes[i]->entrees[j]->nom_liaison);
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
		position_sorties += sprintf(texte_sorties + position_sorties, "%s ", circuit->sorties[i]->pin->nom_liaison);

		//Ajouter la porte et ses liaisons au fichier
		fprintf(fsortie, "%s\n", texte_sorties);
	}
	
	fclose(fsortie);
}

/**********************************************************************************/
void circuit_IO_charger(const char* chemin_acces, t_circuit* circuit)
{

}