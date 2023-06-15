#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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


typedef struct Carte{
    int numero;     //numéro carte de 1 à 104
    int valeur;     //nombre tête de boeuf de 1 à 7
} Carte;


Carte creerCarte(int numero){
    Carte carte;
    carte.numero = numero;
    if (carte.numero == 55){
        carte.valeur=7
    }
    else if (carte.numero % 10 == 0){
        carte.valeur=3
    }
    else if (carte.numero % 5 == 0){
        carte.valeur=2 
    }
    else if (carte.numero % 10 == 0){
        carte.valeur=5
    }
    else carte.valeur=1
    
    return carte;
}  


typedef struct Noeud{
    Carte carte;
    Noeud* suivant;
} Noeud;


void insererNoeud(Noeud** liste, Carte carte, int index){
    for (int i = 0; i < index; i++){
        liste = &((*liste)->suivant);
    }
    Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
    noeud->carte = carte;
    noeud->suivant = *liste;
    liste = &noeud;
}


Noeud* extraireNoeud(Noeud** liste, int index){
    for (int i = 0; i < index; i++){
        liste = &((*liste)->suivant);
    }
    Noeud* noeud = *liste;
    liste = &(noeud->suivant);

    return noeud;
}


void sixQuiPrend(){
    creerJoueurs(int nbJoueurs);
    reglages();
    lancerPartie();
}


void reglages(){
    // explication de la fonction

}


void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    // explication de la fonction
    Noeud** plateau = malloc(4 * sizeof( (Noeud*)malloc(sizeof(Noeud)) ));
    Joueur* tblJoueurs = creerTblJoueurs(nbJoueurs);

    distribution(plateau, tblJoueurs, nbJoueurs, nbCartes);
}


Joueur* creerTblJoueurs(int nbJoueurs){
    Joueur* tblJoueurs = malloc(nbJoueurs * sizeof(Joueur));
    char* nom = malloc(100 * sizeof(char));
    for (int i = 0; i < nbJoueurs; i++){
        printf("Joueur %d, entre ton nom : ", i + 1);
        scanf("%s", nom);
        tblJoueurs[i] = creerJoueur(nom);
    }
    return tblJoueurs;
}


int distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud* paquet = melangerCartes(int nbCartes);
    
    for (int i = 0; i < 4; i++){
        insererNoeud(&(plateau[i]), extraireNoeud(&paquet, 0)->carte, 0);
    }
    for (int i = 0; i < nbJoueurs; i++){
        tblJoueurs[i].main = distribuerMain(&paquet);
    }

    return 0;
}


Noeud* melangerCartes(int nbCartes){
    srand(time(NULL));
    Noeud* paquet = (Noeud*)malloc(sizeof(Noeud));
    Carte* tblCartes = malloc(nbCartes * sizeof(Carte));
    int iTmp;
    Carte tmp;

    for (int i = 1; i <= nbCartes; i++){
        tblCartes[i] = creerCarte(i);
    }
    for (int i = 0; i < nbCartes; i++){
        iTmp = rand() % nbCartes;
        tmp = tblCartes[iTmp];
        tblCartes[iTmp] = tblCartes[i];
        tblCartes[i] = tmp;
    }
    for (int i = 0; i < nbCartes; i++){
        insererNoeud(&paquet, tblCartes[i], 0);
    }

    return paquet;
}


Carte* distribuerMain(Noeud** paquet){
    Carte* main = malloc(10 * sizeof(Carte));
    Noeud* cartesTriees = (Noeud*)malloc(sizeof(Noeud));
    insererNoeud(&cartesTriees, extraireNoeud(&paquet, 0), 0);
    for (int i = 1; i < 10; i++){
        ///wip
    }
}