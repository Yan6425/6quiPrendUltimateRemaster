#ifndef __fonctions_H_
#define __fonctions_H_

typedef struct Carte Carte; // sert à modéliser une carte
Carte creerCarte(int numero);//cree une carte avec son numéro et sa valeur (nb de taureau)
typedef struct Joueur Joueur; // sert à modéliser un joueur ainsi que son nombre de points et sa main
Joueur creerJoueur(char* nom);// cree un joueur avec un nom, une main et un nombre de carte
Joueur* creerTblJoueurs(int nbJoueurs);//rassemble tous les joueurs dans un tableau
typedef struct Noeud Noeud; // sert a modéliser un noeud d'une liste chainée 
void insererNoeud(Noeud** liste, Carte carte, int index);//Insère un noeud dans une liste chainée
void triInsertion(Noeud** liste, Carte carte);//Permet de trier les cartes grâce au tri par insertion
Carte extraireNoeud(Noeud** liste, int index);//Extrait un noeud spécifique d'une liste chainée
void affListe(Noeud* liste);// Affiche les informations du nœud courant : numéro de carte, valeur de carte et taille de la liste


void reglages(int* nbJoueurs, int* nbCartes);// sert à parametrer le jeu
void lancerPartie(Joueur* tblJoueurs, int nbJoueurs, int nbCartes);//mets en place le plateau et la distribution
void effacerBuffer();//Eviter des problèmes de saisis
void distribution(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs, int nbCartes);
Noeud* melangerCartes(int nbCartes);
Carte* creerMain(Noeud** paquet);
Carte choixCarte(Joueur* joueur, int nbCartes);//le joueur choisi parmis ses 10 cartes en main
void reduireMain(Carte* main, int reponseJoueur, int nbCartes);
void nettoyerPlateau(Noeud** plateau);
void placerCarte(Noeud** plateau, Carte carte);
int choixLigne(Joueur* joueur);
void calcScore(Noeud** plateau);
int scoreListe(Noeud* liste);
void affPrincipal(Noeud** plateau, Joueur* tblJoueurs, int nbJoueurs);
void affScores(Joueur* tblJoueurs, int nbJoueurs);
void affPlateau(Noeud** plateau);
void affMain(Carte* main, int nbCartes);
void affLstAttente(Noeud* listeAttente, int nbJoueurs);
void remplirStrAttente(Noeud* ligne, char** strCartes);
void affLigne(Noeud* ligne);
void remplirLigne(Noeud* ligne, char** strCartes);
void catStrCartes(char** strCartes, Carte carte);
char* stringNum(int numero);
char** strValeur(int valeur);

#endif