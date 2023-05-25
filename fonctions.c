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
    Carte* carte;
    Noeud* suivant;
} Noeud;


void creerJoueurs(int nombreJoueurs){
    // explication de la fonction

}


Joueur _creerJoueur(char* nom){
    Joueur joueur;
    joueur.nom = nom;
    joueur.main = malloc(10 * sizeof(Carte));
    return joueur;
}


void reglages(){
    // explication de la fonction

}


void lancerPartie(){
    // explication de la fonction
}


int _distribution(){
    // explication de la fonction
    return 0;
}


Carte _creerCarte(int numero){
    Carte carte;
    carte.numero = numero;
    if (numero % 10 == 5){
        carte.valeur = 2;
    }
    else if (numero % 10 == 0){
        carte.valeur = 3;
    }
    else if (numero % 11 == 0){
        carte.valeur = 5;
    }
    else if (numero == 5){
        carte.valeur = 7;
    }
    else {
        carte.valeur = 1;
    }
    return carte;
}


int _choixCarte(){
    // explication de la fonction
    return 0;
}


int _comparaisons(){
    // explication de la fonction
    return 0;
}


int _distributionPts(){
    // explication de la fonction
    return 0;
}

