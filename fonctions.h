#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points et sa main
Joueur creerJoueur(char* nom);// cree un joueur avec un nom, une main et un nombre de carte
typedef struct Carte Carte; // sert à modéliser une carte
Carte creerCarte(int numero);//cree une carte avec son numéro et sa valeur (nb de taureau)
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 
void insererNoeud(Noeud** liste, Carte carte, int index);
Noeud* extraireNoeud(Noeud** liste, int index);

void sixQuiPrend();//ratio
void reglages();// sert à parametrer le jeu
void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes);//mets en place le plateau et la distribution
Joueur* creerTblJoueurs(int nbJoueurs);//rassemble tous les joueurs dans un tableau
int distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
void ajouterNoeud(Noeud** liste, Carte carte);
Noeud* melangerCartes(int nbCartes);
Carte* distribuerMain(Noeud** paquet);//distribue les mains aux joueurs
int choixCarte(Joueur joueur, int nbCartes);//le joueur choisi parmis ses 10 cartes en main
int triCarte();
int comparaisons();
int distributionPts(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes);

#endif
