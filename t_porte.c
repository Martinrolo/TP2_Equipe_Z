#include "t_porte.h"

//FONCTION static d�finir nb_entrees
static void creer_entrees(e_types_portes type, t_porte* porte)
{
	if (type == PORTE_NOT)
	{
		porte->nb_entrees = 1;
		porte->entrees[0] = t_pin_entree_init();
	}

	else
	{
		porte->nb_entrees = MAX_ENTREES_PORTE;

		for (int i = 0; i < MAX_ENTREES_PORTE; i++)
			porte->entrees[i] = t_pin_entree_init();
	}
}

t_porte* t_porte_init(int id, e_types_portes type, char* nom)
{
	//Selon le type (SOUS-PROGRAMME STATIC):
	//	-�tablir le nb_entrees (1 ou 2)
	//	-Cr�er le(s) entre�e(s) avec t_pin_entree_init()
	//Cr�er la sortie (t_pin_sortie_init)
	t_porte* nouvelle_porte;

	nouvelle_porte = (t_porte*)malloc(sizeof(t_porte));

	//Assigner les valeurs des param�tres
	nouvelle_porte->id = id;
	nouvelle_porte->nom = nom;
	nouvelle_porte->type = type;

	//Cr�es la/les entr�es
	creer_entrees(type, nouvelle_porte);

	//Cr�er la sortie de la porte
	nouvelle_porte->sortie = t_pin_sortie_init();

	return nouvelle_porte;
}

/********************************************************************/
void t_porte_destroy(t_porte* porte)
{
	//Lib�rer le/les entr�es et la sortie en 1er
	t_pin_entree_destroy(porte->entrees);
	t_pin_sortie_destroy(porte->sortie);

	//Lib�rer la porte elle-m�me
	free(porte);
}

/********************************************************************/
void t_porte_calculer_sorties(t_porte* porte)
{
	int val_entree0, val_entree1;
	int resultat;

	//R�cup�rer les valeurs aux entr�es avec t_pin_entree_get_valeur()
	val_entree0 = t_pin_entree_get_valeur(porte->entrees[0]);

	if (porte->nb_entrees == MAX_ENTREES_PORTE)
		val_entree1 = t_pin_entree_get_valeur(porte->entrees[1]);

	//	Attribuer la valeur de sortie selon le calcul du type, avec t_pin_sortie_set_valeur()
	switch (porte->type)
	{
	case PORTE_ET:
		resultat = (val_entree0 & val_entree1);
		break;

	case PORTE_OU:
		resultat = (val_entree0 | val_entree1);
		break;

	case PORTE_XOR:
		resultat = (val_entree0 ^ val_entree1);
		break;

	case PORTE_NOT:
		resultat = !val_entree0;
		break;
	}

	printf("R�sultat: %d", resultat);

	t_pin_sortie_set_valeur(porte->sortie, resultat);
}

/********************************************************************/
int t_porte_relier(t_porte* dest, int num_entree, char* nom_sortie, t_pin_sortie* source)
{
	//Valider "num_entree" re�u selon le nb_entrees de la porte
	//	Return 0 si non-valide
	//Si OK: On relie la source dans l'entr�e num�ro num_entree avec t_pin_entree_relier
}

/********************************************************************/
int t_porte_est_reliee(t_porte* porte)
{
	//V�rifier le(s) entr�e(s) avec t_pin_entree_est_reliee
	//V�rifier la sortie avec t_pin_sortie_est_reliee
}

/********************************************************************/
void t_porte_reset(t_porte* porte)
{
	//Mettre les entr�es et sorties � INACTIF avec t_pin_entree_set_valeur et t_pin_sortie_set_valeur.
}

/********************************************************************/
int t_porte_propager_signal(t_porte* porte)
{
	//Si une des entr�es est INACTIF, return 0
	//Sinon, on calcule la sortie avec t_porte_calculer_sortie)
	//Ensuite, appeler t_pin_sortie_propager_signal() et return son r�sultat

	//POUR TESTER LES PORTES: Faire un circuit avec 2 entr�es, 1 sortie et 1 porte.
}

int t_porte_get_id(const t_porte* porte)
{

}

char* t_porte_get_nom(const t_porte* porte)
{

}

int t_porte_get_nb_entrees(const t_porte* porte)
{

}

e_types_portes t_porte_get_type(const t_porte* porte)
{

}

t_pin_entree* t_porte_get_pin_entree(const t_porte* porte, int num)
{

}

t_pin_sortie* t_porte_get_pin_sortie(const t_porte* porte)
{

}

void t_porte_serialiser(const t_porte* porte, char* resultat)
{

}
