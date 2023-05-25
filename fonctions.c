#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct Joueur{
    char* nom;
    Carte* main;
} Joueur;


typedef struct Carte{
    int numero;
    int valeur;
} Carte;


typedef struct Noeud{
    Carte carte;
    Noeud* suivant;
} Noeud;