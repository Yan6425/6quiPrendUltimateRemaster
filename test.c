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
    Joueur* tblJoueurs = creerTblJoueurs(10);
    for (int i = 0; i < 10; i++){
        printf("Joueur %d : %s\n", i + 1, tblJoueurs[i].nom);
    }
    Noeud* test = NULL;
    for (int i = 0; i < 4; i++){
        insererNoeud(&test, creerCarte(i), 0);
    }
    affListe(test);
    affListe(extraireNoeud(&test, 0));
    
    distribution(plateau, tblJoueurs, 10, 104);
    affPlateau(plateau);
    for (int i = 0; i < 10; i++){
        affMain(tblJoueurs[i].main, 10);
    }
    
    
    return 0;
}