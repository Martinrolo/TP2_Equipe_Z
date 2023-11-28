#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "FILESLIB.h"

//fonction pour initialiser une file, la file sera vide 
void initfile(t_file *f)
{ f->debut = 0;
  f->fin   = MAXFILE-1;
  f->total = 0;
}

//fonction pour verifier si une file est pleine
int  pleine(const t_file *f)
{ return (f->total == MAXFILE); }

//fonction pour verifier si une file est vide
int  vide(const t_file *f)
{ return (f->total == 0); }

//fonction pour ajouter un element de plus a la fin d'une file
void ajouterfin(t_file *f, t_element el)
{ if (pleine(f))
    printf("ERREUR!!! Debordement de file.\n");
  else {
    f->fin = (f->fin+1) % MAXFILE;
    f->file[f->fin] = el;
    f->total++;
  }
}

//focntion pour enlever un element du debut d'une file
void enleverdebut(t_file *f, t_element *el)
{ if (vide(f))
    printf("ERREUR!!! File vide.\n");
  else {
    *el = f->file[f->debut];
    f->debut = (f->debut+1) % MAXFILE;
    f->total--;
  }
}
