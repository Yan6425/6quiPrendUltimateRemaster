#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points
typedef struct Carte Carte; // sert à modéliser une carte
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 
void insererNoeud(Noeud** liste, Carte carte, int index);
Noeud* extraireNoeud(Noeud** liste, int index);

void sixQuiPrend();
void creerJoueurs(int nbJoueurs);
Joueur creerJoueur(char* nom);
void reglages();// sert à parametrer le jeu
void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
Joueur* creerTblJoueurs(int nbJoueurs);
int distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
Noeud* melangerCartes(int nbCartes);
Carte* distribuerMain();
int choixCarte();
int triCarte();
int comparaisons();
int distributionPts();

#endif