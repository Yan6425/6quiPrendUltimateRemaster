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


Joueur* creerTblJoueurs(int nombreJoueurs){
    Joueur* tblJoueur = malloc(nombreJoueurs * sizeof(Joueur));
    char* nom = malloc(100 * sizeof(char));
    for (int i = 0; i < nombreJoueurs; i++){
        printf("Joueur %d, entre ton nom : ", i + 1);
        scanf("%s", nom);
        tblJoueur[i] = creerJoueur(nom);
    }
    return tblJoueur;
}


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

Carte creerCarte(int numero){
    Carte carte;
    carte.numero = numero;
    if (carte.numero == 55){
        carte.valeur=7;
    }
    else if (carte.numero % 10 == 0){
        carte.valeur=3;
    }
    else if (carte.numero % 5 == 0){
        carte.valeur=2;
    }
    else if (carte.numero % 10 == 0){
        carte.valeur=5;
    }
    else carte.valeur=1;
    
    return carte;
}  


 Joueur creerJoueur(char* nom){
    Joueur joueur;
    joueur.nom = nom;
    joueur.main = malloc(10 * sizeof(Carte));
    joueur.nbPoints = 0;
    return joueur;
}

