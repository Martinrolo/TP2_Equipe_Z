//
#define _CRT_SECURE_NO_WARNINGS
#include "t_circuit.h"
#include <math.h>

int** t_circuit_tdv(const t_circuit* le_circuit)
{
	int nb_entrees = t_circuit_get_nb_entrees(le_circuit);
	int nb_sorties = t_circuit_get_nb_sorties(le_circuit);
	int nb_colonnes = nb_entrees + nb_sorties;
	int nb_lignes = pow(2, nb_entrees);


	int signal[MAX_ENTREES];
	for (int i = 0; i < nb_entrees; i++)
	{

	}


}

int codage_dec2bin(int nombre, int resultat[])
{
    int i, bit;
    int nb_bits = 0;

    //Pour déterminer si la case du tableau contient un 1 ou un 0
    for (i = 0; i < CODAGE_NB_BITS; i++) {
        bit = nombre % 2;
        resultat[i] = bit;
        //Pour trouver le nombre de bits utilisés pour écrire la valeur en binaire
        if (nombre)
        {
            nb_bits++;
        }
        nombre /= 2;
    }

    inverser_tab_bits(resultat, CODAGE_NB_BITS);
    return nb_bits;
}