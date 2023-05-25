#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Joueur{
    char* nom;
    Carte* main;
    int nbPoints;
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


 Joueur creerJoueur(char* nom){
    Joueur joueur;
    joueur.nom = nom;
    joueur.main = malloc(10 * sizeof(Carte));
    joueur.nbPoints = 0;
    return joueur;
}
    
    
