#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


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
    int score;
} Joueur;


Joueur creerJoueur(char* nom){              //donne un nom,une main et un nombre de points 
    Joueur joueur;
    joueur.nom = nom;
    joueur.main = malloc(10 * sizeof(Carte));           //initialise la main du joueur
    joueur.score = 0;
    return joueur;
}


Joueur* creerTblJoueurs(int nbJoueurs){             //mise en place d'un tableau dynamique pour rassembler tous les joueurs
    Joueur* tblJoueur = malloc(nbJoueurs * sizeof(Joueur));
    for (int i = 0; i < nbJoueurs; i++){
        char* nom = malloc(100 * sizeof(char));
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
    Joueur* joueur;
} Noeud;


void insererNoeud(Noeud** liste, Carte carte, Joueur* joueur, int index){
    for (int i = 0; i < index; i++){
        (*liste)->tailleListe++;
        liste = &((*liste)->suivant);
    }
    Noeud* noeud = malloc(sizeof(Noeud));
    noeud->carte = carte;
    noeud->joueur = joueur;
    if (*liste != NULL){
        noeud->tailleListe = (*liste)->tailleListe + 1;
    }
    else noeud->tailleListe = 1;
    noeud->suivant = *liste;
    *liste = noeud;
}


void triInsertion(Noeud** liste, Carte carte, Joueur* joueur){
    if (*liste == NULL || (*liste)->carte.numero > carte.numero) {  
        insererNoeud(liste, carte, joueur, 0);
    }
    else {
        (*liste)->tailleListe++;
        triInsertion(&((*liste)->suivant), carte, NULL);
    }
}


Carte extraireNoeud(Noeud** liste, int index){
    for (int i = 0; i < index; i++){
        (*liste)->tailleListe--;
        liste = &((*liste)->suivant);
    }
    Carte carte = (*liste)->carte;
    *liste = (*liste)->suivant;

    return carte;
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


void reglages(){
}


void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud** plateau = malloc(4 * sizeof(malloc(sizeof(Noeud))));      //initialisation du plateau

    distribution(plateau, tblJoueurs, nbJoueurs, nbCartes);
    
    for (int i = 0; i < 10; i++){
        affPrincipal(plateau, tblJoueurs, nbJoueurs);
        int tailleMain = 10 - i;
        Noeud* listeAttente = NULL;
        
        for (int j = 0; j < nbJoueurs; j++){
            Joueur joueur = tblJoueurs[i];
            printf("%s appuie sur entrée quand tu es prêt à jouer.", joueur.nom);
            getchar():
            affPrincipal(plateau, tblJoueurs, nbJoueurs);
            affMain(joueur.main, tailleMain);
            triInsertion(&listeAttente, choixCarte(&joueur, tailleMain), &joueur);
        }

        for (int j = 0; j < nbJoueurs; j++){
            affPrincipal(plateau, tblJoueurs, nbJoueurs);
            affLstAttente(listeAttente, nbJoueurs);
            nettoyerPlateau(plateau);
            placerCarte(plateau, extraireNoeud(&listeAttente, 0));
            calcScore(plateau);
            sleep(0.7);
        }
    }
}


void distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud* paquet = melangerCartes(nbCartes);       //création du paquets de cartes
    for (int i = 0; i < 4; i++){
        insererNoeud(&(plateau[i]), extraireNoeud(&paquet, 0), NULL, 0);
    }
    for (int i = 0; i < nbJoueurs; i++){
        tblJoueurs[i].main = creerMain(&paquet);
    }
}


Noeud* melangerCartes(int nbCartes){
    srand(time(NULL));
    Noeud* paquet = malloc(sizeof(Noeud));
    Carte* tblCartes = malloc(nbCartes * sizeof(Carte));
    int indexEchange;
    Carte carteEchange;
    for (int i = 0; i < nbCartes; i++){
        tblCartes[i] = creerCarte(i + 1);
    }
    for (int i = 0; i < nbCartes; i++){
        indexEchange = rand() % nbCartes;
        carteEchange = tblCartes[indexEchange];
        tblCartes[indexEchange] = tblCartes[i];
        tblCartes[i] = carteEchange;
    }
    for (int i = 0; i < nbCartes; i++){
        insererNoeud(&paquet, tblCartes[i], NULL, 0);
    }
    return paquet;
}


Carte* creerMain(Noeud** paquet) {
    Carte* main = malloc(10 * sizeof(Carte));
    Noeud** cartesTriees = malloc(sizeof(Noeud*));  // Allouer de la mémoire pour cartesTriees
    *cartesTriees = NULL;  // Initialiser cartesTriees à NULL
    for (int i = 0; i < 10; i++) {
        triInsertion(cartesTriees, extraireNoeud(paquet, 0), NULL);
    }
    for (int i = 0; i < 10; i++) {
        main[i] = extraireNoeud(cartesTriees, 0);
    }
    return main;
}


Carte choixCarte (Joueur* joueur, int nbCartes){
    Carte carte;
    Carte* tabTmp = malloc((nbCartes-1) * sizeof(Carte));
    if (nbCartes < 1){
        int reponseJoueur;
        int j=0;
        do {
            printf("%s, quelle carte voulez vous jouer ? ", joueur->nom);
            scanf("%d", &reponseJoueur);
        }while (reponseJoueur<1 || reponseJoueur>nbCartes);     //test pour s'assurer que le joueur entre bien un nombre correct
        for (int i = 0; i < nbCartes; i++){
            if (i != reponseJoueur - 1){
                tabTmp[j] = joueur->main[i];
                j++;
            }
        }
        carte = joueur->main[reponseJoueur - 1];
    } else carte = joueur->main[0];
    free(joueur->main);
    joueur->main = realloc(joueur->main, (nbCartes - 1)*sizeof(Carte));
    joueur->main = tabTmp;
    free(tabTmp);
    return carte;
}


void nettoyerPlateau(Noeud** plateau){
    for (int i = 0; i < 4; i++){
        if (plateau[i]->tailleListe > 5){
            plateau[i]->suivant = NULL;
            plateau[i]->tailleListe = 1;
        }
    }
}


void placerCarte(Noeud** plateau, Carte carte){
    int iMin = 0;
    for (int i = 1; i <= 4; i++){
        if (plateau[i - 1]->carte.numero < carte.numero && (iMin == 0 || plateau[iMin - 1]->carte.numero > plateau[i - 1]->carte.numero)){
            iMin = i;
        }
    }
    insererNoeud(&(plateau[iMin - 1]), carte, NULL, 0);
}


void calcScore(Noeud** plateau){
    for (int i = 0; i < 4; i++){
        if (plateau[i]->tailleListe > 5){
            plateau[i]->joueur->score += scoreListe(plateau[i]);
        }
    }
}


int scoreListe(Noeud* liste){
    int score = liste->carte.valeur;
    if (liste->suivant != NULL){
        score += scoreListe(liste->suivant);
    }
    return score;
}


void affPrincipal(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs){
    printf("\x1b[2J\x1b[H");
    affScores(tblJoueurs, nbJoueurs);
    affPlateau(plateau);
}


void affScores(Joueur* tblJoueurs, int nbJoueurs){
    printf("\x1b[1mSCORES      \x1b[0m");
    for (int i = 0; i < nbJoueurs; i++){
        printf("%s : %d      ", tblJoueurs[i].nom, tblJoueurs[i].score);
    }
    printf("\n\n");
}


void affPlateau(Noeud** plateau){
    for (int i = 0; i < 4; i++){
        affLigne(plateau[i]);
    }
}


void affMain(Carte* main, int nbCartes){
    char** strCartes = malloc(8 * sizeof(char*));
    for (int i = 0; i < 8; i++) {
        printf("\n");
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


void affLstAttente(Noeud* listeAttente, int nbJoueurs){
    int tailleLigne = 13 * nbJoueurs;
    char** strCartes = malloc(8 * sizeof(char*));
    for (int i = 0; i < 8; i++) {
        strCartes[i] = malloc(tailleLigne * sizeof(char));
    }
    remplirLigne(listeAttente, strCartes);
    for (int i = 0; i < 8; i++){
        printf("%s\n", strCartes[i]);
    }
}


void affLigne(Noeud* ligne){
    int tailleLigne = 13 * ligne->tailleListe;
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


void remplirLigne(Noeud* ligne, char** strCartes){
    if (ligne->suivant != NULL){
        remplirLigne(ligne->suivant, strCartes);
    }
    catStrCartes(strCartes, ligne->carte);
}


void catStrCartes(char** strCartes, Carte carte){
    char** str = strValeur(carte.valeur);
    strcat(strCartes[0], " ---------   ");
    strcat(strCartes[1], "|         |  ");
    strcat(strCartes[2], "|"); strcat(strCartes[2], str[0]); strcat(strCartes[2], "|  ");
    strcat(strCartes[3], "|"); strcat(strCartes[3], str[1]); strcat(strCartes[3], "|  ");
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
    char** str = malloc(2 * sizeof(malloc(5 * sizeof(char))));

    if (valeur == 7){
        str[0] = " * * * * ";
        str[1] = "  * * *  ";
    }
    else if (valeur == 3){
        str[0] = "  * * *  ";
        str[1] = "         ";
    }
    else if (valeur == 2) {
        str[0] = "   * *   ";
        str[1] = "         ";
    }
    else if (valeur == 5){
        str[0] = "  * * *  ";
        str[1] = "   * *   ";
    }
    else if (valeur == 1){
        str[0] = "    *    ";
        str[1] = "         ";
    }
    return str;
}