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

}


void lancerPartie(Joueur* tblJoueurs, int nombreJoueurs){
    Noeud** plateau = malloc(4 * sizeof( (Noeud*)malloc(sizeof(Noeud)) ));

    distribution(plateau, tblJoueurs, nbJoueurs, nbCartes);
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

int choixCarte (Joueur joueur, int nbCartes){
    int reponseJoueur;
    printf("%s, quelle carte voulez vous jouer ? ", joueur.nom);
    scanf("%d",reponseJoueur);
    while (reponseJoueur<0 || reponseJoueur>nbCartes){
        printf(" %s, entrez un nombre valide s'il vous plait !", joueur.nom);  //boucle si le joueur entre un mauvais nb


    }

    return Carte;
}