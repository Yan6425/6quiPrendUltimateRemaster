#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Carte Carte; // sert à modéliser une carte
Carte creerCarte(int numero);//cree une carte avec son numéro et sa valeur (nb de taureau)
typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points et sa main
Joueur creerJoueur(char* nom);// cree un joueur avec un nom, une main et un nombre de carte
Joueur* creerTblJoueurs(int nbJoueurs);//rassemble tous les joueurs dans un tableau
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 
void insererNoeud(Noeud** liste, Carte carte, int index);
Noeud* extraireNoeud(Noeud** liste, int index);
void affListe(Noeud* liste);


void reglages();// sert à parametrer le jeu
void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes);//mets en place le plateau et la distribution
void distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
Noeud* melangerCartes(int nbCartes);
Carte* creerMain(Noeud** paquet);
void triInsertion(Noeud** liste, Noeud* nouvNoeud);
Carte choixCarte(Joueur* joueur, int nbCartes);//le joueur choisi parmis ses 10 cartes en main
void comparaisons();
void distributionPts(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
void affPlateau(Noeud** plateau);
void affMain(Carte* main, int nbCartes);
void affLigne(Noeud** ligne);
void remplirLigne(Noeud** ligne, char** strCartes);
void catStrCartes(char** strCartes, Carte carte);
char* stringNum(int numero);
char** strValeur(int valeur);

#endif