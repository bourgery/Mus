#ifndef _JEU_IA_H
#define _JEU_IA_H

bool choix_mus_IA(Joueur j, int carte_jetee);
void choix_carte_mus_IA(Joueur j, bool tab[]);

float proba_carte_superieur(Carte c);
float proba_gagner_grand(Joueur j);
float proba_gagner_petit(Joueur j);
float proba_gagner_pair(Partie *partie, Joueur j);
float proba_gagner_jeu(Partie *partie, Joueur j);
float proba_gagner_faux_jeu(Partie *partie, Joueur j);


int phase_mise_IA_grand(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu);
int phase_mise_IA_petit(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu);
int phase_mise_IA_pair(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu);
int phase_mise_IA_jeu(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu);
int phase_mise_IA_faux_jeu(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu);
int phase_de_mise_IA(Partie *partie, Phase *phase, int mise_precedente, int mise_totale, int miseur, int mise_en_jeu);

#endif //jeu_IA.h