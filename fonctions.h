#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points
Joueur creerJoueur(char* nom);
typedef struct Carte Carte; // sert à modéliser une carte
Carte creerCarte(int numero);
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 
void ajouterNoeud(Noeud** liste, Carte carte);
Noeud* extraireNoeud(Noeud** liste, int index);

void sixQuiPrend();
void reglages();// sert à parametrer le jeu
void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
void creerTblJoueurs(int nbJoueurs);
int distribution(Carte** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
Noeud* melangerCartes(int nbCartes);
int distribuerMain();
int choixCarte();
int triCarte();
int comparaisons();
int distributionPts();

#endif