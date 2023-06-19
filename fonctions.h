#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points et sa main
Joueur creerJoueur(char* nom);
typedef struct Carte Carte; // sert à modéliser une carte
Carte creerCarte(int numero);
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 
void insererNoeud(Noeud** liste, Carte carte, int index);
Noeud* extraireNoeud(Noeud** liste, int index);

void sixQuiPrend();
void reglages();// sert à parametrer le jeu
void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
Joueur* creerTblJoueurs(int nbJoueurs);//rassemble tous les joueurs dans un tableau
int distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
Noeud* melangerCartes(int nbCartes);
Carte* distribuerMain();
int choixCarte(Joueur joueur, int nbCartes);
int triCarte();
int comparaisons();
int distributionPts(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes);

#endif
