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
    if (carte.numero == 55){    //conditions pour donner le nombre de tête de taureau
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


typedef struct Joueur{ //structure joueur en fonction de son nom sa main et son nb de points
    char* nom;
    Carte* main;
    int nbPoints;
} Joueur;


Joueur creerJoueur(char* nom){//donne un nom,une main et un nombre de points 
    Joueur joueur;
    joueur.nom = nom;
    joueur.main = malloc(10 * sizeof(Carte)); //initialise la main du joueur
    joueur.nbPoints = 0;
    return joueur;
}


typedef struct Noeud{
    Carte carte;
    Noeud* suivant;
} Noeud;


Joueur* creerTblJoueurs(int nombreJoueurs){//mise en place d'un tableau pour rassembler tous les joueurs
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
    Noeud** plateau = malloc(4 * sizeof( (Noeud*)malloc(sizeof(Noeud)) ));//initialisation du plateau

    distribution(plateau, tblJoueurs, nbJoueurs, nbCartes);
}



int distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud* paquet = melangerCartes(int nbCartes);//création du paquets
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
    Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));//allocation pour la taille d'un noeud 
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

Carte choixCarte (Joueur* joueur, int nbCartes){
    int reponseJoueur;
    Carte carte;
    int j=0;
    Carte* tabTmp = malloc((nbCartes-1) * sizeof(Carte));
    do {
        printf("%s, quelle carte voulez vous jouer ? ", joueur->nom);
        scanf("%d",reponseJoueur);
    }while (reponseJoueur<1 || reponseJoueur>nbCartes);
    for (int i = 0; i < nbCartes; i++){
        if (i != reponseJoueur - 1){
            tabTmp[j] = joueur->main[i];
            j++;
        }
    }
    carte = joueur->main[reponseJoueur - 1];
    realloc(joueur->main, (nbCartes - 1)*sizeof(Carte));
    joueur->main = tabTmp;
    return carte;
} 