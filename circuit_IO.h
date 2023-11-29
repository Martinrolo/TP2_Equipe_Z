/*
Module: circuit_IO
Description: Contients des fonctions faisant la sauvegarde et la charge de circuits
	dans des fichiers.
Auteurs: Martin Rolo Dussault, Antoine St-Amour, Maxim Dmitriev
*/
#ifndef CIRCUIT_IO_H_
#define CIRCUIT_IO_H_

#include <stdio.h>
#include "t_circuit.h"

/*
Fonction: circuit_IO_sauvegarder
Description: Cr�e une sauvegarde de circuit dans un fichier texte

Param�tres: Le nom du fichier o� sera effectu�e la sauvegarde
Retour: Aucun
Param�tres modifi�: N/A.
*/
void circuit_IO_sauvegarder(const char* nom_fichier, const t_circuit* circuit);

/*
Fonction: circuit_IO_charger
Description: Charge un fichier texte qui d�crit un circuit, et construit ce m�me
circuit

Param�tres: Le nom du fichier qui contient la sauvegarde du circuit, et le circuit
Retour: Aucun
Param�tres modifi�: N/A.
*/
void circuit_IO_charger(const char* chemin_acces, t_circuit* circuit);
#endif
