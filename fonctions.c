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