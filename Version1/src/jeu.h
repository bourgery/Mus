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

Partie *init_partie(SDL_Surface *ecran);
void init_rand();
void melange_paquet_debut(Partie *partie);
void distribution_debut(Partie *partie, SDL_Surface *ecran);
bool est_mus_equipe(Partie *partie, int equipe);
void melange_paquet_mus(Partie *partie);
void distribution_mus(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[]);
bool est_fini_tour_grand_petit(int mise_en_cours[]);
void compte_point_phase(Partie *partie, Phase *phase, int mise_en_cours[], int dernier_joueur);
int jouer(SDL_Surface *ecran, SDL_Rect tab[], Partie *partie, Phase *phase, bool tab_joueur[]);
void jeu(SDL_Surface *ecran);

#endif //jeu.h
