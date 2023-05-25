#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points
typedef struct Carte Carte; // sert à modéliser une carte
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 

void _6QuiPrend();
int lancerPartie();
int distribution();
int choixCarte();
int comparaisons();
int distributionPts();

#endif