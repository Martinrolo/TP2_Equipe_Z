/*definitions pour la librairie de fonctions partie_bonus
Description: Contient des fonctions afin de cr�er une matrice binaire
    qui d�crit la table de v�rit� d'un circuit donn�
    Auteur: Martin Rolo Dussault, Maxim Dmitriev, Antoine St-Amour
    */

#define _CRT_SECURE_NO_WARNINGS
#include "t_circuit.h"
#include "partie_bonus.h"
#include <math.h>

/*******************************************************************************************/
/*                                   FONCTIONS PRIV�ES                                     */
/*******************************************************************************************/

/**********************************************************************/
//Fonction inverser_tab_bits
//  Inverse le contenu d'un tableau en param�tre
//Param�tres:  le tableau � inverser, nombre de bits du tableau, le circuit
//Retourne: rien
//Param�tres modifi�s: le tableau de r�sultat contenant les bits
static void inverser_tab_bits(int tab_bits[], int nb_bits, const t_circuit* le_circuit)
{
    int i;
    int temp;

    if (nb_bits > t_circuit_get_nb_entrees(le_circuit))
        return 0;

    //On fait une boucle pour inverser les bits entre les indices plus grands et plus petits
    for (i = 0; i < nb_bits / 2; i++)
    {
        temp = tab_bits[i];
        tab_bits[i] = tab_bits[nb_bits - 1 - i];
        tab_bits[nb_bits - 1 - i] = temp;
    }
}

/**********************************************************************/
//Fonction codage_dec2bin
//  Permet de traduire un nombre d�cimal en binaire, afin de calculer toutes les combinaisons
//  de bits appliqu�s aux entr�es
//Param�tres:   nombre � traduire, tableau o� on va stocker les bits, le circuit
//Retourne: rien
//Param�tres modifi�s: le tableau de r�sultat contenant les bits

static void codage_dec2bin(int nombre, int resultat[], const t_circuit* le_circuit)
{
    int i, bit;

    //Pour d�terminer si la case du tableau contient un 1 ou un 0
    for (i = 0; i < t_circuit_get_nb_entrees(le_circuit); i++) {
        bit = nombre % 2;
        resultat[i] = bit;
        nombre /= 2;
    }

    //Inverser les bits pour avoir la table de v�rit� en ordre croissant
    inverser_tab_bits(resultat, t_circuit_get_nb_entrees(le_circuit), le_circuit);
}

/*******************************************************************************************/
/*                                   FONCTIONS PUBLIQUES                                   */
/*******************************************************************************************/

/**********************************************************************/
int** t_circuit_tdv(const t_circuit* le_circuit)
{
	int nb_entrees = t_circuit_get_nb_entrees(le_circuit);
	int nb_sorties = t_circuit_get_nb_sorties(le_circuit);
	int nb_colonnes = nb_entrees + nb_sorties;              //Nombre de colonnes de la matrice
	int nb_lignes = pow(2, nb_entrees);                     //Nombre de lignes de la matrice
    int* signal = (int*)malloc(nb_entrees * sizeof(int));   //Tableau des bits qu'on va appliquer

    //Cr�er la matrice
    int** matrice = (int**)malloc(nb_lignes * sizeof(int*));
    for (int i = 0; i < nb_lignes; i++)
    {
        matrice[i] = (int*)malloc(nb_colonnes * sizeof(int));
    }

    //Mettre les valeur de toutes les combinaisons d'entr�es
	for (int i = 0; i < nb_lignes; i++)
	{
        t_circuit_reset(le_circuit);

        //Traduire la ligne en binaire
        int* bits_entrees = (int*)malloc(nb_entrees * sizeof(int*));
        codage_dec2bin(i, bits_entrees, le_circuit);

        //mettre les bits des entr�es dans le tableau + les bits dans le signal
        for (int j = 0; j < nb_entrees; j++)
        {
            matrice[i][j] = bits_entrees[j];
            signal[j] = bits_entrees[j];
        }

        //quand tous les bits d'une entr�e sont appliqu�es, on peut appliquer 
        //le signal et calculer les sorties
        t_circuit_appliquer_signal(le_circuit, signal, t_circuit_get_nb_entrees(le_circuit));
        t_circuit_propager_signal(le_circuit);

        //�crire les valeurs des sorties dans la matrice
        for (int k = 0; k < nb_sorties; k++)
        {
            //chaque bit de sortie est � la position nb_entrees+k dans la matrice
            matrice[i][nb_entrees + k] = le_circuit->sorties[k]->pin->valeur;
        }
	}

    return matrice;
}

/**********************************************************************/
void t_circuit_tdv_destroy(t_circuit* circuit, int** matrice)
{
    int nb_entrees = t_circuit_get_nb_entrees(circuit);
    int nb_sorties = t_circuit_get_nb_sorties(circuit);
    int nb_colonnes = nb_entrees + nb_sorties;              //Nombre de colonnes de la matrice
    int nb_lignes = pow(2, nb_entrees);                     //Nombre de lignes de la matrice

    //Lib�rer la matrice
    for (int i = 0; i < nb_lignes; i++)
    {
        free(matrice[i]);
    }

    free(matrice);
}
