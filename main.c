#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){
    printf("\x1b[2J\x1b[H");
    int nbJoueurs;
    int nbCartes;
    reglages(&nbJoueurs, &nbCartes);
    Joueur* tblJoueurs = creerTblJoueurs(nbJoueurs);
    int nouvellePartie;
    char* reponseUtilisateur = malloc(100 * sizeof(char));

    do{
        lancerPartie(tblJoueurs, nbJoueurs, nbCartes);
        
        do{
            printf("Voulez-vous relancer une manche ? (y/n) ");
            scanf("%s", reponseUtilisateur);
            effacerBuffer();
        } while (strcmp(reponseUtilisateur, "y") && strcmp(reponseUtilisateur, "n"));
        nouvellePartie = !strcmp(reponseUtilisateur, "y");
    } while (nouvellePartie);

    return 0;
}