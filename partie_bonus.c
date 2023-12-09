//
#define _CRT_SECURE_NO_WARNINGS
#include "t_circuit.h"
#include "partie_bonus.h"
#include <math.h>


/**********************************************************************/
int** t_circuit_tdv(const t_circuit* le_circuit)
{
	int nb_entrees = t_circuit_get_nb_entrees(le_circuit);
	int nb_sorties = t_circuit_get_nb_sorties(le_circuit);
	int nb_colonnes = nb_entrees + nb_sorties;
	int nb_lignes = pow(2, nb_entrees);
    int* signal = (int*)malloc(nb_entrees * sizeof(int));

    //Créer la matrice
    int** matrice = (int**)malloc(nb_lignes * sizeof(int*));
    for (int i = 0; i < nb_lignes; i++)
    {
        matrice[i] = (int*)malloc(nb_colonnes * sizeof(int));
    }

    //Mettre les valeur de toutes les combinaisons d'entrées
	for (int i = 0; i < nb_lignes; i++)
	{
        t_circuit_reset(le_circuit);

        //Traduire la ligne en binaire
        int* bits_entrees = (int*)malloc(nb_entrees * sizeof(int*));
        codage_dec2bin(i, bits_entrees, le_circuit);

        //mettre les bits des entrées dans le tableau + les bits dans le signal
        for (int j = 0; j < nb_entrees; j++)
        {
            matrice[i][j] = bits_entrees[j];
            signal[j] = bits_entrees[j];
        }

        //quand tous les bits d'une entrée sont appliquées, on peut appliquer 
        //le signal et calculer les sorties
        t_circuit_appliquer_signal(le_circuit, signal, t_circuit_get_nb_entrees(le_circuit));
        t_circuit_propager_signal(le_circuit);

        //écrire les valeurs des sorties dans la matrice
        for (int k = 0; k < nb_sorties; k++)
        {
            //chaque bit de sortie est à la position nb_entrees+k dans la matrice
            matrice[i][nb_entrees + k] = le_circuit->sorties[k]->pin->valeur;
        }
	}

    return matrice;
}

static int codage_dec2bin(int nombre, int resultat[], const t_circuit* le_circuit)
{
    int i, bit;
    int nb_bits = 0;

    //Pour déterminer si la case du tableau contient un 1 ou un 0
    for (i = 0; i < t_circuit_get_nb_entrees(le_circuit); i++) {
        bit = nombre % 2;
        resultat[i] = bit;
        //Pour trouver le nombre de bits utilisés pour écrire la valeur en binaire
        if (nombre)
        {
            nb_bits++;
        }
        nombre /= 2;
    }

    inverser_tab_bits(resultat, t_circuit_get_nb_entrees(le_circuit), le_circuit);
    return nb_bits;
}

static int inverser_tab_bits(int tab_bits[], int nb_bits, const t_circuit* le_circuit)
{
    int i;
    int temp;

    if (nb_bits > t_circuit_get_nb_entrees(le_circuit))
        return 0;

    for (i = 0; i < nb_bits / 2; i++)
    {
        temp = tab_bits[i];
        tab_bits[i] = tab_bits[nb_bits - 1 - i];
        tab_bits[nb_bits - 1 - i] = temp;
    }

    return 1;
}