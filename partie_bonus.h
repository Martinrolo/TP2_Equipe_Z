/*definitions pour la librairie de fonctions partie_bonus
Description: Contient des fonctions afin de créer une matrice binaire
	qui décrit la table de vérité d'un circuit donné
	Auteur: Martin Rolo Dussault, Maxim Dmitriev, Antoine St-Amour
	*/

#ifndef PARTIE_BONUS_H_
#define PARTIE_BONUS_H_

#include <stdio.h>
#include "t_circuit.h"

/*
Fonction: t_circuit_tdv
Description: Génère une matrice contenant la table de vérité du circuit en paramètre

Paramètres: Le circuit (doit être déjà construit)
Retour: La matrice
Paramètres modifié: N/A.
*/
int** t_circuit_tdv(const t_circuit* le_circuit);

#endif