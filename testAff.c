#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Carte{
    int numero;     //numéro carte de 1 à 104
    int valeur;     //nombre tête de boeuf de 1 à 7
} Carte;



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


void affListe(Noeud* liste){
    if (liste->suivant != NULL){
        affListe(liste->suivant);
    }
    if (liste->suivant == NULL){
        printf("\n");
    }
    printf("noeud.carte.numero = %d, noeud.carte.valeur = %d, noeud.tailleListe = %d\n", liste->carte.numero, liste->carte.valeur, liste->tailleListe);
}


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
    else if (carte.numero % 11 == 0){
        carte.valeur = 5;
    }
    else carte.valeur = 1;
    
    return carte;
}  


char** creerTdb(int valeur){
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


char* stringNum(int numero){
    char* strNum = malloc(4 * sizeof(char));
    sprintf(strNum, "%*s%d%*s", !(numero / 100), "", numero, !(numero / 10), "");

    return strNum;
}


void catStrCartes(char** strCartes, Carte carte){
    char** tdb = creerTdb(carte.valeur);
    strcat(strCartes[0], " ---------   ");
    strcat(strCartes[1], "|         |  ");
    strcat(strCartes[2], "|"); strcat(strCartes[2], tdb[0]); strcat(strCartes[2], "|  ");
    strcat(strCartes[3], "|"); strcat(strCartes[3], tdb[1]); strcat(strCartes[3], "|  ");
    strcat(strCartes[4], "|         |  ");
    strcat(strCartes[5], "|   "); strcat(strCartes[5], stringNum(carte.numero)); strcat(strCartes[5], "   |  ");
    strcat(strCartes[6], "|         |  ");
    strcat(strCartes[7], " ---------   ");
}


void remplirLigne(Noeud** ligne, char** strCartes){
    if ((*ligne)->suivant != NULL){
        remplirLigne(&((*ligne)->suivant), strCartes);
    }
    catStrCartes(strCartes, (*ligne)->carte);
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


void affPlateau(Noeud** plateau){
    for (int i = 0; i < 4; i++){
        affLigne(&(plateau[i]));
    }
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


int main(){
    printf("\x1b[2J\x1b[H");

    Noeud** plateau = (Noeud**)malloc(4 * sizeof(struct Node*));
    int numCartes[4][7] = {{5, 12, 45, 55, 10, 1, 80}, {35, 7}, {30, 12, 33, 104}, {14}};
    int lenTbl[4] = {7, 2, 4, 1};
    for (int i = 0; i < 4; i++){
        Noeud** ligne = &(plateau[i]);
        for (int j = 0; j < lenTbl[i]; j++){
            insererNoeud(ligne, creerCarte(numCartes[i][j]), 0);
        }
    }

    affPlateau(plateau);

    for (int i = 0; i < 8; i++){
        printf("\n");
    }

    Joueur Bob = creerJoueur("Bob");
    int nbCartes = 10;
    for (int i = 0; i < nbCartes; i++){
        Bob.main[i] = creerCarte(numCartes[0][i]);
    }

    affMain(Bob.main, nbCartes);
    
    for (int i = 0; i < 8; i++){
        printf("\n");
    }

    return 0;
}
