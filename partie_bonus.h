/*definitions pour la librairie de fonctions partie_bonus
Description: Contient des fonctions afin de cr�er une matrice binaire
	qui d�crit la table de v�rit� d'un circuit donn�
	Auteur: Martin Rolo Dussault, Maxim Dmitriev, Antoine St-Amour
	*/

#ifndef PARTIE_BONUS_H_
#define PARTIE_BONUS_H_

#include <stdio.h>
#include "t_circuit.h"

/*
Fonction: t_circuit_tdv
Description: G�n�re une matrice contenant la table de v�rit� du circuit en param�tre

Param�tres: Le circuit (doit �tre d�j� construit)
Retour: La matrice
Param�tres modifi�: N/A.
*/
int** t_circuit_tdv(const t_circuit* le_circuit);

#endif