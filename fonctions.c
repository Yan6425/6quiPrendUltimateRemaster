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


typedef struct Noeud{
    Carte carte;
    Noeud* suivant;
} Noeud;


void sixQuiPrend(){
    creerJoueurs(int nbJoueurs);
    reglages();
    jouer();

}

void jouer(){
    _distribution();
    _triMain();
    _choixCarte();
    _triCarte();
    _comparaisons();
    _distributionPts();

}
