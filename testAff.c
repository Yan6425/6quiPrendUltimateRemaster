#include <stdio.h>
#include <stdlib.h>

typedef struct Carte{
    int numero;     //numéro carte de 1 à 104
    int valeur;     //nombre tête de boeuf de 1 à 7
} Carte;

typedef struct Noeud{
    Carte carte;
    Noeud* suivant;
} Noeud;

Carte creerCarte(int numero){
    Carte carte;
    carte.numero = numero;
    if (carte.numero == 55){
        carte.valeur=7;
    }
    else if (carte.numero % 10 == 0){
        carte.valeur=3;
    }
    else if (carte.numero % 5 == 0){
        carte.valeur=2;
    }
    else if (carte.numero % 10 == 0){
        carte.valeur=5;
    }
    else carte.valeur=1;
    
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


void affCarte(Carte carte){
    char** tdb = creerTdb(carte.valeur);
printf(" _________\n"
"|         |\n"
"|%s|\n"
"|%s|\n"
"|         |\n"
"|   %3d   |\n"
"|         |\n"
" ‾‾‾‾‾‾‾‾‾ \n", tdb[0], tdb[1], carte.numero); 
}

int main(){
    Carte carte = creerCarte(55);
    affCarte(carte);

    return 0;
}