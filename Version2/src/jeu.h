#ifndef _JEU_H
#define _JEU_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_CARACTERES 15
#define NB_MANCHES 3
#define NB_POINTS 40
#define NB_PERMUT 200
#define NB_CARTES 40

typedef enum{
  AS=1, DEUX=2, TROIS=3, QUATRE=4, CINQ=5, SIX=6, SEPT=7, DIX=8, VALET=9, ROI=10
}Valeur;

typedef enum{
  PIECE = 0, COUPE, EPEE, MASSUE
}Couleur;

typedef enum{
  GRAND = 0, PETIT, PAIRE, JEU, FAUXJEU
}Gppj;

typedef enum{
  EQUIPE1, EQUIPE2, AUCUN, NOJOUEUR
}Gagnant;

typedef struct{
  Valeur valeur;
  Couleur couleur;
}Carte;

typedef struct{
  Carte carte[NB_CARTES];
  int curseur;
  int cartes_jetees;
  int debut;
  int fin;
}Paquet;

typedef struct{
  char nom[MAX_CARACTERES];
  Carte main[4];
  int num_joueur;
  bool IA;
}Joueur;


typedef struct{
  Gppj phase;
  int mise;
  Gagnant gagnant;
}Phase;

typedef struct{
  Joueur joueurs[4];
  int score[2];
  int manche[2];
  Phase phase[4];
  int nb_tours;
  Paquet paquet;
}Partie;

int indice_tableau(int tab[], int val, int n);

void init_rand();
void init_paquet(Partie *partie);
void init_joueur(SDL_Surface *ecran, Partie *partie);
void init_phase(Partie *partie);
void init_score(Partie *partie, SDL_Surface *ecran);
void init_tab_joueur(bool tab[]);
Partie *init_partie(SDL_Surface *ecran);

bool est_finie_partie(Partie *partie);
bool est_finie_manche(Partie *partie);


void melange_paquet_debut(Partie *partie);
void echange_carte(Carte *carte1, Carte *carte2);
void tri_main(Partie *partie, int i_joueur);
void tri_toutes_mains(Partie *partie);
void distribution_debut(Partie *partie, SDL_Surface *ecran);


bool est_mus(SDL_Surface *ecran, SDL_Rect tab[], Partie *partie);
int nb_true(bool cartes[4]);
void melange_paquet_mus(Partie *partie);
void distribution_mus(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[]);


void tab_pair(Partie * partie, bool tab_joueur[]);
int compte_jeu(Joueur * joueur);
void tab_jeu(Partie * partie, bool tab_joueur[]);
bool est_fini_tour(int mise_en_cours[]);
void compte_point_phase(Partie *partie, Phase *phase, int mise_en_cours[], int dernier_joueur);
int jouer(SDL_Surface *ecran, SDL_Rect tab[], Partie *partie, Phase *phase, bool tab_joueur[]);


int meilleur_grand_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku);
Gagnant meilleur_grand(Partie * partie);
int meilleur_petit_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku);
Gagnant meilleur_petit(Partie * partie);
int pair(Joueur j1);
bool brelan(Joueur j1);
bool double_pair(Joueur j1);
int combinaison_pair(Joueur j);
int meilleur_pair_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku);
Gagnant meilleur_pair(Partie * partie);
int meilleur_jeu_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku);
Gagnant meilleur_jeu(Partie * partie);
int meilleur_fauxjeu_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku);
Gagnant meilleur_fauxjeu(Partie *partie);
int point_pair(Partie *partie, int gagnant);
int point_jeu(Partie *partie, int gagnant);
int phase_de_jeu(SDL_Surface *ecran, Partie *partie, SDL_Rect carte_graphique[]);
void compte_point(SDL_Surface *ecran, SDL_Rect carte_graphique[], Partie *partie);

void jeu(SDL_Surface * ecran);

#endif //jeu.h
