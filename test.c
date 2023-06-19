#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Carte{
    int numero;     //numéro carte de 1 à 104
    int valeur;     //nombre tête de boeuf de 1 à 7
} Carte;


typedef struct Joueur{
    char* nom;
    Carte* main;
    int nbPoints;
} Joueur;


typedef struct Noeud{
    Carte carte;
    Noeud* suivant;
} Noeud;


int main(){
    Joueur joueur = creerJoueur("Bob");
    assert(joueur.nom = "Bob");
    assert(joueur.nbPoints = 0);
    assert(joueur.main = Carte*);
    assert(sizeof(joueur.main) = 10 * sizeof(Carte));
    
    return 0;
}