#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    Joueur* tblJoueurs = creerTblJoueurs(2);

    lancerPartie(tblJoueurs, 2, 104);

    return 0;
}