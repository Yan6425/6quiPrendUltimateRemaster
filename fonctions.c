#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct Joueur{
    char* nom;
    Carte* main;
} Joueur;


typedef struct Carte{
    int numero;     //numéro carte de 1 à 104
    int valeur;     //nombre tête de boeuf de 1 à 7
} Carte;

void creerJoueurs(int nbJoueurs);
    