/*
Module: circuit_IO
Description: Contients des fonctions faisant la sauvegarde et la charge de circuits
	dans des fichiers.
Auteurs: Martin Rolo Dussault, Antoine St-Amour, Maxim Dmitriev
*/
#define _CRT_SECURE_NO_WARNINGS
#include "circuit_IO.h"

void circuit_IO_sauvegarder(const char* nom_fichier, const t_circuit* circuit)
{
	//Ouvrir le fichier
	FILE* fsortie;
	fsortie = fopen(nom_fichier, "a");

	//Afficher nombre de composants dans texte
	char texte[100];
	sprintf(texte, "%d", circuit->nb_entrees);
	fprintf(fsortie, "%s\n", texte);
	sprintf(texte, "%d", circuit->nb_sorties);
	fprintf(fsortie, "%s\n", texte);
	sprintf(texte, "%d", circuit->nb_portes);
	fprintf(fsortie, "%s\n", texte);

	//Écrire texte dans fichier
	printf("Nombres: %s", texte);

	//Ajouter texte pour chaque entrée
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_serialiser(circuit->entrees[i], &texte);
		fprintf(fsortie, "%s\n", texte);
	}

	//Ajouter texte pour chaque sortie
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_serialiser(circuit->sorties[i], &texte);
		fprintf(fsortie, "%s\n", texte);
	}

	//Ajouter texte pour chaque porte
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_serialiser(circuit->portes[i], &texte);
		fprintf(fsortie, "%s\n", texte);
	}

	fclose(fsortie);
}

/**********************************************************************************/
void circuit_IO_charger(const char* chemin_acces, t_circuit* circuit)
{

}