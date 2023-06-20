#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


typedef struct Carte{
    int numero;     //numéro carte de 1 à 104
    int valeur;     //nombre tête de boeuf de 1 à 7
    Joueur* joueur;
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
    else if (carte.numero % 11 == 0){
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


typedef struct Noeud{   //structure avec la carte, la taille de la liste associée à ce nœud
    Carte carte;            
    int tailleListe;        
    struct Noeud* suivant; 
} Noeud;


void insererNoeud(Noeud** liste, Carte carte, int index) {
    for (int i = 0; i < index; i++) {
        (*liste)->tailleListe++;  // Incrémente la taille de la liste actuelle
        liste = &((*liste)->suivant);
    }
    
    Noeud* noeud = malloc(sizeof(Noeud));  // Alloue de la mémoire pour un nouveau nœud
    noeud->carte = carte;
    
    if (*liste != NULL) {
        noeud->tailleListe = (*liste)->tailleListe + 1;  // Ajoute 1 à la taille de la liste si elle n'est pas vide
    } else {
        noeud->tailleListe = 1; 
    }
    
    noeud->suivant = *liste; 
    *liste = noeud;  // Met à jour le pointeur de la liste pour pointer vers le nouveau nœud
}


void triInsertion(Noeud** liste, Carte carte) {
    if (*liste == NULL || (*liste)->carte.numero > carte.numero) {
        insererNoeud(liste, carte, 0);  // Insère la carte au début de la liste si la liste est vide ou si la carte doit être placée avant la première carte existante
    } else {
        (*liste)->tailleListe++;
        triInsertion(&((*liste)->suivant), carte); 
    }
}



Carte extraireNoeud(Noeud** liste, int index) {
    for (int i = 0; i < index; i++) {
        (*liste)->tailleListe--;  // Décrémente la taille de la liste actuelle
        liste = &((*liste)->suivant);  
    }
    
    Carte carte = (*liste)->carte;  // Récupère la carte du nœud à extraire
    *liste = (*liste)->suivant; 
    
    return carte;
}


void affListe(Noeud* liste) {
    if (liste->suivant != NULL) {
        affListe(liste->suivant);  // Récursivement appelle la fonction pour le prochain nœud dans la liste
    }
    
    if (liste->suivant == NULL) {
        printf("\n");  // Retour à la ligne une fois arrivé au dernier nœud de la liste
    }
    
    printf("noeud.carte.numero = %d, noeud.carte.valeur = %d, noeud.tailleListe = %d\n", liste->carte.numero, liste->carte.valeur, liste->tailleListe);
    
}



void reglages(int* nbJoueurs, int* nbCartes) {
    int reponse1;
    do {
        printf("Combien de joueurs êtes-vous ? (jouable de 2 à 10 joueurs) ");
        scanf("%d", &reponse1);
        effacerBuffer(); 
    } while (reponse1 < 2 || reponse1 > 10);
    
    *nbJoueurs = reponse1;  // Met à jour le nombre de joueurs avec la réponse fournie
    
    char* reponse2 = malloc(100 * sizeof(char));  // Alloue de la mémoire pour stocker la réponse
    
    do {
        printf("Voulez-vous jouer avec le nombre maximum de cartes ? (y/n) ");
        scanf("%s", reponse2);
        effacerBuffer();
    } while (strcmp(reponse2, "y") && strcmp(reponse2, "n"));
    
    if (!strcmp(reponse2, "y")) {
        *nbCartes = 104;  // Met à jour le nombre de cartes avec 104 si la réponse est "y"
        printf("%d", strcmp(reponse2, "y"));
    } else {
        *nbCartes = 4 + *nbJoueurs * 10;  // Calcule le nombre de cartes en fonction du nombre de joueurs si la réponse est "n"
    }
    
    printf("Vous jouerez avec %d cartes sur 104.\n", *nbCartes);  // Affiche le nombre de cartes sélectionné
}



void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud** plateau = malloc(4 * sizeof(malloc(sizeof(Noeud))));      //initialisation du plateau

    distribution(plateau, tblJoueurs, nbJoueurs, nbCartes);  // Distribue les cartes aux joueurs et initialise le plateau

    for (int i = 0; i < 10; i++){
        int tailleMain = 10 - i;
        Noeud* listeAttente = NULL;
        
        for (int j = 0; j < nbJoueurs; j++){
            affPrincipal(plateau, tblJoueurs, nbJoueurs);
            Joueur* joueur = &(tblJoueurs[j]);
            printf("%s appuie sur entrée quand tu es prêt à jouer.", joueur->nom);  
            getchar();
            effacerBuffer();
            
            affPrincipal(plateau, tblJoueurs, nbJoueurs);  // Affiche à nouveau l'état actuel du plateau
            affMain(joueur->main, tailleMain);  // Affiche la main du joueur
            triInsertion(&listeAttente, choixCarte(joueur, tailleMain));  // Trie et insère la carte choisie par le joueur dans la liste d'attente
        }
        
        for (int j = 0; j < nbJoueurs; j++){
            affPrincipal(plateau, tblJoueurs, nbJoueurs);  // Affiche l'état actuel du plateau
            affLstAttente(listeAttente, nbJoueurs);
            nettoyerPlateau(plateau); 
            placerCarte(plateau, extraireNoeud(&listeAttente, 0));  // Place la première carte de la liste d'attente sur le plateau
            calcScore(plateau);
            sleep(1);  // Attend 1 seconde avant de continuer
        }
    }
    affPrincipal(plateau, tblJoueurs, nbJoueurs);  // Affiche l'état final du plateau après 10 tours de jeu
}


void effacerBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud* paquet = melangerCartes(nbCartes);       //création du paquets de cartes
    for (int i = 0; i < 4; i++){
        insererNoeud(&(plateau[i]), extraireNoeud(&paquet, 0), 0);
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
        insererNoeud(&paquet, tblCartes[i], 0);
    }
    return paquet;
}


Carte* creerMain(Noeud** paquet) {
    Carte* main = malloc(10 * sizeof(Carte));
    Noeud** cartesTriees = malloc(sizeof(Noeud*));  // Allouer de la mémoire pour cartesTriees
    *cartesTriees = NULL;  // Initialiser cartesTriees à NULL
    for (int i = 0; i < 10; i++) {
        triInsertion(cartesTriees, extraireNoeud(paquet, 0));
    }
    for (int i = 0; i < 10; i++) {
        main[i] = extraireNoeud(cartesTriees, 0);
    }
    return main;
}


Carte choixCarte (Joueur* joueur, int nbCartes){
    Carte carte;
    int reponseJoueur;
    do {
        printf("%s, quelle carte veux-tu jouer ? ", joueur->nom);
        scanf("%d", &reponseJoueur);
        effacerBuffer();
    } while (reponseJoueur < 1 || reponseJoueur > nbCartes);     //test pour s'assurer que le joueur entre bien un nombre correct
    carte = joueur->main[reponseJoueur - 1];
    reduireMain(joueur->main, reponseJoueur, nbCartes);
    carte.joueur = joueur;

    return carte;
}


void reduireMain(Carte* main, int reponseJoueur, int nbCartes){
    for (int i = reponseJoueur; i < nbCartes; i++){
        main[i-1] = main[i]; 
    }
    main = realloc(main, (nbCartes - 1) * sizeof(Carte));
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
    int iMax = 0;
    for (int i = 1; i <= 4; i++){
        if (plateau[i - 1]->carte.numero < carte.numero && (iMax == 0 || plateau[iMax - 1]->carte.numero < plateau[i - 1]->carte.numero)){
            iMax = i;
        }
    }
    if (!iMax){
        iMax = choixLigne(carte.joueur);
        carte.joueur->score += scoreListe(plateau[iMax - 1]);
        plateau[iMax - 1]->carte = carte;
        plateau[iMax - 1]->suivant = NULL;
        plateau[iMax - 1]->tailleListe = 1;
    } else insererNoeud(&(plateau[iMax - 1]), carte, 0);
}


int choixLigne(Joueur* joueur){
    int choix;
    do {
        printf("%s, sur quelle colonne veux-tu jouer ? ", joueur->nom);
        scanf("%d", &choix);
        effacerBuffer();
    } while (choix < 1 || choix > 4);
    return choix;
}


void calcScore(Noeud** plateau){
    for (int i = 0; i < 4; i++){
        if (plateau[i]->tailleListe > 5){
            plateau[i]->carte.joueur->score += scoreListe(plateau[i]);
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
    printf("                    ");
    for (int i = 1; i <= nbCartes; i++){
        printf("    %2d       ", i);
    }
    printf("\n");
}


void affLstAttente(Noeud* listeAttente, int nbJoueurs){
    int tailleLigne = 20 + 13 * nbJoueurs;
    char** strCartes = malloc(8 * sizeof(char*));
    for (int i = 0; i < 8; i++){
        printf("\n");
        strCartes[i] = malloc(tailleLigne * sizeof(char));
    }
    remplirStrAttente(listeAttente, strCartes);
    for (int i = 0; i < 8; i++){
        printf("%s\n", strCartes[i]);
    }
}


void remplirStrAttente(Noeud* ligne, char** strCartes){
    catStrCartes(strCartes, ligne->carte);
    if (ligne->suivant != NULL){
        remplirLigne(ligne->suivant, strCartes);
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