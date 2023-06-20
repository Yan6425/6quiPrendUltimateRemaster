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


typedef struct Joueur{              //structure joueur en fonction de son nom sa main et son nb de points
    char* nom;
    Carte* main;
    int nbPoints;
} Joueur;


Joueur creerJoueur(char* nom){              //donne un nom,une main et un nombre de points 
    Joueur joueur;
    joueur.nom = nom;
    joueur.main = malloc(10 * sizeof(Carte));           //initialise la main du joueur
    joueur.nbPoints = 0;
    return joueur;
}


Joueur* creerTblJoueurs(int nbJoueurs){             //mise en place d'un tableau dynamique pour rassembler tous les joueurs
    Joueur* tblJoueur = malloc(nbJoueurs * sizeof(Joueur));
    char* nom = malloc(100 * sizeof(char));
    for (int i = 0; i < nbJoueurs; i++){
        printf("Joueur %d, entre ton nom : ", i + 1);
        scanf("%s", nom);
        tblJoueur[i] = creerJoueur(nom);
    }
    return tblJoueur;
}


typedef struct Noeud{
    Carte carte;
    int tailleListe;
    struct Noeud* suivant;
} Noeud;


void insererNoeud(Noeud** liste, Carte carte, int index){
    for (int i = 0; i < index; i++){
        liste = &((*liste)->suivant);
    }
    Noeud* noeud = malloc(sizeof(Noeud));
    noeud->carte = carte;
    if (*liste != NULL){
        noeud->tailleListe = (*liste)->tailleListe + 1;
    }
    else noeud->tailleListe = 1;
    noeud->suivant = *liste;
    *liste = noeud;
}


Noeud* extraireNoeud(Noeud** liste, int index){
    for (int i = 0; i < index; i++){
        liste = &((*liste)->suivant);
    }
    Noeud* noeud = *liste;
    *liste = (*liste)->suivant;

    return carte;
}


void reglages(){
}


void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud** plateau = malloc(4 * sizeof( (Noeud*)malloc(sizeof(Noeud)) ));      //initialisation du plateau

    distribution(plateau, tblJoueurs, nbJoueurs, nbCartes);
}


void distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud* paquet = melangerCartes(int nbCartes);       //création du paquets de cartes
    for (int i = 0; i < 4; i++){
        insererNoeud(&(plateau[i]), extraireNoeud(&paquet, 0)->carte, 0);
    }
    for (int i = 0; i < nbJoueurs; i++){
        tblJoueurs[i].main = distribuerMain(&paquet);
    }
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
    insererNoeud(&cartesTriees, extraireNoeud(paquet, 0)->carte, 0);
    for (int i = 1; i < 10; i++){                   //boucle pour donner les cartes aux joueurs
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
    }while (reponseJoueur<1 || reponseJoueur>nbCartes);     //test pour s'assurer que le joueur entre bien un nombre correct
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


void affPlateau(Noeud** plateau){
    for (int i = 0; i < 4; i++){
        affLigne(&(plateau[i]));
    }
}


void affMain(Carte* main, int nbCartes){
    char** strCartes = malloc(8 * sizeof(char*));
    for (int i = 0; i < 8; i++) {
        strCartes[i] = malloc(20 + 13 * nbCartes * sizeof(char));
        sprintf(strCartes[i], "%*s", 20, "");
    }
    for (int i = 0; i < nbCartes; i++){
        catStrCartes(strCartes, main[i]);
    }
    for (int i = 0; i < 8; i++){
        printf("%s\n", strCartes[i]);
    }
}


void affLigne(Noeud** ligne){
    int tailleLigne = 13 * (*ligne)->tailleListe;
    char** strCartes = malloc(8 * sizeof(char*));
    for (int i = 0; i < 8; i++) {
        strCartes[i] = malloc(tailleLigne * sizeof(char));
    }
    remplirLigne(ligne, strCartes);
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < tailleLigne; j++){
            if (j == 65){
                printf("\x1b[31m");
            }
            printf("%c", strCartes[i][j]);
        }
        if (tailleLigne > 65){
            printf("\x1b[0m");
        }
        printf("\n");
    }
}


void remplirLigne(Noeud** ligne, char** strCartes){
    if ((*ligne)->suivant != NULL){
        remplirLigne(&((*ligne)->suivant), strCartes);
    }
    catStrCartes(strCartes, (*ligne)->carte);
}


void catStrCartes(char** strCartes, Carte carte){
    char** tdb = strValeur(carte.valeur);
    strcat(strCartes[0], " ---------   ");
    strcat(strCartes[1], "|         |  ");
    strcat(strCartes[2], "|"); strcat(strCartes[2], tdb[0]); strcat(strCartes[2], "|  ");
    strcat(strCartes[3], "|"); strcat(strCartes[3], tdb[1]); strcat(strCartes[3], "|  ");
    strcat(strCartes[4], "|         |  ");
    strcat(strCartes[5], "|   "); strcat(strCartes[5], stringNum(carte.numero)); strcat(strCartes[5], "   |  ");
    strcat(strCartes[6], "|         |  ");
    strcat(strCartes[7], " ---------   ");
}


char* stringNum(int numero){
    char* strNum = malloc(4 * sizeof(char));
    sprintf(strNum, "%*s%d%*s", !(numero / 100), "", numero, !(numero / 10), "");

    return strNum;
} 


char** strValeur(int valeur){
    char** tdb = malloc(2 * sizeof(malloc(5 * sizeof(char))));

    if (valeur == 7){
        tdb[0] = " * * * * ";
        tdb[1] = "  * * *  ";
    }
    else if (valeur == 3){
        tdb[0] = "  * * *  ";
        tdb[1] = "         ";
    }
    else if (valeur == 2) {
        tdb[0] = "   * *   ";
        tdb[1] = "         ";
    }
    else if (valeur == 5){
        tdb[0] = "  * * *  ";
        tdb[1] = "   * *   ";
    }
    else if (valeur == 1){
        tdb[0] = "    *    ";
        tdb[1] = "         ";
    }
    return tdb;
}