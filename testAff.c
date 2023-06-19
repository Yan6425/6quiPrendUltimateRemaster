#include <stdio.h>
#include <stdlib.h>

typedef struct Carte{
    int numero;     //numéro carte de 1 à 104
    int valeur;     //nombre tête de boeuf de 1 à 7
} Carte;

typedef struct Noeud{
    Carte carte;
    struct Noeud* suivant;
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

char** affCarte(Carte carte){
    char** tdb = creerTdb(carte.valeur);
    char** cartes
printf(" _________\n"
"|         |\n"
"|%s|\n"
"|%s|\n"
"|         |\n"
"|   %3d   |\n"
"|         |\n"
" ‾‾‾‾‾‾‾‾‾ \n", tdb[0], tdb[1], carte.numero); 
}

void remplirLigne(Noeud** ligne, char** cartes, int nbCartes){
    if ((*ligne)->suivant != NULL){
        remplirLigne(&((*ligne)->suivant), cartes, nbCartes - 1);
    }
    char** tdb = creerTdb((*ligne)->carte.valeur);
    cartes[0][(nbCartes - 1 )* 13] = " _________   ";
    cartes[1][(nbCartes - 1 )* 13] = "|         |  ";
    cartes[2][(nbCartes - 1 )* 13] = "|" + tdb[0] + "|  ";
    cartes[3][(nbCartes - 1 )* 13] = "|" + tdb[1] + "|  ";
    cartes[4][(nbCartes - 1 )* 13] = "|         |  ";
    cartes[5][(nbCartes - 1 )* 13] = "|   " + "   |  ";
    cartes[6][(nbCartes - 1 )* 13] = "|         |  ";
    cartes[7][(nbCartes - 1 )* 13] = " ‾‾‾‾‾‾‾‾‾   ";
}

void affLigne(Noeud** ligne){
    int nbCartes = sizeof(numCartes[i]) / sizeof(numCartes[i][0]);
    char** cartes = malloc(8 * sizeof(malloc(13 * nbCartes * sizeof(char))));
    remplirLigne(ligne, cartes, nbCartes);
    for (int i = 0; i < 8; i++){
        printf("%s", cartes[i]);
    }
}

void affPlateau(Noeud** plateau){
    for (int i = 0; i < 4; i++){
        affLigne(&(plateau[i]));
    }
}

int main(){
    Noeud** plateau = malloc(4 * sizeof( (Noeud*)malloc(sizeof(Noeud)) ));
    int numCartes[4][5] = {{5, 12, 45, 68, 19}, {35, 7}, {37, 12, 36, 104}, {14}};
    for (int i = 0; i < 4; i++){
        Noeud* ligne = plateau[i];
        for (int j = 0; j < (sizeof(numCartes[i]) / sizeof(numCartes[i][0])); j++){
            insererNoeud(&ligne, creerCarte(numCartes[i][j]), 0);
        }
    }
    affPlateau(plateau);

    return 0;
}
