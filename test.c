#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Carte{
    int numero;     //numéro carte de 1 à 104
    int valeur;     //nombre tête de boeuf de 1 à 7
} Carte;


typedef struct Joueur{              //structure joueur en fonction de son nom sa main et son nb de points
    char* nom;
    Carte* main;
    int nbPoints;
} Joueur;


typedef struct Noeud{
    Carte carte;
    int tailleListe;
    struct Noeud* suivant;
} Noeud;


int main(){
    Noeud** plateau = malloc(4 * sizeof(malloc(sizeof(Noeud))));
    Joueur* tblJoueurs = creerTblJoueurs(4);
    
    distribution(plateau, tblJoueurs, 4, 104);
    affPrincipal(plateau, tblJoueurs, 4);
    affMain(tblJoueurs[0].main, 10);
    
    
    return 0;
}