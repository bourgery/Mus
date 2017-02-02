#ifndef _AFFICHAGE_H
#define _AFFICHAGE_H

#include "jeu.h"


#define LONGUEUR_CARTE 123
#define LARGEUR_CARTE 80
#define NB_PIXEL_DECALAGE 8
#define COULEUR_FOND SDL_MapRGB(ecran->format, 30, 110, 30)
#define CHOIX_POLICE(x) "ressource/FreeMonoBold.ttf", x


typedef enum {
	BAS = 0, DROITE, HAUT, GAUCHE
} Direction;

int modulo_4_neg(int n);
void pauses(SDL_Surface *ecran);

void afficher_menu_nom(SDL_Surface *ecran, char nom[][MAX_CARACTERES]);
void demander_un_nom(SDL_Surface *ecran, char nom[], SDL_Rect pos);

void affiche_nom_un_joueur(SDL_Surface *ecran, Joueur joueur, Direction d);
void enlever_nom_un_joueur(SDL_Surface *ecran, Direction d);
void affiche_nom_joueurs(SDL_Surface *ecran, Partie *partie, Direction place_j1);
void enlever_nom_joueurs(SDL_Surface *ecran);

void graphique_init_paquet(SDL_Rect tab[]);
void affiche_dos(SDL_Surface *ecran, Direction d, SDL_Rect chem_carte);
void affiche_paquet_esku(SDL_Surface *ecran, Direction esku);
void affiche_paquet(SDL_Surface *ecran, SDL_Rect pos);
void affiche_carte(SDL_Rect tab[], SDL_Rect pos, Carte *carte, SDL_Surface *ecran, Direction d);
void graphique_distribuer_une_carte(SDL_Surface *ecran, Direction d, int nb_carte_distribuer);
void graphique_distribuer(SDL_Surface *ecran, int esku);
void graphique_affiche_main(SDL_Surface *ecran, Carte tab[], SDL_Rect tab_pos[], Direction d);
void graphique_affiche_main_cachee(SDL_Surface *ecran);
void afficher_toutes_les_mains(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[]);
void enlever_toutes_les_mains(SDL_Surface *ecran, Partie *partie);
void enlever_paquet_esku(SDL_Surface *ecran, Direction esku);
void enlever_paquet(SDL_Surface *ecran, SDL_Rect pos);
void enlever_paquet_4_endroit(SDL_Surface *ecran);

bool graphique_choix_mus_joueur(SDL_Surface *ecran);
bool graphique_choix_mus_equipe(SDL_Surface *ecran, int equipe, Partie *partie, SDL_Rect tab[]);
void graphique_lever_baisser_carte(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[], int joueur, int carte, bool lever);
void jeter_carte(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[], Direction d, bool choix_carte[]);
void enlever_carte_jetee(SDL_Surface *ecran);
void distribuer_carte_manquante(SDL_Surface *ecran, bool choix_carte[], Direction d, int esku);
void graphique_choix_carte_mus(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[], int joueur, bool choix_carte[]);

int graphique_phase_de_mise(SDL_Surface *ecran, SDL_Rect tab[], Partie *partie, int mise_precedente, int joueur);
int phase_de_mise_debut(SDL_Surface *ecran, SDL_Surface *carre, SDL_Rect pos_carre);
int phase_de_mise_hordago(SDL_Surface *ecran, SDL_Surface *carre, SDL_Rect pos_carre);
int phase_de_mise_iduki(SDL_Surface *ecran, SDL_Surface *carre, SDL_Rect pos_carre);
int phase_de_mise_surenchir(SDL_Surface *ecran, SDL_Surface *carre, SDL_Rect pos_carre);

void graphique_init_score(SDL_Surface *ecran);
void graphique_mise_a_jour_score(SDL_Surface *ecran, Partie *partie);
void graphique_mise_a_jour_manche(SDL_Surface *ecran, Partie *partie);
void init_score_phase(SDL_Surface *ecran);
void enleve_phase(SDL_Surface *ecran, SDL_Rect pos, SDL_Surface *texte);
void mise_a_jour_phase_actuel(SDL_Surface *ecran, Gppj phase);
void mise_a_jour_phase_score(SDL_Surface *ecran, Phase phase);

void message_joueur_suivant(SDL_Surface *ecran, Partie *partie, int joueur);
void message_fin_tour(SDL_Surface *ecran);
void affiche_message_oui_non(SDL_Surface *ecran, Direction d, bool oui_non);
void enleve_message_oui_non(SDL_Surface *ecran, Direction d);
void message_oui_non(SDL_Surface *ecran, Partie *partie, bool tab_joueur[]);
void affiche_gagnant_manche(SDL_Surface *ecran, int gagnant);
void affiche_gagnant_partie(SDL_Surface *ecran, int gagnant);

#endif //affichage.h
