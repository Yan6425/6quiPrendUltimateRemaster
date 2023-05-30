#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points
typedef struct Carte Carte; // sert à modéliser une carte
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 

Joueur* creerTblJoueurs(int nombreJoueurs);
Joueur creerJoueur(char* nom);
void reglages();
void lancerPartie(Joueur* tblJoueurs, int nombreJoueurs);
int lancerManche(Joueur* tblJoueurs, int nombreJoueurs);
int distribution(Joueur* tblJoueurs, int nombreJoueurs);
Noeud* melangerCartes();
void ajouterNoeud(Noeud** liste, Carte carte);
Carte extraireCarte(Noeud** liste, int index);
Carte creerCarte(int numero);
int choixCarte(Joueur joueur);
int comparaisons();
int distributionPts();

#endif