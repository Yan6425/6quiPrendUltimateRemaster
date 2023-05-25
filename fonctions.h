#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points
typedef struct Carte Carte; // sert à modéliser une carte
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 

void 6QuiPrend();
void creerJoueurs(int nbJoueurs);
void reglages();// sert à parametrer le jeu
void jouer();
void _distribution();
void _triMain();
void _choixCarte();
void _triCarte();
void _comparaisons();
void _distributionPts();

#endif