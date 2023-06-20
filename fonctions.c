#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
} Noeud;



void insererNoeud(Noeud** liste, Carte carte, int index){
    for (int i = 0; i < index; i++){
        (*liste)->tailleListe++;
        liste = &((*liste)->suivant);
    }
    Noeud* noeud = malloc(sizeof(Noeud));// Allocation de mémoire pour créer un nouveau noeud
    
    noeud->carte = carte;

    if (*liste != NULL){// Si la liste n'est pas vide, on définit la taille du nouveau noeud à la taille du noeud précédent +1
        
        noeud->tailleListe = (*liste)->tailleListe + 1;
    }
    else { //Sinon on definit la taille du noeud à 1
        noeud->tailleListe = 1;
    }

    noeud->suivant = *liste;
    *liste = noeud;
}


void triInsertion(Noeud** liste, Carte carte){
    // Vérifie si la liste est vide ou si la carte doit être insérée avant le premier élément de la liste
    if (*liste == NULL || (*liste)->carte.numero > carte.numero) {  
        // Appelle la fonction insererNoeud pour insérer la carte au début de la liste
        insererNoeud(liste, carte, 0);
    }
    else {
        (*liste)->tailleListe++;
        // Appelle récursivement triInsertion avec le pointeur vers le prochain élément de la liste et la carte à insérer
        triInsertion(&((*liste)->suivant), carte);
    }
}


Carte extraireNoeud(Noeud** liste, int index){
    for (int i = 0; i < index; i++){
        *liste.tailleListe--;
        liste = &((*liste)->suivant);
    }
    
    // Le pointeur noeud pointe vers le noeud à extraire
    Noeud* noeud = *liste;
    
    // Le pointeur de liste est mis à jour pour pointer vers le noeud suivant, sautant ainsi le noeud à extraire
    
    Carte carte = (*liste)->carte;
    
    // Le pointeur de liste est mis à jour pour pointer vers le noeud suivant, sautant ainsi le noeud à extraire
    *liste = (*liste)->suivant;
    
    // La référence suivante du noeud extrait est définie comme NULL pour le détacher de la liste
    noeud->suivant = NULL;
    
    // La taille du noeud extrait est réinitialisée à 1
    noeud->tailleListe = 1;
    return noeud;
}


void affListe(Noeud* liste){
    //Si le noeud actuel a un noeud suivant on fait un appel récursif pour afficher les noeuds suivants
    if (liste->suivant != NULL){
        affListe(liste->suivant);
    }

    if (liste->suivant == NULL){//Si le noeud est le dernier noeud de la liste on fait un retour à la ligne 
        printf("\n");
    }
    
    // Affiche les informations du noeud actuel (carte.numero, carte.valeur, tailleListe)
    printf("noeud.carte.numero = %d, noeud.carte.valeur = %d, noeud.tailleListe = %d\n", liste->carte.numero, liste->carte.valeur, liste->tailleListe);
}




void reglages(){
}


void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes){
    Noeud** plateau = malloc(4 * sizeof(malloc(sizeof(Noeud))));      //initialisation du plateau

    distribution(plateau, tblJoueurs, nbJoueurs, nbCartes);
    
    for (int i = 0; i < 10; i++){
        affPrincipal(plateau, tblJoueurs, nbJoueurs);
        tailleMain = 10 - i;
        Noeud* listeAttente = NULL;
        
        for (int j = 0; j < nbJoueurs; j++){
            Joueur joueur = tblJoueurs[i];
            printf("%s appuie sur entrée quand tu es prêt à jouer.", joueur.nom);
            fflush(stdout);  // Vide le tampon de sortie pour afficher le message immédiatement
            getchar();  // Attente de l'appui sur la touche Entrée
            affPrincipal(plateau, tblJoueurs, nbJoueurs);
            affMain(joueur.main, tailleMain);
            triInsertion(&listeAttente, choixCarte(&joueur, tailleMain));
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
        insererNoeud(&(plateau[i]), extraireNoeud(&paquet, 0), 0);
    }
    for (int i = 0; i < nbJoueurs; i++){//Distribu les cartes aux joueurs
        tblJoueurs[i].main = creerMain(&paquet);
    }
}

Noeud* melangerCartes(int nbCartes) {
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires
    // Allouer de la mémoire pour le paquet et les cartes
    Noeud* paquet = (Noeud*)malloc(sizeof(Noeud));
    Carte* tblCartes = malloc(nbCartes * sizeof(Carte));
    int iTmp;
    Carte carteEchange;
    // Créer un tableau de cartes avec des valeurs de 1 à nbCartes
    for (int i = 1; i <= nbCartes; i++){
        tblCartes[i] = creerCarte(i);
    }
    // Mélanger les cartes
    for (int i = 0; i < nbCartes; i++){
        // Générer un indice aléatoire
        iTmp = rand() % nbCartes;
        // Échanger la carte courante avec la carte à l'indice aléatoire
        carteEchange = tblCartes[iTmp];
        tblCartes[iTmp] = tblCartes[i];
        tblCartes[i] = carteEchange;
    }
    // Insérer les cartes mélangées dans le paquet sous forme de nœuds de liste chaînée
    for (int i = 0; i < nbCartes; i++){
        insererNoeud(&paquet, tblCartes[i], 0);
    }
    return paquet; // Retourner le paquet mélangé
}

Carte* creerMain(Noeud** paquet) {
    Carte* main = malloc(10 * sizeof(Carte)); // Allouer de la mémoire pour la main qui contiendra 10 cartes
    Noeud** cartesTriees = malloc(sizeof(Noeud*));  // Allouer de la mémoire pour cartesTriees
    *cartesTriees = NULL;  // Initialiser cartesTriees à NULL
    // Extraire les 10 premières cartes du paquet et les trier en utilisant l'algorithme de tri par insertion
    for (int i = 0; i < 10; i++) {
        triInsertion(cartesTriees, extraireNoeud(paquet, 0), NULL);
    }
    // Extraire les cartes triées dans la main
    for (int i = 0; i < 10; i++) {
        main[i] = extraireNoeud(cartesTriees, 0);
    }
    return main; // Retourner la main créée
}

Carte choixCarte(Joueur* joueur, int nbCartes) {
    Carte carte;
    Carte* tabTmp = malloc((nbCartes - 1) * sizeof(Carte)); // Allouer de la mémoire pour le tableau temporaire
    if (nbCartes < 1) {
        int reponseJoueur;
        int j = 0;
        // Demander au joueur quelle carte il souhaite jouer
        do {
            printf("%s, quelle carte voulez-vous jouer ? ", joueur->nom);
            scanf("%d", &reponseJoueur);
        } while (reponseJoueur < 1 || reponseJoueur > nbCartes); // Vérifier que le joueur entre un nombre correct
        // Copier les cartes restantes dans le tableau temporaire
        for (int i = 0; i < nbCartes; i++) {
            if (i != reponseJoueur - 1) {
                tabTmp[j] = joueur->main[i];
                j++;
            }
        }
        carte = joueur->main[reponseJoueur - 1]; // Stocker la carte choisie
    } else {
        carte = joueur->main[0]; // S'il n'y a qu'une seule carte, la choisir directement
    }
    free(joueur->main); // Libérer la mémoire occupée par l'ancien tableau de cartes
    joueur->main = realloc(joueur->main, (nbCartes - 1) * sizeof(Carte)); // Réallouer de la mémoire pour le nouveau tableau de cartes
    joueur->main = tabTmp; // Affecter le tableau temporaire au tableau de cartes du joueur
    free(tabTmp); // Libérer la mémoire occupée par le tableau temporaire
    return carte; // Retourner la carte choisie
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
    // Allocation dynamique du tableau de pointeurs de chaînes de caractères pour stocker les lignes d'affichage des cartes
    char** strCartes = malloc(8 * sizeof(char*));
    // Boucle pour initialiser chaque élément du tableau strCartes
    for (int i = 0; i < 8; i++) {
        // Allocation dynamique de mémoire pour chaque ligne en fonction du nombre de cartes
        printf("\n");
        strCartes[i] = malloc(20 + 13 * nbCartes * sizeof(char));      
        // Utilisation de sprintf pour initialiser chaque ligne avec des espaces vides
        sprintf(strCartes[i], "%*s", 20, "");
    }
    // Boucle pour concaténer les informations de chaque carte à chaque ligne d'affichage
    for (int i = 0; i < nbCartes; i++){
        catStrCartes(strCartes, main[i]);
    }
    // Boucle pour afficher chaque ligne d'affichage des cartes
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


void affLigne(Noeud** ligne){
    // Calcul de la taille de la ligne en fonction du nombre de cartes dans la liste de noeuds
    int tailleLigne = 13 * (*ligne)->tailleListe;
    // Allocation dynamique du tableau de pointeurs de chaînes de caractères pour stocker les lignes d'affichage des cartes
    char** strCartes = malloc(8 * sizeof(char*));
    // Boucle pour allouer dynamiquement de la mémoire pour chaque ligne d'affichage
    for (int i = 0; i < 8; i++) {
        strCartes[i] = malloc(tailleLigne * sizeof(char));
    }
    // Appel de la fonction remplirLigne pour remplir les lignes d'affichage avec les informations des cartes
    remplirLigne(ligne, strCartes);
    // Boucle pour afficher chaque ligne d'affichage des cartes
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < tailleLigne; j++){
            // Vérification si on atteint la position 65, qui correspond à la position où une carte doit être mise en rouge
            if (j == 65){
                printf("\x1b[31m"); //Afficher le texte en rouge
            }
            printf("%c", strCartes[i][j]); // Affichage du caractère correspondant à la position (i, j) de la ligne
        }    
        // Vérification si la taille de la ligne dépasse 65, afin de réinitialiser le format de couleur à la normale
        if (tailleLigne > 65){
            printf("\x1b[0m"); // Réinitialisation du format de couleur
        }
        printf("\n"); // Saut de ligne après l'affichage de la ligne
    }
}


void remplirLigne(Noeud* ligne, char** strCartes){
    if (ligne->suivant != NULL){
        remplirLigne(&(ligne->suivant), strCartes);
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