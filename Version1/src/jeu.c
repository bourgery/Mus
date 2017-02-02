#include "jeu.h"
#include "affichage.h"

int indice_tableau(int tab[], int val, int n) {
  for (int i = 0; i < n; i++)
    if (tab[i] == val)
      return i;
  return -1;
}

void init_paquet(Partie *partie) { //Initialitsation du paquet de carte
  for (int i = 0; i < NB_CARTES; i++) {
    partie->paquet.carte[i].valeur = i % 10 + 1;
    partie->paquet.carte[i].couleur = i / 10;
  }
  partie->paquet.curseur = 0;
  partie->paquet.cartes_jetees = 0;
  partie->paquet.debut = 0;
  partie->paquet.fin = NB_CARTES - 1;
}

void init_joueur(SDL_Surface *ecran, Partie *partie) {
  char nom[4][MAX_CARACTERES];
  for (int i = 0; i < 4; i++)
    nom[i][0] = 0;
  afficher_menu_nom(ecran, nom);
  for (int i = 0; i < 4; i++)
    strcpy(partie->joueurs[i].nom, nom[i]);
}

void init_phase(Partie *partie) {
  for (int i = 0; i < 4; i++) {
    partie->phase[i].phase = i;
    partie->phase[i].mise = 0;
    partie->phase[i].gagnant = AUCUN;
  }
}

void init_score(Partie *partie, SDL_Surface *ecran) {
  partie->score[0] = 0;
  partie->score[1] = 0;
  graphique_mise_a_jour_score(ecran, partie);
  graphique_mise_a_jour_manche(ecran, partie);
}

Partie *init_partie(SDL_Surface *ecran) { //Initialisation de la partie
  Partie *partie = malloc(sizeof(*partie));
  partie->manche[0] = 0;
  partie->manche[1] = 0;
  partie->nb_tours = 0;
  init_paquet(partie);
  init_phase(partie);
  init_joueur(ecran, partie);
  SDL_FillRect(ecran, NULL, COULEUR_FOND);
  SDL_Flip(ecran);
  graphique_init_score(ecran);
  init_score(partie, ecran);
  return partie;
}


bool est_finie_partie(Partie *partie) {
  return (partie->manche[0] == NB_MANCHES || partie->manche[1] == NB_MANCHES);
}

bool est_finie_manche(Partie *partie) {
  if (partie->score[0] >= NB_POINTS) {
    partie->manche[0] ++;
    return true;
  }
  else if (partie->score[1] >= NB_POINTS) {
    partie->manche[1] ++;
    return true;
  }
  else
    return false;
}

void init_rand() {
  srand(time(NULL));
}

void init_tab_joueur(bool tab[]) {
  for (int i = 0; i < 4; i++)
    tab[i] = true;
}

void melange_paquet_debut(Partie *partie) {
  init_paquet(partie);
  Carte tmp;
  int a, b;
  for (int i = 0; i < NB_PERMUT; i ++) {
    a = rand() % NB_CARTES;
    b = rand() % NB_CARTES;
    tmp.valeur = partie->paquet.carte[a].valeur;
    tmp.couleur = partie->paquet.carte[a].couleur;
    partie->paquet.carte[a].valeur = partie->paquet.carte[b].valeur;
    partie->paquet.carte[a].couleur = partie->paquet.carte[b].couleur;
    partie->paquet.carte[b].valeur = tmp.valeur;
    partie->paquet.carte[b].couleur = tmp.couleur;
  }
}

void echange_carte(Carte *carte1, Carte *carte2) {
  Carte* tmp = malloc(sizeof(tmp));
  tmp->valeur = carte1->valeur;
  tmp->couleur = carte1->couleur;
  carte1->valeur = carte2->valeur;
  carte1->couleur = carte2->couleur;
  carte2->valeur = tmp->valeur;
  carte2->couleur = tmp->couleur;
}

void tri_main(Partie *partie, int i_joueur) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3 - i; j++) {
      if (partie->joueurs[i_joueur].main[j].valeur < partie->joueurs[i_joueur].main[j + 1].valeur)
        echange_carte(&partie->joueurs[i_joueur].main[j], &partie->joueurs[i_joueur].main[j + 1]);
    }
  }
}


void tri_toutes_mains(Partie *partie) {
  for (int i = 0; i < 4; i++) {
    tri_main(partie, i);
  }
}

void distribution_debut(Partie *partie, SDL_Surface *ecran) {
  int esku = partie->nb_tours % 4;
  affiche_nom_joueurs(ecran, partie, modulo_4_neg(esku));
  for (int i = 0; i < 4; i++) // parcours les joueurs
    for (int j = 0; j < 4; j++) // parcours les 4 cartes de chaque joueur
      partie->joueurs[(esku + i) % 4].main[j] = partie->paquet.carte[4 * j + i];
  partie->paquet.curseur = 16;
  tri_toutes_mains(partie);
  graphique_distribuer(ecran, esku);
}

bool est_mus(SDL_Surface *ecran, SDL_Rect tab[], Partie *partie) {
  int esku = partie->nb_tours % 4;
  if (esku == 0 || esku == 2)
    return (graphique_choix_mus_equipe(ecran, 0, partie, tab) && graphique_choix_mus_equipe(ecran, 1, partie, tab));
  else
    return (graphique_choix_mus_equipe(ecran, 1, partie, tab) && graphique_choix_mus_equipe(ecran, 0, partie, tab));
}

int nb_true(bool cartes[4]) {
  int s = 0;
  for (int i = 0; i < 4; i++) {
    if (cartes[i])
      s++;
  }
  return s;
}

void melange_paquet_mus(Partie *partie) {
  Carte tmp;
  int a, b;
  for (int i = 0; i < NB_PERMUT; i++) {
    a = rand() % (partie->paquet.cartes_jetees);
    b = rand() % (partie->paquet.cartes_jetees);
    tmp.valeur = partie->paquet.carte[a].valeur;
    tmp.couleur = partie->paquet.carte[a].couleur;
    partie->paquet.carte[a].valeur = partie->paquet.carte[b].valeur;
    partie->paquet.carte[a].couleur = partie->paquet.carte[b].couleur;
    partie->paquet.carte[b].valeur = tmp.valeur;
    partie->paquet.carte[b].couleur = tmp.couleur;
  }
}



void distribution_mus(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[]) {
  int esku = partie->nb_tours % 4;
  for (int i = 0; i < 4; i++) {
    bool cartes[4] = {false, false, false, false};
    enlever_nom_joueurs(ecran);
    affiche_nom_joueurs(ecran, partie, ((4 - esku - i) % 4));
    graphique_choix_carte_mus(ecran, partie, tab, ((esku + i) % 4), cartes); //renvoie un tab de bool (true si la carte est jetee)11
    jeter_carte(ecran, partie, tab, 0, cartes);
    distribuer_carte_manquante(ecran, cartes, 0, ((4 - i - 1) % 4));
    enlever_paquet_esku(ecran, ((4 - i) % 4));
    int nb_jet = nb_true(cartes);

    //mise des cartes jetees au debut du paquet en ecrasant les cartes qui y étaient
    int l = partie->paquet.cartes_jetees;
    for (int m = 0; m < 4; m++) {
      if (cartes[m]) {
        partie->paquet.carte[l] = partie->joueurs[(esku + i) % 4].main[m];
        l++;
      }
    }

    partie->paquet.cartes_jetees = partie->paquet.cartes_jetees + nb_jet;
    if (partie->paquet.curseur + nb_jet <= NB_CARTES) {
      int j = partie->paquet.curseur;
      for (int k = 0; k < 4; k++) {
        if (cartes[k]) {
          (partie->joueurs[(esku + i) % 4]).main[k] = partie->paquet.carte[j];
          j++;
        }
      }
      partie->paquet.curseur = partie->paquet.curseur + nb_jet;
    }
    else {
      int j = partie->paquet.curseur;
      for (int k = 0; k < 4; k++) {
        if (cartes[k] && j < NB_CARTES) {
          (partie->joueurs[(esku + i) % 4]).main[k] = partie->paquet.carte[j];
          j++;
          cartes[k] = false;
        }
      }
      partie->paquet.curseur = 0;
      melange_paquet_mus(partie);//mélange les cartes de l'indice 0 à cartes_jetees-1
      j = 0;
      for (int k = 0; k < 4; k++) {
        if (cartes[k]) {
          (partie->joueurs[(esku + i) % 4]).main[k] = partie->paquet.carte[j];
          j++;
        }
        partie->paquet.curseur = partie->paquet.curseur + j;
      }
    }
  }
  tri_toutes_mains(partie);
  enlever_nom_joueurs(ecran);
  affiche_nom_joueurs(ecran, partie, 4 - esku);
  enlever_carte_jetee(ecran);
}

bool est_fini_tour(int mise_en_cours[]) {
  if (mise_en_cours[1] == 1 || mise_en_cours[1] == -2 || mise_en_cours[1] == -3)
    return true;
  return false;
}

void compte_point_phase(Partie *partie, Phase *phase, int mise_en_cours[], int dernier_joueur) {
  if (mise_en_cours[1] == 1) {
    phase->mise = mise_en_cours[0];
    phase->gagnant = (dernier_joueur) % 2;
    partie->score[dernier_joueur % 2] += mise_en_cours[0];
  }
  else if (mise_en_cours[1] == -2) {
    phase->mise = -2;
    phase->gagnant = AUCUN;
  }
  else if (mise_en_cours[1] == -3) {
    phase->mise = mise_en_cours[0];
    phase->gagnant = AUCUN;
  }
  else if (mise_en_cours[0] == -4)
    return;
  else {
    phase->mise = 1;
    phase->gagnant = AUCUN;
  }
}

int jouer(SDL_Surface *ecran, SDL_Rect tab[], Partie *partie, Phase *phase, bool tab_joueur[]) {
  mise_a_jour_phase_actuel(ecran, phase->phase);
  int mise_en_cours[2] = {0, 0};
  int miseur = partie->nb_tours % 4;
  int mise;
  int compteur = 0;
  bool joueur_dispo = true;
  if (tab_joueur[0] + tab_joueur[1] + tab_joueur[2] + tab_joueur[3] == 0 && phase->phase == 2) {//Aucun joueur
    phase->gagnant = NOJOUEUR;
    phase->mise = 0;
    mise_en_cours[0] = -4;
    joueur_dispo = false;
  }
  if (tab_joueur[0] + tab_joueur[1] + tab_joueur[2] + tab_joueur[3] == 0 && phase->phase == 3) {//Aucun joueur donc faux jeu
    for (int i = 0; i < 4; i++) {
      tab_joueur[i] = true;
    }
    phase->phase = FAUXJEU;
    return jouer(ecran, tab, partie, phase, tab_joueur);
  }
  if (tab_joueur[0] + tab_joueur[1] + tab_joueur[2] + tab_joueur[3] == 1) { //1 joueur
    if (tab_joueur[0] || tab_joueur[2]) {
      phase->gagnant = 0;
      phase->mise = 0;
    }
    if (tab_joueur[1] || tab_joueur[3]) {
      phase->gagnant = 1;
      phase->mise = 0;
    }
    mise_en_cours[0] = -4;
    joueur_dispo = false;
  }
  if (tab_joueur[0] + tab_joueur[1] + tab_joueur[2] + tab_joueur[3] == 2) {
    if (tab_joueur[0] + tab_joueur[2] == 2) {
      phase->gagnant = 0;
      phase->mise = 0;
      mise_en_cours[0] = -4;
      joueur_dispo = false;
    }
    if (tab_joueur[1] + tab_joueur[3] == 2) {
      phase->gagnant = 1;
      phase->mise = 0;
      mise_en_cours[0] = -4;
      joueur_dispo = false;
    }
  }
  while (joueur_dispo && !est_fini_tour(mise_en_cours) && !(mise_en_cours[1] == 0 && miseur == partie->nb_tours % 4 && compteur != 0)) {
    if (tab_joueur[miseur] == 1) {
      mise = graphique_phase_de_mise(ecran, tab, partie, mise_en_cours[1], miseur);
      if (mise > 1) {         //le joueur surenchérit
        mise_en_cours[0] += mise_en_cours[1];
        mise_en_cours[1] = mise;
      }
      else {
        if (mise == -3) {     //le joueur fait idoki
          if (tab_joueur[ (miseur + 2) % 4 ] == 1) {
            mise = graphique_phase_de_mise(ecran, tab, partie, mise_en_cours[1], (miseur + 2) % 4); //on demande à son collègue
            if (mise == -3) {     //son collègue veut aussi idoki
              mise_en_cours[0] += mise_en_cours[1];
              mise_en_cours[1] = -3;
            }
            else {                //son collègue veut surenchérir ou hordago
              mise_en_cours[0] += mise_en_cours[1];
              mise_en_cours[1] = mise;
            }
          }
          else {
            mise_en_cours[0] += mise_en_cours[1];
            mise_en_cours[1] = -3;
          }
        }
        else {
          if (mise == 1) {   //le joueur veut tira
            if (tab_joueur[ (miseur + 2) % 4 ] == 1) {
              mise = graphique_phase_de_mise(ecran, tab, partie, mise_en_cours[1], (miseur + 2) % 4);  //on demande à son collègue
              if (mise == 1) {    //son collègue veut aussi tira
                if (mise_en_cours[0] == 0) {
                  mise_en_cours[0] = 1;
                  mise_en_cours[1] = 1;
                }
                mise_en_cours[1] = mise;
              }
              else {
                if (mise == -3) { //son collègue veut idoki
                  mise_en_cours[0] += mise_en_cours[1];
                  mise_en_cours[1] = -3;
                }
                else if (mise == -2) { //son collègue veut kanta
                  mise_en_cours[1] = mise;
                  return 1;
                }
                else {            //son collègue surenchérit ou hordago
                  mise_en_cours[0] += mise_en_cours[1];
                  mise_en_cours[1] = mise;
                }
              }
            }
            else {
              if (mise_en_cours[0] == 0) {
                mise_en_cours[0] = 1;
                mise_en_cours[1] = 1;
              }
              mise_en_cours[1] = mise;
            }
          }
          else {
            if (mise == -1) { //le joueur veut hordago
              mise_en_cours[0] += mise_en_cours[1];
              mise_en_cours[1] = mise;
            }
            else {
              if (mise == -2) { //le joueur veut kanta
                mise_en_cours[1] = mise;
                return 1;
              }
            }
          }
        }
      }
    }
    if (mise > 1) {
      if (tab_joueur[(miseur + 1) % 4] == false)
        miseur = (miseur + 3) % 4;
      else
        miseur = (miseur + 1) % 4;
    }
    else {
      miseur = (miseur + 1) % 4;
    }
    compteur ++;
  }
  compte_point_phase(partie, phase, mise_en_cours, miseur);
  mise_a_jour_phase_score(ecran, *phase);
  graphique_mise_a_jour_score(ecran, partie);
  return 0;
}



/*graphique_phase_de_mise : 0 paso
  -1 : hordago
  -2 : kanta
  1 : tira
  -3 : idoki
  autres chiffres : 2 a 40
*/


void tab_pair(Partie * partie, bool tab_joueur[]) {
  for (int i = 0; i < 4; i++) {
    tab_joueur[i] = 0;
    for (int j = 0; j < 3; j++) {
      if (partie->joueurs[i].main[j].valeur == partie->joueurs[i].main[j + 1].valeur)
        tab_joueur[i] = 1;
    }
  }
}

int compte_jeu(Joueur * joueur) {
  int compt = 0;
  for (int i = 0; i < 4; i++) {
    if (joueur->main[i].valeur >= 8)
      compt += 10;
    else
      compt += joueur->main[i].valeur;
  }
  return compt;
}

void tab_jeu(Partie * partie, bool tab_joueur[]) {
  for (int i = 0; i < 4; i++) {
    if (compte_jeu(&partie->joueurs[i]) > 30)
      tab_joueur[i] = 1;
    else
      tab_joueur[i] = 0;
  }
}

int meilleur_grand_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku) {
  for (int i = 0; i < 4; i++) {
    if (j1.main[i].valeur > j2.main[i].valeur)
      return 0;
    if (j1.main[i].valeur < j2.main[i].valeur)
      return 2;
  }
  if (esku == joueur1 || esku == (joueur1 - 1) % 4)
    return 0;
  else
    return 2;
}

Gagnant meilleur_grand(Partie * partie) {
  int equipe1 = meilleur_grand_2joueurs(partie->joueurs[0], partie->joueurs[2], 0, 2, partie->nb_tours % 4);
  int equipe2 = 1 + meilleur_grand_2joueurs(partie->joueurs[1], partie->joueurs[3], 1, 3, partie->nb_tours % 4);
  int gagnant = meilleur_grand_2joueurs(partie->joueurs[equipe1], partie->joueurs[equipe2], equipe1, equipe2, partie->nb_tours % 4);
  return (gagnant == 0) ? 0 : 1;
}

int meilleur_petit_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku) {
  for (int i = 3; i >= 0; i--) {
    if (j1.main[i].valeur < j2.main[i].valeur)
      return 0;
    if (j1.main[i].valeur > j2.main[i].valeur)
      return 2;
  }
  if (esku == joueur1 || esku == (joueur1 - 1) % 4)
    return 0;
  else
    return 2;
}

Gagnant meilleur_petit(Partie * partie) {
  int equipe1 = meilleur_petit_2joueurs(partie->joueurs[0], partie->joueurs[2], 0, 2, partie->nb_tours % 4);
  int equipe2 = 1 + meilleur_petit_2joueurs(partie->joueurs[1], partie->joueurs[3], 1, 3, partie->nb_tours % 4);
  int gagnant = meilleur_petit_2joueurs(partie->joueurs[equipe1], partie->joueurs[equipe2], equipe1, equipe2, partie->nb_tours % 4);
  return (gagnant == 0) ? 0 : 1;
}

int pair(Joueur j1) {
  for (int i = 0; i < 3; i++)
    if (j1.main[i].valeur == j1.main[i + 1].valeur)
      return i + 1;
  return 0;
}

bool brelan(Joueur j1) {
  return (j1.main[1].valeur == j1.main[2].valeur && (j1.main[0].valeur == j1.main[1].valeur || j1.main[2].valeur == j1.main[3].valeur));
}

bool double_pair(Joueur j1) {
  return (j1.main[0].valeur == j1.main[1].valeur && j1.main[2].valeur == j1.main[3].valeur);
}

int combinaison_pair(Joueur j) {
  if (double_pair(j))
    return -2;
  if (brelan(j))
    return -1;
  return pair(j);
}

int meilleur_pair_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku) {
  int gagnant_si_esku;
  if (esku == joueur1 || esku == (joueur1 - 1) % 4)
    gagnant_si_esku = 0;
  else
    gagnant_si_esku = 2;
  int player1 = combinaison_pair(j1), player2 = combinaison_pair(j2);
  if (player1 < player2)
    return 0;
  else if (player1 > player2)
    return 2;
  else {
    if (player1 == -2) {
      if (j1.main[0].valeur > j2.main[0].valeur)
        return 0;
      else if (j1.main[0].valeur < j2.main[0].valeur)
        return 2;
      else {
        if (j1.main[2].valeur > j2.main[2].valeur)
          return 0;
        else if (j1.main[2].valeur < j2.main[2].valeur)
          return 2;
        else
          return gagnant_si_esku;
      }
    }
    else if (player1 == -1) {
      if (j1.main[1].valeur > j2.main[1].valeur)
        return 0;
      else if (j1.main[1].valeur < j2.main[1].valeur)
        return 2;
      else
        return gagnant_si_esku;
    }
    else {
      if (j1.main[player1].valeur > j2.main[player2].valeur)
        return 0;
      else if (j1.main[player1].valeur < j2.main[player2].valeur)
        return 2;
      else
        return gagnant_si_esku;
    }
  }
}

Gagnant meilleur_pair(Partie * partie) {
  bool tab_joueur[4];
  tab_pair(partie, tab_joueur);
  int equipe1, equipe2;
  if (tab_joueur[0] + tab_joueur[1] + tab_joueur[2] + tab_joueur[3] == 0)
    return 3;
  if (tab_joueur[0] && tab_joueur[2])
    equipe1 = meilleur_pair_2joueurs(partie->joueurs[0], partie->joueurs[2], 0, 2, partie->nb_tours % 4);
  else if (tab_joueur[0])
    equipe1 = 0;
  else if (tab_joueur[2])
    equipe1 = 2;
  else
    return 1;
  if (tab_joueur[1] && tab_joueur[3])
    equipe2 = meilleur_pair_2joueurs(partie->joueurs[1], partie->joueurs[3], 1, 3, partie->nb_tours % 4);
  else if (tab_joueur[1])
    equipe2 = 1;
  else if (tab_joueur[3])
    equipe2 = 3;
  else
    return 0;
  int gagnant = meilleur_pair_2joueurs(partie->joueurs[equipe1], partie->joueurs[equipe2], equipe1, equipe2, partie->nb_tours % 4);
  return (gagnant == 0) ? 0 : 1;
}

int meilleur_jeu_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku) {
  int points[8] = {31, 32, 40, 37, 36, 35, 34, 33};
  if (indice_tableau(points, compte_jeu(&j1), 8) < indice_tableau(points, compte_jeu(&j2), 8))
    return 0;
  else if (indice_tableau(points, compte_jeu(&j1), 8) > indice_tableau(points, compte_jeu(&j2), 8))
    return 2;
  else {
    if (esku == joueur1 || esku == (joueur1 - 1) % 4)
      return 0;
    else
      return 2;
  }

}

Gagnant meilleur_jeu(Partie * partie) {
  bool tab_joueur[4];
  tab_jeu(partie, tab_joueur);
  int equipe1, equipe2;
  if (tab_joueur[0] && tab_joueur[2])
    equipe1 = meilleur_jeu_2joueurs(partie->joueurs[0], partie->joueurs[2], 0, 2, partie->nb_tours % 4);
  else if (tab_joueur[0])
    equipe1 = 0;
  else if (tab_joueur[2])
    equipe1 = 2;
  else
    return 1;
  if (tab_joueur[1] && tab_joueur[3])
    equipe2 = meilleur_jeu_2joueurs(partie->joueurs[1], partie->joueurs[3], 1, 3, partie->nb_tours % 4);
  else if (tab_joueur[1])
    equipe2 = 1;
  else if (tab_joueur[3])
    equipe2 = 3;
  else
    return 0;
  int gagnant = meilleur_jeu_2joueurs(partie->joueurs[equipe1], partie->joueurs[equipe2], equipe1, equipe2, partie->nb_tours % 4);
  return (gagnant == 0) ? 0 : 1;
}

int meilleur_fauxjeu_2joueurs(Joueur j1, Joueur j2, int joueur1, int joueur2, int esku) {
  int jeu1 = compte_jeu(&j1), jeu2 = compte_jeu(&j2);
  if (jeu1 > jeu2)
    return 0;
  else if (jeu1 < jeu2)
    return 2;
  else {
    if (esku == joueur1 || esku == (joueur1 - 1) % 4)
      return 0;
    else
      return 2;
  }
}

Gagnant meilleur_fauxjeu(Partie *partie) {
  int equipe1 = meilleur_fauxjeu_2joueurs(partie->joueurs[0], partie->joueurs[2], 0, 2, partie->nb_tours % 4);
  int equipe2 = 1 + meilleur_fauxjeu_2joueurs(partie->joueurs[1], partie->joueurs[3], 1, 3, partie->nb_tours % 4);
  int gagnant = meilleur_fauxjeu_2joueurs(partie->joueurs[equipe1], partie->joueurs[equipe2], equipe1, equipe2, partie->nb_tours % 4);
  return (gagnant == 0) ? 0 : 1;
}

int point_pair(Partie *partie, int gagnant) {
  int point = 0;
  if (double_pair(partie->joueurs[gagnant]))
    point += 3;
  else if (brelan(partie->joueurs[gagnant]))
    point += 2;
  else if (pair(partie->joueurs[gagnant]))
    point += 1;
  else
    point += 0;
  if (double_pair(partie->joueurs[gagnant + 2]))
    point += 3;
  else if (brelan(partie->joueurs[gagnant + 2]))
    point += 2;
  else if (pair(partie->joueurs[gagnant + 2]))
    point += 1;
  else
    point += 0;
  return point;
}

int point_jeu(Partie *partie, int gagnant) {
  int point = 0;
  if (compte_jeu(&partie->joueurs[gagnant]) ==  31)
    point += 3;
  else if (compte_jeu(&partie->joueurs[gagnant]) >  31)
    point += 2;
  else
    point += 0;
  if (compte_jeu(&partie->joueurs[gagnant + 2]) ==  31)
    point += 3;
  else if (compte_jeu(&partie->joueurs[gagnant + 2]) >  31)
    point += 2;
  else
    point += 0;
  return point;
}

int phase_de_jeu(SDL_Surface *ecran, Partie *partie, SDL_Rect carte_graphique[]) {
  bool tab_joueur[4];
  init_tab_joueur(tab_joueur);
  if (jouer(ecran, carte_graphique, partie, &partie->phase[0], tab_joueur)) { //Hordago
    if (meilleur_grand(partie) == 0) {
      partie->score[0] = 40;
      partie->manche[0] ++;
    }
    else {
      partie->score[1] = 40;
      partie->manche[1] ++;
    }
    return 1;
  }
  if (partie->score[0] >= 40) {
    partie->score[0] = 40;
    partie->manche[0] ++;
    return 1;
  }
  if (partie->score[1] >= 40) {
    partie->score[1] = 40;
    partie->manche[1] ++;
    return 1;
  }
  if (jouer(ecran, carte_graphique, partie, &partie->phase[1], tab_joueur)) { //Hordago
    if (meilleur_petit(partie) == 0) {
      partie->score[0] = 40;
      partie->manche[0] ++;
    }
    else {
      partie->score[1] = 40;
      partie->manche[1] ++;
    }
    return 1;
  }
  if (partie->score[0] >= 40) {
    partie->score[0] = 40;
    partie->manche[0] ++;
    return 1;
  }
  if (partie->score[1] >= 40) {
    partie->score[1] = 40;
    partie->manche[1] ++;
    return 1;
  }
  tab_pair(partie, tab_joueur);
  message_oui_non(ecran, partie, tab_joueur);
  if (jouer(ecran, carte_graphique, partie, &partie->phase[2], tab_joueur)) { //Hordago
    if (meilleur_pair(partie) == 0) {
      partie->score[0] = 40;
      partie->manche[0] ++;
    }
    else {
      partie->score[1] = 40;
      partie->manche[1] ++;
    }
    return 1;
  }
  if (partie->score[0] >= 40) {
    partie->score[0] = 40;
    partie->manche[0] ++;
    return 1;
  }
  if (partie->score[1] >= 40) {
    partie->score[1] = 40;
    partie->manche[1] ++;
    return 1;
  }
  tab_jeu(partie, tab_joueur);
  message_oui_non(ecran, partie, tab_joueur);
  if (jouer(ecran, carte_graphique, partie, &partie->phase[3], tab_joueur)) { //Hordago
    if (partie->phase[3].phase == JEU) {
      if (meilleur_jeu(partie) == 0) {
        partie->score[0] = 40;
        partie->manche[0] ++;
      }
      else {
        partie->score[1] = 40;
        partie->manche[1] ++;
      }
    }
    else {
      if (meilleur_fauxjeu(partie) == 0) {
        partie->score[0] = 40;
        partie->manche[0] ++;
      }
      else {
        partie->score[1] = 40;
        partie->manche[1] ++;
      }
    }
    return 1;
  }
  if (partie->score[0] >= 40) {
    partie->score[0] = 40;
    partie->manche[0] ++;
    return 1;
  }
  if (partie->score[1] >= 40) {
    partie->score[1] = 40;
    partie->manche[1] ++;
    return 1;
  }
  return 0;
}

void compte_point(SDL_Surface *ecran, SDL_Rect carte_graphique[], Partie *partie) {
  int gagnant;
  if (partie->phase[0].gagnant == 2) { //Aucun gagnant pour l'instant pour le grand
    partie->phase[0].gagnant = meilleur_grand(partie);
    partie->score[meilleur_grand(partie)] += partie->phase[0].mise;
  }
  mise_a_jour_phase_score(ecran, partie->phase[0]);
  if (partie->score[0] >= 40) {
    partie->score[0] = 40;
    return;
  }
  if (partie->score[1] >= 40) {
    partie->score[1] = 40;
    return;
  }
  if (partie->phase[1].gagnant == 2) { //Aucun gagnant pour l'instant pour le petit
    partie->phase[1].gagnant = meilleur_petit(partie);
    partie->score[meilleur_petit(partie)] += partie->phase[1].mise;
  }
  mise_a_jour_phase_score(ecran, partie->phase[1]);
  if (partie->score[0] >= 40) {
    partie->score[0] = 40;
    return;
  }
  if (partie->score[1] >= 40) {
    partie->score[1] = 40;
    return;
  }
  if (partie->phase[2].gagnant != NOJOUEUR) { //Personne a joué
    if (partie->phase[2].gagnant == 2) {
      gagnant = meilleur_pair(partie);
      partie->phase[2].gagnant = gagnant;
      partie->score[gagnant] += partie->phase[2].mise;
      partie->score[gagnant] += point_pair(partie, gagnant);
      partie->phase[2].mise += point_pair(partie, gagnant);
    }
    else {
      partie->score[partie->phase[2].gagnant] += point_pair(partie, partie->phase[2].gagnant);
      partie->phase[2].mise += point_pair(partie, partie->phase[2].gagnant);
    }
  }
  mise_a_jour_phase_score(ecran, partie->phase[2]);
  if (partie->score[0] >= 40) {
    partie->score[0] = 40;
    return;
  }
  if (partie->score[1] >= 40) {
    partie->score[1] = 40;
    return;
  }
  if (partie->phase[3].phase == JEU) {//On a joué au jeu
    if (partie->phase[3].gagnant == 2) {
      gagnant = meilleur_jeu(partie);
      partie->phase[3].gagnant = gagnant;
      partie->score[gagnant] += partie->phase[3].mise;
      partie->score[gagnant] += point_jeu(partie, gagnant);
      partie->phase[3].mise += point_jeu(partie, gagnant);
    }
    else {
      partie->score[partie->phase[3].gagnant] += point_jeu(partie, partie->phase[3].gagnant);
      partie->phase[3].mise += point_jeu(partie, partie->phase[3].gagnant);
    }
  }
  else { //On a joué au faux jeu
    if (partie->phase[3].gagnant == 2) { //Aucun gagnant pour l'instant pour le faux jeu
      partie->phase[3].gagnant = meilleur_fauxjeu(partie);
      partie->score[meilleur_fauxjeu(partie)] += partie->phase[3].mise + 1;//+ 1 pour le point du faux jeu
    }
    else {
      partie->score[partie->phase[3].gagnant] ++;//+1 pour le point du faux jeu
    }
    partie->phase[3].mise ++;
  }
  mise_a_jour_phase_score(ecran, partie->phase[3]);
  if (partie->score[0] >= 40) {
    partie->score[0] = 40;
    return;
  }
  if (partie->score[1] >= 40) {
    partie->score[1] = 40;
    return;
  }
}

void jeu(SDL_Surface * ecran) {
  SDL_Rect carte_graphique[120];
  graphique_init_paquet(carte_graphique);
  Partie *partie = init_partie(ecran);
  int gagnant, hordago;
  while (!est_finie_partie(partie)) {
    init_score(partie, ecran);
    enlever_toutes_les_mains(ecran, partie);
    while (!est_finie_manche(partie)) {
      init_phase(partie);
      melange_paquet_debut(partie);
      distribution_debut(partie, ecran);
      while (est_mus(ecran, carte_graphique, partie)) {
        distribution_mus(ecran, partie, carte_graphique);
      }
      init_score_phase(ecran);
      hordago = phase_de_jeu(ecran, partie, carte_graphique);
      afficher_toutes_les_mains(ecran, partie, carte_graphique);
      enlever_paquet_4_endroit(ecran);
      affiche_paquet_esku(ecran, 0);
      if (hordago) {
        graphique_mise_a_jour_score(ecran, partie);
        partie->nb_tours ++;
        break;
      }
      compte_point(ecran, carte_graphique, partie);
      graphique_mise_a_jour_score(ecran, partie);
      message_fin_tour(ecran);
      partie->nb_tours ++;
      enlever_toutes_les_mains(ecran, partie);
    }
    gagnant = (partie->score[0] == NB_POINTS) ? 1 : 2;
    affiche_gagnant_manche(ecran, gagnant);
  }
  gagnant = (partie->manche[0] == NB_MANCHES) ? 1 : 2;
  affiche_gagnant_partie(ecran, gagnant);
  free(partie);
}
