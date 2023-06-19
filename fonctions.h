#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points
typedef struct Carte Carte; // sert à modéliser une carte
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 

void sixQuiPrend();
void creerJoueurs(int nbJoueurs);
void reglages();// sert à parametrer le jeu
void jouer();

int _distribution();
Carte creerValeurCarte(int numero);
int _triMain();
int _choixCarte();
int _triCarte();
int _comparaisons();
int _distributionPts();

#endif
