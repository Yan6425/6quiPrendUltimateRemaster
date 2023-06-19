#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Carte{
    int numero;     //numéro carte de 1 à 104
    int valeur;     //nombre tête de boeuf de 1 à 7
} Carte;


Carte creerCarte(int numero){
    Carte carte;
    carte.numero = numero;
    if (carte.numero == 55){
        carte.valeur = 7;
    }
    else if (carte.numero % 10 == 0){
        carte.valeur = 3;
    }
    else if (carte.numero % 5 == 0){
        carte.valeur = 2; 
    }
    else if (carte.numero % 10 == 0){
        carte.valeur = 5;
    }
    else carte.valeur = 1;
    
    return carte;
}  


typedef struct Joueur{
    char* nom;
    Carte* main;
    int nbPoints;
} Joueur;


Joueur creerJoueur(char* nom){
    Joueur joueur;
    joueur.nom = nom;
    joueur.main = malloc(10 * sizeof(Carte));
    joueur.nbPoints = 0;
    return joueur;
}


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
    int nbJoueurs;
    int nbCartes;
    Joueur* tblJoueurs = creerTblJoueurs(nbJoueurs);
    reglages();
    lancerPartie(tblJoueurs, nbJoueurs, nbCartes);
}


void reglages(){
    // explication de la fonction

}


void lancerPartie(Joueur* tblJoueurs, int nombreJoueurs){
    // explication de la fonction
    Noeud** plateau = malloc(4 * sizeof( (Noeud*)malloc(sizeof(Noeud)) ));

    distribution(plateau, tblJoueurs, nbJoueurs, nbCartes);
}


int distribution(Joueur* tblJoueurs, int nombreJoueurs){
    Noeud* paquet = melangerCartes();
    return 0;
}


int distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud* paquet = melangerCartes(nbCartes);
    
    for (int i = 1; i <= 104; i++){
        ajouterNoeud(&listeDeCartes, creerCarte(i));
    }
    for (int i = 104; i > 0; i++){
        ajouterNoeud(&paquet, extraireCarte(&listeDeCartes, rand() % i));
    }

    return paquet;
}


void ajouterNoeud(Noeud** liste, Carte carte){
    Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
    noeud->carte = carte;
    noeud->suivant = *liste;
    *liste = noeud;
}


Carte extraireCarte(Noeud** liste, int index){
    for (int i = 0; i < index; i++){
        liste = &((*liste)->suivant);
    }
    Carte carte = (*liste)->carte;
    liste = &((*liste)->suivant);

    return carte;
}


Carte* distribuerMain(Noeud** paquet){
    Carte* main = malloc(10 * sizeof(Carte));
    Noeud* cartesTriees = (Noeud*)malloc(sizeof(Noeud));
    insererNoeud(&cartesTriees, extraireNoeud(paquet, 0)->carte, 0);
    for (int i = 1; i < 10; i++){
        ///wip
    }

    return main;
}
