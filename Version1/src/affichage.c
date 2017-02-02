#include "affichage.h"


////////////////////////////////////////////////////////////////
////
////               Fonction auxiliaire
////
////////////////////////////////////////////////////////////////

/* reverse:  reverse string s in place */
void reverse(char s[]) {
  int i, j;
  char c;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0)  /* record sign */
    n = -n;          /* make n positive */
  i = 0;
  do {       /* generate digits in reverse order */
    s[i++] = n % 10 + '0';   /* get next digit */
  } while ((n /= 10) > 0);     /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

int modulo_4_neg(int n) {
  switch (n) {
  case 0:
    return 0;
  case 1:
    return 3;
  case 2:
    return 2;
  case 3:
    return 1;
  default:
    return -1;
  }
}

int endroit_paquet(int esku, int joueur) {
  if (esku == 0)
    return modulo_4_neg(joueur);
  else if (esku == 1) {
    switch (joueur) {
    case 0:
      return 1;
    case 1:
      return 0;
    case 2:
      return 3;
    case 3:
      return 2;
    }
  }
  else if (esku == 2) {
    switch (joueur) {
    case 0:
      return 2;
    case 1:
      return 1;
    case 2:
      return 0;
    case 3:
      return 3;
    }
  }
  else {
    switch (joueur) {
    case 0:
      return 3;
    case 1:
      return 2;
    case 2:
      return 1;
    case 3:
      return 0;
    }
  }
  return -1;
}

void enleve_ecriture_sur_fond_noir(SDL_Surface *ecran, SDL_Surface *fond, SDL_Rect pos) {
  SDL_SetAlpha(fond, 0, 180);
  SDL_FillRect(fond, NULL, COULEUR_FOND);
  SDL_BlitSurface(fond, NULL, ecran, &pos);
  SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  SDL_SetAlpha(fond, SDL_SRCALPHA, 180);
  SDL_BlitSurface(fond, NULL, ecran, &pos);
  SDL_Flip(ecran);
}

void pauses(SDL_Surface *ecran) {
  int continuer = 1;
  SDL_Event event;
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
      continuer = 0;
      break;
    case SDL_KEYDOWN:
      continuer = 0;
      break;
    }
  }
}

////////////////////////////////////////////////////////////////
////
////              Demande noms des joueurs
////
////////////////////////////////////////////////////////////////

void afficher_menu_nom(SDL_Surface *ecran, char nom[][MAX_CARACTERES]) {
  int continuer = 1;
  SDL_Event event;
  SDL_Surface *texte_j1 = NULL, *texte_j2 = NULL, *texte_j3 = NULL, *texte_j4 = NULL, *fond_noir = NULL, *texte_suivant = NULL;
  SDL_Rect pos_j1, pos_j2, pos_j3, pos_j4, pos_fn1, pos_fn2, pos_fn3, pos_fn4, pos_suivant;
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(30));
  SDL_Color couleurblanche = {255, 255, 255};
  texte_j1 = TTF_RenderText_Blended(police, "Joueur 1 :", couleurblanche);
  texte_j2 = TTF_RenderText_Blended(police, "Joueur 2 :", couleurblanche);
  texte_j3 = TTF_RenderText_Blended(police, "Joueur 3 :", couleurblanche);
  texte_j4 = TTF_RenderText_Blended(police, "Joueur 4 :", couleurblanche);
  TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE);
  texte_suivant = TTF_RenderText_Blended(police, "Suivant", couleurblanche);
  fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, 0.22 * ecran->w, ecran->h / 10, 32, 0, 0, 0, 0);
  SDL_FillRect(fond_noir, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  SDL_SetAlpha(fond_noir, SDL_SRCALPHA, 180);
  pos_j1.x = 0.35 * ecran->w - texte_j1->w / 2;
  pos_j1.y = 2 * ecran->h / 10 - texte_j1->h / 2;
  pos_j2.x = 0.35 * ecran->w - texte_j2->w / 2;
  pos_j2.y = 4 * ecran->h / 10 - texte_j2->h / 2;
  pos_j3.x = 0.35 * ecran->w - texte_j3->w / 2;
  pos_j3.y = 6 * ecran->h / 10 - texte_j3->h / 2;
  pos_j4.x = 0.35 * ecran->w - texte_j4->w / 2;
  pos_j4.y = 8 * ecran->h / 10 - texte_j4->h / 2;
  pos_fn1.x = 0.35 * ecran->w + 0.6 * texte_j1->w;
  pos_fn1.y = 2 * ecran->h / 10 - fond_noir->h / 2;
  pos_fn2.x = 0.35 * ecran->w + 0.6 * texte_j2->w;
  pos_fn2.y = 4 * ecran->h / 10 - fond_noir->h / 2;
  pos_fn3.x = 0.35 * ecran->w + 0.6 * texte_j3->w;
  pos_fn3.y = 6 * ecran->h / 10 - fond_noir->h / 2;
  pos_fn4.x = 0.35 * ecran->w + 0.6 * texte_j4->w;
  pos_fn4.y = 8 * ecran->h / 10 - fond_noir->h / 2;
  pos_suivant.x = pos_fn4.x + fond_noir->w + texte_suivant->w;
  pos_suivant.y = 8 * ecran->h / 10 - texte_suivant->h / 2;
  SDL_BlitSurface(texte_j1, NULL, ecran, &pos_j1);
  SDL_BlitSurface(texte_j2, NULL, ecran, &pos_j2);
  SDL_BlitSurface(texte_j3, NULL, ecran, &pos_j3);
  SDL_BlitSurface(texte_j4, NULL, ecran, &pos_j4);
  SDL_BlitSurface(fond_noir, NULL, ecran, &pos_fn1);
  SDL_BlitSurface(fond_noir, NULL, ecran, &pos_fn2);
  SDL_BlitSurface(fond_noir, NULL, ecran, &pos_fn3);
  SDL_BlitSurface(fond_noir, NULL, ecran, &pos_fn4);
  SDL_BlitSurface(texte_suivant, NULL, ecran, &pos_suivant);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
      if (event.button.x >= (pos_fn1.x) &&
          event.button.x <= (pos_fn1.x + fond_noir->w)) { //Bon x
        if (event.button.y >= (pos_fn1.y) &&
            event.button.y <= (pos_fn1.y + fond_noir->h)) {
          demander_un_nom(ecran, nom[0], pos_fn1);
          break;
        }
        if (event.button.y >= (pos_fn2.y) &&
            event.button.y <= (pos_fn2.y + fond_noir->h)) {
          demander_un_nom(ecran, nom[1], pos_fn2);
          break;
        }
        if (event.button.y >= (pos_fn3.y) &&
            event.button.y <= (pos_fn3.y + fond_noir->h)) {
          demander_un_nom(ecran, nom[2], pos_fn3);
          break;
        }
        if (event.button.y >= (pos_fn4.y) &&
            event.button.y <= (pos_fn4.y + fond_noir->h)) {
          demander_un_nom(ecran, nom[3], pos_fn4);
          break;
        }
      }
      if (strlen(nom[0]) && strlen(nom[1]) && strlen(nom[2]) && strlen(nom[3])) { //Tout les noms sont remplis
        if (event.button.x >= pos_suivant.x && event.button.x <= pos_suivant.x + texte_suivant->w &&
            event.button.y >= pos_suivant.y && event.button.y <= pos_suivant.y + texte_suivant->h)
          continuer = 0;
        break;
      }
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        _exit(0);
        break;
      default:
        break;
      }
    }
  }
  SDL_FreeSurface(texte_j1);
  SDL_FreeSurface(texte_j2);
  SDL_FreeSurface(texte_j3);
  SDL_FreeSurface(texte_j4);
  SDL_FreeSurface(fond_noir);
  TTF_CloseFont(police);
}

void demander_un_nom(SDL_Surface *ecran, char nom[], SDL_Rect pos) {
  SDL_Surface *fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, 0.22 * ecran->w, ecran->h / 10, 32, 0, 0, 0, 0);
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(30));
  SDL_Color couleurblanche = {255, 255, 255};
  SDL_Event event;
  int continuer = 1;
  int drapeau_shift = 0;
  int drapeau_maj = 0;
  char lettre[2];
  lettre[1] = 0;
  int indice = strlen(nom);
  SDL_Surface *texte_nom = NULL;
  SDL_Rect pos_texte;
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_KEYDOWN:
      lettre[0] = event.key.keysym.sym;
      if (lettre[0] >= SDLK_a && lettre[0] <= SDLK_z && indice < 15) {
        if (drapeau_maj || drapeau_shift)
          nom[indice] = toupper(lettre[0]);
        else
          nom[indice] = lettre[0];
        indice ++;
        nom[indice] = 0;
        texte_nom = TTF_RenderText_Blended(police, nom, couleurblanche);
        enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos);
        pos_texte.x = pos.x + (fond_noir->w / 2 - texte_nom->w / 2);
        pos_texte.y = pos.y + (fond_noir->h / 2 - texte_nom->h / 2);
        SDL_BlitSurface(texte_nom, NULL, ecran, &pos_texte);
        SDL_Flip(ecran);
        break;
      }
      if (lettre[0] == SDLK_BACKSPACE && indice != 0) {
        indice --;
        nom[indice] = 0;
        if (indice != 0) { //Taille non nulle
          texte_nom = TTF_RenderText_Blended(police, nom, couleurblanche);
          enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos);
          pos_texte.x = pos.x + (fond_noir->w / 2 - texte_nom->w / 2);
          pos_texte.y = pos.y + (fond_noir->h / 2 - texte_nom->h / 2);
          SDL_BlitSurface(texte_nom, NULL, ecran, &pos_texte);
        }
        else
          enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos);
        SDL_Flip(ecran);
        break;
      }
      if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) {
        drapeau_shift = 1;
        break;
      }
      if (event.key.keysym.sym == SDLK_CAPSLOCK) {
        drapeau_maj = !drapeau_maj;
        break;
      }
      if (lettre[0] == SDLK_RETURN) {
        continuer = 0;
        break;
      }
      break;
    case SDL_KEYUP:
      if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) {
        drapeau_shift = 0;
        break;
      }
      break;
    case SDL_MOUSEBUTTONUP:
      if (event.button.x <= pos.x || event.button.x >= (pos.x + fond_noir->w) ||
          event.button.y <= pos.y || event.button.y >= (pos.y + fond_noir->h)) {
        continuer = 0;
        break;
      }
      break;
    }
  }
  SDL_FreeSurface(fond_noir);
  SDL_FreeSurface(texte_nom);
  TTF_CloseFont(police);
}


////////////////////////////////////////////////////////////////
////
////            Affichage des noms des joueurs
////
////////////////////////////////////////////////////////////////

void affiche_nom_un_joueur(SDL_Surface *ecran, Joueur joueur, Direction d) {
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(20));
  SDL_Surface *texte = NULL;
  SDL_Color couleurblanche = {255, 255, 255};
  SDL_Rect pos;
  texte = TTF_RenderText_Blended(police, joueur.nom, couleurblanche);
  if (d == BAS || d == HAUT) {
    pos.x = ecran->w / 2 - texte->w / 2;
    if (d == BAS)
      pos.y = ecran->h - texte->h;
    else
      pos.y = texte->h / 2;
  }
  else {
    if (d == GAUCHE) {
      pos.x = 5 * LONGUEUR_CARTE / 8 - texte->w / 2 + 8;
      pos.y = ecran->h / 2 + 2 * LARGEUR_CARTE + texte->h / 2;
    }
    else {
      pos.x = ecran->w - 5 * LONGUEUR_CARTE / 8 - texte->w / 2 - 8;
      pos.y = ecran->h / 2 - 2 * LARGEUR_CARTE - 3 * texte->h / 2;
    }
  }
  SDL_BlitSurface(texte, NULL, ecran, &pos);
  SDL_Flip(ecran);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}

void enlever_nom_un_joueur(SDL_Surface *ecran, Direction d) {
  SDL_Rect pos;
  SDL_Surface *fond_vert = SDL_CreateRGBSurface(SDL_HWSURFACE, 20 * MAX_CARACTERES, 20, 32, 0, 0, 0, 0);
  SDL_FillRect(fond_vert, NULL, COULEUR_FOND);
  if (d == BAS || d == HAUT) {
    pos.x = ecran->w / 2 - fond_vert->w / 2;
    if (d == BAS)
      pos.y = ecran->h - fond_vert->h;
    else
      pos.y = fond_vert->h / 2;
  }
  else {
    if (d == GAUCHE) {
      pos.x = 5 * LONGUEUR_CARTE / 8 - fond_vert->w / 2;
      pos.y = ecran->h / 2 + 2 * LARGEUR_CARTE + fond_vert->h / 2;
    }
    else {
      pos.x = ecran->w - 5 * LONGUEUR_CARTE / 8 - fond_vert->w / 2;
      pos.y = ecran->h / 2 - 2 * LARGEUR_CARTE - 3 * fond_vert->h / 2;
    }
  }
  SDL_BlitSurface(fond_vert, NULL, ecran, &pos);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond_vert);
}
void affiche_nom_joueurs(SDL_Surface *ecran, Partie *partie, Direction place_j1) {
  for (int i = 0; i < 4; i++)
    affiche_nom_un_joueur(ecran, partie->joueurs[i], (place_j1 + i) % 4);

}

void enlever_nom_joueurs(SDL_Surface *ecran) {
  for (int i = 0; i < 4; i++)
    enlever_nom_un_joueur(ecran, i);
}

////////////////////////////////////////////////////////////////
////
////              Init_graphique et affichage de base
////
////////////////////////////////////////////////////////////////

void graphique_init_paquet(SDL_Rect tab[]) {
  for (int j = 0; j < 4; j++) { //On parcout toutes les couleurs pour les cartes en bas et en haut
    for (int i = 0; i < 10; i++) { //On parcourt toutes les valeurs
      if (i > 6) { //Car le jeu a 52 cartes
        tab[(j * 10) + i].x = LARGEUR_CARTE * (i + 2);
        tab[(j * 10) + i].y = LONGUEUR_CARTE * j;
      }
      else {
        tab[(j * 10) + i].x = LARGEUR_CARTE * i;
        tab[(j * 10) + i].y = LONGUEUR_CARTE * j;
      }
      tab[(j * 10) + i].w = LARGEUR_CARTE;
      tab[(j * 10) + i].h = LONGUEUR_CARTE;
    }
  }
  for (int j = 0; j < 4; j++) { // Cartes a droite
    for (int i = 0; i < 10; i ++) {
      if (i > 6) {
        tab[40 + (j * 10) + i].x = LONGUEUR_CARTE * j;
        tab[40 + (j * 10) + i].y = LARGEUR_CARTE * (12 - (i + 2));
      }
      else {
        tab[40 + (j * 10) + i].x = LONGUEUR_CARTE * j;
        tab[40 + (j * 10) + i].y = LARGEUR_CARTE * (12 - i);
      }
      tab[40 + (j * 10) + i].w = LONGUEUR_CARTE;
      tab[40 + (j * 10) + i].h = LARGEUR_CARTE;
    }
  }
  for (int j = 0; j < 4; j++) { // Cartes a gauche
    for (int i = 0; i < 10; i ++) {
      if (i > 6) {
        tab[80 + (j * 10) + i].x = LONGUEUR_CARTE * (3 - j);
        tab[80 + (j * 10) + i].y = LARGEUR_CARTE * (i + 2);
      }
      else {
        tab[80 + (j * 10) + i].x = LONGUEUR_CARTE * (3 - j);
        tab[80 + (j * 10) + i].y = LARGEUR_CARTE * i;
      }
      tab[80 + (j * 10) + i].w = LONGUEUR_CARTE;
      tab[80 + (j * 10) + i].h = LARGEUR_CARTE;
    }
  }
}

void affiche_dos(SDL_Surface *ecran, Direction d, SDL_Rect chem_carte) {
  SDL_Rect pos;
  SDL_Surface *carte_image = NULL;
  if (d == BAS || d == HAUT) {
    carte_image = IMG_Load("ressource/jeu_complet.png");
    pos.x = LARGEUR_CARTE * 12; //Pos de la carte dans l'image
    pos.y = 0;
    pos.w = LARGEUR_CARTE;
    pos.h = LONGUEUR_CARTE;
  }
  else {
    carte_image = IMG_Load("ressource/jeu_complet_tourner_droite.png");
    pos.x = 0;
    pos.y = 0;
    pos.w = LONGUEUR_CARTE;
    pos.h = LARGEUR_CARTE;
  }
  SDL_BlitSurface(carte_image, &pos, ecran, &chem_carte);
  SDL_Flip(ecran);
  SDL_FreeSurface(carte_image);
}

void affiche_carte(SDL_Rect tab[], SDL_Rect pos, Carte *carte, SDL_Surface *ecran, Direction d) {
  int valeur = 0;
  if (d == GAUCHE)
    valeur = 80;
  if (d == DROITE)
    valeur = 40;
  valeur += ((carte->couleur) * 10) + carte->valeur - 1;
  SDL_Surface *carte_image = NULL;
  if (d == DROITE)
    carte_image = IMG_Load("ressource/jeu_complet_tourner_droite.png");
  else if (d == GAUCHE)
    carte_image = IMG_Load("ressource/jeu_complet_tourner_gauche.png");
  else
    carte_image = IMG_Load("ressource/jeu_complet.png");
  SDL_BlitSurface(carte_image, &tab[valeur], ecran, &pos);
  SDL_Flip(ecran);
  SDL_FreeSurface(carte_image);
}

void graphique_affiche_main(SDL_Surface *ecran, Carte tab[], SDL_Rect tab_pos[], Direction d) {
  SDL_Rect pos;
  if (d == HAUT || d == BAS) {
    pos.x = ecran->w / 2 - 2 * LARGEUR_CARTE;
    if (d == BAS)
      pos.y = ecran->h - (LONGUEUR_CARTE + (LONGUEUR_CARTE / 4));
    else
      pos.y = LONGUEUR_CARTE / 4;
  }
  else {
    pos.y = ecran->h / 2 - 2 * LARGEUR_CARTE;
    if (d == GAUCHE)
      pos.x = LONGUEUR_CARTE / 4;
    else
      pos.x = ecran->w - (5 * LONGUEUR_CARTE / 4);
  }
  for (int i = 0; i < 4; i++) {
    affiche_carte(tab_pos, pos, &tab[i], ecran, d);
    if (d == BAS || d == HAUT)
      pos.x += LARGEUR_CARTE;
    else
      pos.y += LARGEUR_CARTE;
  }
  SDL_Flip(ecran);
}

void graphique_affiche_main_cachee(SDL_Surface *ecran) {
  SDL_Rect pos;
  pos.y = ecran->h - (LONGUEUR_CARTE + (LONGUEUR_CARTE / 4));
  for (int i = 1; i < 5; i ++) {
    pos.x = ecran->w / 2 - (-2 * LARGEUR_CARTE + (i * LARGEUR_CARTE));
    affiche_dos(ecran, 0, pos);
  }
  SDL_Flip(ecran);
}

void affiche_paquet_esku(SDL_Surface *ecran, Direction esku) {
  SDL_Rect pos;
  if (esku == BAS || esku == DROITE) {
    pos.y = ecran->h - (LONGUEUR_CARTE + (LONGUEUR_CARTE / 4));
    if (esku == BAS)
      pos.x = ecran->w / 4;
    else
      pos.x = 3 * ecran->w / 4;
  }
  else {
    pos.y = LONGUEUR_CARTE / 4;
    if (esku == GAUCHE)
      pos.x = ecran->w / 4;
    else
      pos.x = 3 * ecran->w / 4;
  }
  affiche_paquet(ecran, pos);
}

void affiche_paquet(SDL_Surface *ecran, SDL_Rect pos) {
  SDL_Surface *carte_image = IMG_Load("ressource/jeu_complet.png");
  SDL_Rect p;
  p.x = LARGEUR_CARTE * 12;
  p.y = 0;
  p.w = LARGEUR_CARTE;
  p.h = LONGUEUR_CARTE;
  for (int i = 0; i < 5; i ++) { //On superpose plusieurs carte de dos pour avoir un effet de perspective
    SDL_BlitSurface(carte_image, &p, ecran, &pos);
    pos.y -= 2;
  }
  SDL_Flip(ecran);
  SDL_FreeSurface(carte_image);
}

void afficher_toutes_les_mains(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[]) {
  int esku = partie->nb_tours;
  enlever_nom_joueurs(ecran);
  affiche_nom_joueurs(ecran, partie, modulo_4_neg(esku));
  enlever_paquet_4_endroit(ecran);
  affiche_paquet_esku(ecran, esku);
  for (int i = 0; i < 4; i++)
    graphique_affiche_main(ecran, partie->joueurs[(esku + i) % 4].main, tab, i);
}

void enlever_toutes_les_mains(SDL_Surface *ecran, Partie *partie) {
  SDL_FillRect(ecran, NULL, COULEUR_FOND);
  SDL_Flip(ecran);
  graphique_init_score(ecran);
  graphique_mise_a_jour_score(ecran, partie);
  graphique_mise_a_jour_manche(ecran, partie);
}

void enlever_paquet_esku(SDL_Surface *ecran, Direction esku) {
  SDL_Rect pos;
  if (esku == BAS || esku == DROITE) {
    pos.y = ecran->h - (LONGUEUR_CARTE + (LONGUEUR_CARTE / 4));
    if (esku == BAS)
      pos.x = ecran->w / 4;
    else
      pos.x = 3 * ecran->w / 4;
  }
  else {
    pos.y = LONGUEUR_CARTE / 4;
    if (esku == GAUCHE)
      pos.x = ecran->w / 4;
    else
      pos.x = 3 * ecran->w / 4;
  }
  enlever_paquet(ecran, pos);
}

void enlever_paquet(SDL_Surface *ecran, SDL_Rect pos) {
  SDL_Surface *fond_vert = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_CARTE, LONGUEUR_CARTE + 8, 32, 0, 0, 0, 0);
  pos.y -= 8;
  SDL_FillRect(fond_vert, NULL, COULEUR_FOND);
  SDL_BlitSurface(fond_vert, NULL, ecran, &pos);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond_vert);
}

void enlever_paquet_4_endroit(SDL_Surface *ecran) {
  for (int i = 0; i < 4; i++)
    enlever_paquet_esku(ecran, i);
}

////////////////////////////////////////////////////////////////
////
////              Distribution
////
////////////////////////////////////////////////////////////////

void animation_distribuer_carte(SDL_Surface *ecran, SDL_Surface *carte_image, SDL_Rect pos, SDL_Rect chem_carte) {
  SDL_Surface *fond_vert;
  fond_vert = SDL_CreateRGBSurface(SDL_HWSURFACE, pos.w, pos.h, 32, 0, 0, 0, 0);
  SDL_FillRect(fond_vert, NULL, COULEUR_FOND);
  SDL_BlitSurface(carte_image, &pos, ecran, &chem_carte);
  SDL_Flip(ecran);
  SDL_BlitSurface(fond_vert, NULL, ecran, &chem_carte);
  SDL_FreeSurface(fond_vert);
}

void graphique_distribuer_une_carte(SDL_Surface *ecran, Direction d, int nb_carte_distribuer) {
  SDL_Surface *carte_image;
  SDL_Rect pos, chem_carte;
  chem_carte.x = ecran->w / 2 - 2 * LARGEUR_CARTE;
  chem_carte.y = ecran->h / 2 - 2 * LARGEUR_CARTE;
  if (d == HAUT || d == BAS) {
    carte_image = IMG_Load("ressource/jeu_complet.png");
    pos.x = LARGEUR_CARTE * 12;
    pos.y = 0;
    pos.w = LARGEUR_CARTE;
    pos.h = LONGUEUR_CARTE;
    if (d == HAUT) { //Aller en haut
      chem_carte.y -= LONGUEUR_CARTE + 6;
      while (chem_carte.y > LONGUEUR_CARTE / 4) {
        animation_distribuer_carte(ecran, carte_image, pos, chem_carte);
        chem_carte.y -= NB_PIXEL_DECALAGE;
      }
    }
    if (d == BAS) { //Aller en bas
      chem_carte.y += LONGUEUR_CARTE;
      while (chem_carte.y < ecran->h - (LONGUEUR_CARTE + (LONGUEUR_CARTE / 4))) {
        animation_distribuer_carte(ecran, carte_image, pos, chem_carte);
        chem_carte.y += NB_PIXEL_DECALAGE;
      }
    }
    while (chem_carte.x < ecran->w / 2 - (-2 * LARGEUR_CARTE + (nb_carte_distribuer * LARGEUR_CARTE))) { //Pour la decaler vers la gauche
      animation_distribuer_carte(ecran, carte_image, pos, chem_carte);
      chem_carte.x += NB_PIXEL_DECALAGE;
    }
    chem_carte.x = ecran->w / 2 - (-2 * LARGEUR_CARTE + (nb_carte_distribuer * LARGEUR_CARTE));
    if (d == BAS)
      chem_carte.y = ecran->h - (LONGUEUR_CARTE + (LONGUEUR_CARTE / 4));
    else
      chem_carte.y = LONGUEUR_CARTE / 4;
    affiche_dos(ecran, BAS, chem_carte);
  }
  else {
    carte_image = IMG_Load("ressource/jeu_complet_tourner_droite.png");
    pos.x = 0;
    pos.y = 0;
    pos.w = LONGUEUR_CARTE;
    pos.h = LARGEUR_CARTE;
    if (d == GAUCHE) { //Aller vers la gauche
      chem_carte.x -= LONGUEUR_CARTE;
      while (chem_carte.x > (LONGUEUR_CARTE / 4)) {
        animation_distribuer_carte(ecran, carte_image, pos, chem_carte);
        chem_carte.x -= NB_PIXEL_DECALAGE;
      }
    }
    if (d == DROITE) { //Aller vers la droite
      chem_carte.x += LARGEUR_CARTE;
      while (chem_carte.x < ecran->w - (LONGUEUR_CARTE + LONGUEUR_CARTE / 4)) {
        animation_distribuer_carte(ecran, carte_image, pos, chem_carte);
        chem_carte.x += NB_PIXEL_DECALAGE;
      }
    }
    while (chem_carte.y < ecran->h / 2 - (-2 * LARGEUR_CARTE + (nb_carte_distribuer * LARGEUR_CARTE))) { //Pour la descendre
      animation_distribuer_carte(ecran, carte_image, pos, chem_carte);
      chem_carte.y += NB_PIXEL_DECALAGE;
    }
    if (d == DROITE)
      chem_carte.x = ecran->w - (LONGUEUR_CARTE + LONGUEUR_CARTE / 4);
    else
      chem_carte.x = LONGUEUR_CARTE / 4;
    chem_carte.y = ecran->h / 2 - (-2 * LARGEUR_CARTE + (nb_carte_distribuer * LARGEUR_CARTE));
    affiche_dos(ecran, DROITE, chem_carte);
  }
  SDL_FreeSurface(carte_image);
}

void graphique_distribuer(SDL_Surface *ecran, int esku) {
  SDL_Rect pos;
  pos.x = ecran->w / 2 - 2 * LARGEUR_CARTE;
  pos.y = ecran->h / 2 - 2 * LARGEUR_CARTE;
  affiche_paquet(ecran, pos);
  for (int j = 1; j < 5; j++)
    for (int i = 0; i < 4; i++)
      graphique_distribuer_une_carte(ecran, (i + esku) % 4, j);
  enlever_paquet(ecran, pos);
  if (esku == BAS || esku == DROITE) {
    pos.y = ecran->h - (LONGUEUR_CARTE + (LONGUEUR_CARTE / 4));
    if (esku == BAS)
      pos.x = ecran->w / 4;
    else
      pos.x = 3 * ecran->w / 4;
  }
  else {
    pos.y = LONGUEUR_CARTE / 4;
    if (esku == GAUCHE)
      pos.x = ecran->w / 4;
    else
      pos.x = 3 * ecran->w / 4;
  }
  affiche_paquet(ecran, pos);
  SDL_Flip(ecran);
}

////////////////////////////////////////////////////////////////
////
////              Phase du mus
////
////////////////////////////////////////////////////////////////

bool graphique_choix_mus_joueur(SDL_Surface *ecran) {
  SDL_Rect pos_mus, pos_mintza, pos_carre;
  SDL_Event event;
  int continuer = 1;
  bool choix;
  TTF_Font *police = NULL;
  SDL_Color couleurblanche = {255, 255, 255};
  SDL_Surface *carre = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w / 4, ecran->h / 4, 32, 0, 0, 0, 0), *texte_mus = NULL, *texte_mintza = NULL;
  police = TTF_OpenFont(CHOIX_POLICE(30));
  SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  pos_carre.x = ecran->w / 2 - carre->w / 2;
  pos_carre.y = ecran->h / 2 - carre->h / 2;
  SDL_SetAlpha(carre, SDL_SRCALPHA, 180);//Mettre de la transparence sur l'image
  SDL_BlitSurface(carre, NULL, ecran, &pos_carre);
  texte_mus = TTF_RenderText_Blended(police, "Mus", couleurblanche);
  pos_mus.x = pos_carre.x + carre->w / 2 - texte_mus->w / 2;
  pos_mus.y = pos_carre.y + carre->h / 4 - texte_mus->h / 2;
  SDL_BlitSurface(texte_mus, NULL, ecran, &pos_mus);
  texte_mintza = TTF_RenderText_Blended(police, "Mintza", couleurblanche);
  pos_mintza.x = pos_carre.x + carre->w / 2 - texte_mintza->w / 2;
  pos_mintza.y = pos_carre.y + 3 * carre->h / 4 - texte_mintza->h / 2;
  SDL_BlitSurface(texte_mintza, NULL, ecran, &pos_mintza);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
      if (event.button.x >= pos_mus.x && event.button.x <= (pos_mus.x + texte_mus->w) && event.button.y >= pos_mus.y && event.button.y <= (pos_mus.y + texte_mus->h)) {
        continuer = 0;
        choix = true;
      }
      if (event.button.x >= pos_mintza.x && event.button.x <= (pos_mintza.x + texte_mintza->w) && event.button.y >= pos_mintza.y && event.button.y <= (pos_mintza.y + texte_mintza->h)) {
        continuer = 0;
        choix = false;
      }
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        _exit(0);
        break;
      default:
        break;
      }
      break;
    }
  }
  SDL_SetAlpha(carre, SDL_SRCALPHA, 255);
  SDL_FillRect(carre, NULL, COULEUR_FOND);
  SDL_BlitSurface(carre, NULL, ecran, &pos_carre);
  SDL_Flip(ecran);
  SDL_FreeSurface(carre);
  SDL_FreeSurface(texte_mus);
  SDL_FreeSurface(texte_mintza);
  TTF_CloseFont(police);
  return choix;
}

bool graphique_choix_mus_equipe(SDL_Surface *ecran, int equipe, Partie *partie, SDL_Rect tab[]) {
  int esku = partie->nb_tours % 4;
  enlever_nom_joueurs(ecran);
  enlever_paquet_4_endroit(ecran);
  if (equipe == 0) {
    switch (esku) {
    case 0:
      affiche_nom_joueurs(ecran, partie, 0);
      affiche_paquet_esku(ecran, 0);
      message_joueur_suivant(ecran, partie, 0);
      graphique_affiche_main(ecran, partie->joueurs[equipe].main, tab, BAS);
      break;
    case 1:
      affiche_nom_joueurs(ecran, partie, 2);
      affiche_paquet_esku(ecran, 3);
      message_joueur_suivant(ecran, partie, 2);
      graphique_affiche_main(ecran, partie->joueurs[equipe + 2].main, tab, BAS);
      break;
    case 2:
      affiche_nom_joueurs(ecran, partie, 2);
      affiche_paquet_esku(ecran, 0);
      message_joueur_suivant(ecran, partie, 2);
      graphique_affiche_main(ecran, partie->joueurs[equipe + 2].main, tab, BAS);
      break;
    case 3:
      affiche_nom_joueurs(ecran, partie, 0);
      affiche_paquet_esku(ecran, 3);
      message_joueur_suivant(ecran, partie, 0);
      graphique_affiche_main(ecran, partie->joueurs[equipe].main, tab, BAS);
      break;
    }
  }
  else {
    switch (esku) {
    case 0:
      affiche_nom_joueurs(ecran, partie, 3);
      affiche_paquet_esku(ecran, 3);
      message_joueur_suivant(ecran, partie, 1);
      graphique_affiche_main(ecran, partie->joueurs[equipe].main, tab, BAS);
      break;
    case 1:
      affiche_nom_joueurs(ecran, partie, 3);
      affiche_paquet_esku(ecran, 0);
      message_joueur_suivant(ecran, partie, 1);
      graphique_affiche_main(ecran, partie->joueurs[equipe].main, tab, BAS);
      break;
    case 2:
      affiche_nom_joueurs(ecran, partie, 1);
      affiche_paquet_esku(ecran, 3);
      message_joueur_suivant(ecran, partie, 3);
      graphique_affiche_main(ecran, partie->joueurs[equipe + 2].main, tab, BAS);
      break;
    case 3:
      affiche_nom_joueurs(ecran, partie, 0);
      message_joueur_suivant(ecran, partie, 3);
      graphique_affiche_main(ecran, partie->joueurs[equipe + 2].main, tab, BAS);
      break;
    }
  }
  if (!graphique_choix_mus_joueur(ecran))
    return false;
  enlever_nom_joueurs(ecran);
  enlever_paquet_4_endroit(ecran);
  if (equipe == 0) {
    switch (esku) {
    case 0:
      affiche_nom_joueurs(ecran, partie, 2);
      affiche_paquet_esku(ecran, 2);
      message_joueur_suivant(ecran, partie, 2);
      graphique_affiche_main(ecran, partie->joueurs[equipe + 2].main, tab, BAS);
      break;
    case 1:
      affiche_nom_joueurs(ecran, partie, 0);
      affiche_paquet_esku(ecran, 1);
      message_joueur_suivant(ecran, partie, 0);
      graphique_affiche_main(ecran, partie->joueurs[equipe].main, tab, BAS);
      break;
    case 2:
      affiche_nom_joueurs(ecran, partie, 0);
      affiche_paquet_esku(ecran, 2);
      message_joueur_suivant(ecran, partie, 0);
      graphique_affiche_main(ecran, partie->joueurs[equipe].main, tab, BAS);
      break;
    case 3:
      affiche_nom_joueurs(ecran, partie, 2);
      affiche_paquet_esku(ecran, 1);
      message_joueur_suivant(ecran, partie, 2);
      graphique_affiche_main(ecran, partie->joueurs[equipe + 2].main, tab, BAS);
      break;
    }
  }
  else {
    switch (esku) {
    case 0:
      affiche_nom_joueurs(ecran, partie, 1);
      affiche_paquet_esku(ecran, 1);
      message_joueur_suivant(ecran, partie, 3);
      graphique_affiche_main(ecran, partie->joueurs[equipe + 2].main, tab, BAS);
      break;
    case 1:
      affiche_nom_joueurs(ecran, partie, 1);
      affiche_paquet_esku(ecran, 2);
      message_joueur_suivant(ecran, partie, 3);
      graphique_affiche_main(ecran, partie->joueurs[equipe + 2].main, tab, BAS);
      break;
    case 2:
      affiche_nom_joueurs(ecran, partie, 3);
      affiche_paquet_esku(ecran, 1);
      message_joueur_suivant(ecran, partie, 1);
      graphique_affiche_main(ecran, partie->joueurs[equipe].main, tab, BAS);
      break;
    case 3:
      affiche_nom_joueurs(ecran, partie, 3);
      affiche_paquet_esku(ecran, 2);
      message_joueur_suivant(ecran, partie, 1);
      graphique_affiche_main(ecran, partie->joueurs[equipe].main, tab, BAS);
      break;
    }
  }
  return graphique_choix_mus_joueur(ecran);
}

//lever est vrai si la carte est lever et faux sinon
void graphique_lever_baisser_carte(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[], int joueur, int carte, bool lever) {
  SDL_Rect pos;
  SDL_Surface *fond_vert = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_CARTE, LONGUEUR_CARTE, 32, 0, 0, 0, 0);
  pos.x = ecran->w / 2 - (-2 * LARGEUR_CARTE + ((4 - carte) * LARGEUR_CARTE));
  SDL_FillRect(fond_vert, NULL, COULEUR_FOND);
  if (lever)
    pos.y = ecran->h - (LONGUEUR_CARTE + LONGUEUR_CARTE / 2);
  else
    pos.y = ecran->h - (LONGUEUR_CARTE + LONGUEUR_CARTE / 4);
  SDL_BlitSurface(fond_vert, NULL, ecran, &pos);
  if (!lever)
    pos.y = ecran->h - (LONGUEUR_CARTE + LONGUEUR_CARTE / 2);
  else
    pos.y = ecran->h - (LONGUEUR_CARTE + LONGUEUR_CARTE / 4);
  affiche_carte(tab, pos, &partie->joueurs[joueur].main[carte], ecran, BAS);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond_vert);
}

void jeter_carte(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[], Direction d, bool choix_carte[]) {
  SDL_Surface *image = IMG_Load("ressource/jeu_complet.png");
  SDL_Rect pos_final, pos_carte, pos;
  pos.x = LARGEUR_CARTE * 12;
  pos.y = 0;
  pos.w = LARGEUR_CARTE;
  pos.h = LONGUEUR_CARTE;
  for (int i = 0; i < 4; i++) {
    pos_final.x = ecran->w / 2;
    pos_final.y = ecran->h / 2;
    if (choix_carte[i]) {
      pos_carte.x = ecran->w / 2 - (-2 * LARGEUR_CARTE + ((4 - i) * LARGEUR_CARTE));
      pos_carte.y = ecran->h - (LONGUEUR_CARTE + LONGUEUR_CARTE / 4);//+ 5 car sinon il reste un bout de carte
      animation_distribuer_carte(ecran, image, pos, pos_carte);
      while (pos_carte.y > ecran->h - (5 * LONGUEUR_CARTE / 2)) {
        animation_distribuer_carte(ecran, image, pos, pos_carte);
        pos_carte.y -= NB_PIXEL_DECALAGE;
      }
      while (abs(pos_carte.x - pos_final.x) != 0 || pos_carte.y > pos_final.y) {
        animation_distribuer_carte(ecran, image, pos, pos_carte);
        if (pos_carte.y > pos_final.y)
          pos_carte.y -= NB_PIXEL_DECALAGE;
        if (pos_carte.x < pos_final.x)
          pos_carte.x ++;
        if (pos_carte.x > pos_final.x)
          pos_carte.x --;
      }
      affiche_dos(ecran, BAS, pos_carte);
    }
  }
  SDL_FreeSurface(image);
}

void enlever_carte_jetee(SDL_Surface *ecran) {
  SDL_Surface *fond = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_CARTE, LONGUEUR_CARTE + 5, 32, 0, 0, 0, 0);
  SDL_FillRect(fond, NULL, COULEUR_FOND);
  SDL_Rect pos;
  pos.x = ecran->w / 2;
  pos.y = ecran->h / 2 - 5;
  SDL_BlitSurface(fond, NULL, ecran, &pos);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond);
}

void distribuer_carte_manquante(SDL_Surface *ecran, bool choix_carte[], Direction d, int esku) {
  int nb = 4;
  SDL_Surface *fond_vert = NULL;
  SDL_Rect pos_fond_vert, pos_dos;
  if (d == BAS || d == HAUT) {
    fond_vert = SDL_CreateRGBSurface(SDL_HWSURFACE, 4 * LARGEUR_CARTE, LONGUEUR_CARTE, 32, 0, 0, 0, 0);
    pos_fond_vert.x = ecran->w / 2 - (-2 * LARGEUR_CARTE + (4 * LARGEUR_CARTE));
    if (d == BAS)
      pos_fond_vert.y = ecran->h - (5 * LONGUEUR_CARTE / 4);
    else
      pos_fond_vert.y = LONGUEUR_CARTE / 4;
  }
  SDL_FillRect(fond_vert, NULL, COULEUR_FOND);
  SDL_BlitSurface(fond_vert, NULL, ecran, &pos_fond_vert);
  for (int i = 0; i < 4; i++)
    nb -= choix_carte[i]; //Nb de carte jetee
  pos_dos.x = pos_fond_vert.x;
  pos_dos.y = pos_fond_vert.y;
  for (int i = 0; i < nb; i++) {
    if (d == BAS || d == HAUT)
      pos_dos.x = ecran->w / 2 - (-2 * LARGEUR_CARTE + ((i + 1) * LARGEUR_CARTE));
    else
      pos_dos.y = ecran->h / 2 - (-2 * LARGEUR_CARTE + (i * LARGEUR_CARTE));
    affiche_dos(ecran, d, pos_dos);
  }
  SDL_Rect pos_distribuer, pos;
  if (esku == BAS || esku == DROITE) {
    pos.y = ecran->h - (LONGUEUR_CARTE + (LONGUEUR_CARTE / 4));
    if (esku == BAS)
      pos.x = ecran->w / 4;
    else
      pos.x = 3 * ecran->w / 4;
  }
  else {
    pos.y = LONGUEUR_CARTE / 4;
    if (esku == GAUCHE)
      pos.x = ecran->w / 4;
    else
      pos.x = 3 * ecran->w / 4;
  }
  enlever_paquet(ecran, pos);
  pos_distribuer.x = ecran->w / 2 - 2 * LARGEUR_CARTE;
  pos_distribuer.y = ecran->h / 2 - 2 * LARGEUR_CARTE;
  affiche_paquet(ecran, pos_distribuer);
  for (int i = nb; i < 4; i ++)
    graphique_distribuer_une_carte(ecran, d, (i + 1));
  enlever_paquet(ecran, pos_distribuer);
  affiche_paquet(ecran, pos);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond_vert);
}

void graphique_choix_carte_mus(SDL_Surface *ecran, Partie *partie, SDL_Rect tab[], int joueur, bool choix_carte[]) {
  graphique_affiche_main(ecran, partie->joueurs[joueur].main, tab, 0);
  bool bota_possible = false;
  SDL_Surface *texte_bota = NULL, *fond_vert = NULL;
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(30));
  SDL_Event event;
  SDL_Color couleurblanche = {255, 255, 255};
  int continuer = 1;
  SDL_Rect pos_bota;
  SDL_Rect pos_l_b[8]; //0 baisse pour carte 0, 1 baisse pour carte 1 ... 4 lever pour carte 1
  for (int i = 0; i < 4; i++) {
    pos_l_b[i].x = ecran->w / 2 - (-2 * LARGEUR_CARTE + ((4 - i) * LARGEUR_CARTE));
    pos_l_b[i].y = ecran->h - (LONGUEUR_CARTE + LONGUEUR_CARTE / 4);
  }
  for (int i = 4; i < 8; i++) {
    pos_l_b[i].x = ecran->w / 2 - (-2 * LARGEUR_CARTE + ((8 - i) * LARGEUR_CARTE));
    pos_l_b[i].y = ecran->h - (LONGUEUR_CARTE + LONGUEUR_CARTE / 2);
  }
  texte_bota = TTF_RenderText_Blended(police, "Bota", couleurblanche);
  pos_bota.x = ecran->w / 2 - 3 * texte_bota->w / 2;
  pos_bota.y = ecran->h / 2 + LONGUEUR_CARTE / 2 - texte_bota->h / 2;
  SDL_BlitSurface(texte_bota, NULL, ecran, &pos_bota);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
      if (event.button.y >= pos_l_b[0].y && event.button.y <= pos_l_b[0].y + LONGUEUR_CARTE) {
        if (!choix_carte[0] && event.button.x >= pos_l_b[0].x && event.button.x <= pos_l_b[0].x + LARGEUR_CARTE) { //Carte 0 baisse
          graphique_lever_baisser_carte(ecran, partie, tab, joueur, 0, false);
          choix_carte[0] = true;
          break;
        }
        if (!choix_carte[1] && event.button.x >= pos_l_b[1].x && event.button.x <= pos_l_b[1].x + LARGEUR_CARTE) { //Carte 1 baisse
          graphique_lever_baisser_carte(ecran, partie, tab, joueur, 1, false);
          choix_carte[1] = true;
          break;
        }
        if (!choix_carte[2] && event.button.x >= pos_l_b[2].x && event.button.x <= pos_l_b[2].x + LARGEUR_CARTE) { //Carte 2 baisse
          graphique_lever_baisser_carte(ecran, partie, tab, joueur, 2, false);
          choix_carte[2] = true;
          break;
        }
        if (!choix_carte[3] && event.button.x >= pos_l_b[3].x && event.button.x <= pos_l_b[3].x + LARGEUR_CARTE) { //Carte 3 baisse
          graphique_lever_baisser_carte(ecran, partie, tab, joueur, 3, false);
          choix_carte[3] = true;
          break;
        }
      }
      if (event.button.y >= pos_l_b[4].y && event.button.y <= pos_l_b[4].y + LONGUEUR_CARTE) {
        if (choix_carte[0] && event.button.x >= pos_l_b[4].x && event.button.x <= pos_l_b[4].x + LARGEUR_CARTE) { //Carte 0 levee
          graphique_lever_baisser_carte(ecran, partie, tab, joueur, 0, true);
          choix_carte[0] = false;
          break;
        }
        if (choix_carte[1] && event.button.x >= pos_l_b[5].x && event.button.x <= pos_l_b[5].x + LARGEUR_CARTE) { //Carte 1 levee
          graphique_lever_baisser_carte(ecran, partie, tab, joueur, 1, true);
          choix_carte[1] = false;
          break;
        }
        if (choix_carte[2] && event.button.x >= pos_l_b[6].x && event.button.x <= pos_l_b[6].x + LARGEUR_CARTE) { //Carte 2 levee
          graphique_lever_baisser_carte(ecran, partie, tab, joueur, 2, true);
          choix_carte[2] = false;
          break;
        }
        if (choix_carte[3] && event.button.x >= pos_l_b[7].x && event.button.x <= pos_l_b[7].x + LARGEUR_CARTE) { //Carte 3 levee
          graphique_lever_baisser_carte(ecran, partie, tab, joueur, 3, true);
          choix_carte[3] = false;
          break;
        }
      }
      bota_possible = choix_carte[0] || choix_carte[1] || choix_carte[2] || choix_carte[3];
      if (bota_possible && event.button.x >= pos_bota.x && event.button.x <= pos_bota.x + texte_bota->w && event.button.y >= pos_bota.y && event.button.y <= pos_bota.y + texte_bota->h) {
        continuer = 0;
        break;
      }
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        _exit(0);
        break;
      default:
        break;
      }
    }
  }
  fond_vert = SDL_CreateRGBSurface(SDL_HWSURFACE, texte_bota->w, texte_bota->h, 32, 0, 0, 0, 0);
  SDL_FillRect(fond_vert, NULL, COULEUR_FOND);
  SDL_BlitSurface(fond_vert, NULL, ecran, &pos_bota);
  SDL_FreeSurface(texte_bota);
  SDL_FreeSurface(fond_vert);
  TTF_CloseFont(police);
}

////////////////////////////////////////////////////////////////
////
////              Phase de mise
////
////////////////////////////////////////////////////////////////

int graphique_phase_de_mise(SDL_Surface *ecran, SDL_Rect tab[], Partie *partie, int mise_precedente, int joueur) {
  int mise;
  int esku = partie->nb_tours % 4;
  enlever_nom_joueurs(ecran);
  affiche_nom_joueurs(ecran, partie, (-joueur) % 4);
  enlever_paquet_4_endroit(ecran);
  affiche_paquet_esku(ecran, endroit_paquet(esku, joueur));
  message_joueur_suivant(ecran, partie, joueur);
  graphique_affiche_main(ecran, partie->joueurs[joueur].main, tab, BAS);
  SDL_Rect pos_carre;
  SDL_Surface *carre = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w / 3, ecran->h / 4, 32, 0, 0, 0, 0);
  SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  SDL_SetAlpha(carre, SDL_SRCALPHA, 180);
  pos_carre.x = ecran->w / 2 - carre->w / 2;
  pos_carre.y = ecran->h / 2 - carre->h / 2;
  SDL_BlitSurface(carre, NULL, ecran, &pos_carre);
  SDL_Flip(ecran);
  if (mise_precedente == 0) //Paso ou premier a miser
    mise = phase_de_mise_debut(ecran, carre, pos_carre);
  else if (mise_precedente == -1) //Hordago avant
    mise = phase_de_mise_hordago(ecran, carre, pos_carre);
  else if (mise_precedente == -3) //Iduki du partenaire
    mise = phase_de_mise_iduki(ecran, carre, pos_carre);

  else //Si une mise avant
    mise = phase_de_mise_surenchir(ecran, carre, pos_carre);
  SDL_SetAlpha(carre, 0, 180);
  SDL_FillRect(carre, NULL, COULEUR_FOND);
  SDL_BlitSurface(carre, NULL, ecran, &pos_carre);
  SDL_Flip(ecran);
  SDL_FreeSurface(carre);
  return mise;
}

//Paso ou premier a miser
int phase_de_mise_debut(SDL_Surface *ecran, SDL_Surface *carre, SDL_Rect pos_carre) {
  int mise, continuer = 1;
  char char_mise[4];
  SDL_Rect pos_hordago, pos_imido, pos_paso, pos_plus, pos_moins, pos_mise;
  SDL_Color couleurblanche = {255, 255, 255};
  SDL_Surface *plus = IMG_Load("ressource/plus.png"), *moins = IMG_Load("ressource/moins.png"), *fond_noir = NULL;
  TTF_Font *police = NULL;
  SDL_Surface *texte_hordago = NULL, *texte_imido = NULL, *texte_paso = NULL, *texte_mise = NULL;
  SDL_Event event;
  police = TTF_OpenFont(CHOIX_POLICE(30));
  texte_hordago = TTF_RenderText_Blended(police, "Hordago", couleurblanche);
  mise = 2;
  itoa(mise, char_mise);
  texte_paso = TTF_RenderText_Blended(police, "Paso", couleurblanche);
  texte_imido = TTF_RenderText_Blended(police, "Imido", couleurblanche);
  texte_mise = TTF_RenderText_Blended(police, char_mise, couleurblanche);
  pos_hordago.x = pos_carre.x + carre->w / 4 - texte_hordago->w / 2;
  pos_hordago.y = pos_carre.y + carre->h / 4 - texte_hordago->h / 2;
  SDL_BlitSurface(texte_hordago, NULL, ecran, &pos_hordago);
  pos_paso.x = pos_carre.x + 3 * carre->w / 4 - texte_paso->w / 2;
  pos_paso.y = pos_carre.y + carre->h / 4 - texte_paso->h / 2;
  SDL_BlitSurface(texte_paso, NULL, ecran, &pos_paso);
  pos_imido.x = pos_carre.x + carre->w / 2 - texte_imido->w / 2;
  pos_imido.y = pos_carre.y + 3 * carre->h / 4 - texte_imido->h / 2;
  SDL_BlitSurface(texte_imido, NULL, ecran, &pos_imido);
  pos_plus.x = pos_carre.x + 7 * carre->w / 8 - plus->w / 2;
  pos_plus.y = pos_carre.y + 3 * carre->h / 4 - plus->h / 2;
  pos_moins.x = pos_carre.x + carre->w / 8 - moins->w / 2;
  pos_moins.y = pos_carre.y + 3 * carre->h / 4 - moins->h / 2;
  pos_mise.x = pos_carre.x + carre->w / 2 - texte_mise->w / 2;
  pos_mise.y = pos_carre.y + 3 * carre->h / 4 - texte_mise->h / 2;
  SDL_BlitSurface(plus, NULL, ecran, &pos_plus);
  SDL_BlitSurface(moins, NULL, ecran, &pos_moins);
  fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, texte_imido->w, texte_imido->h, 32, 0, 0, 0, 0);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
      if (event.button.y >= (pos_paso.y) &&
          event.button.y <= (pos_paso.y + texte_paso->h)) { //ligne du haut
        if (event.button.x >= (pos_paso.x) &&
            event.button.x <= (pos_paso.x + texte_paso->w)) { //paso
          mise = 0;
          continuer = 0;
          break;
        }
        if (event.button.x >= (pos_hordago.x) &&
            event.button.x <= (pos_hordago.x + texte_hordago->w)) { //hordago
          mise = -1;
          continuer = 0;
          break;
        }
      }
      if (event.button.y >= (pos_moins.y) &&
          event.button.y <= (pos_moins.y + moins->h)) { //ligne du bas
        if (event.button.x >= (pos_moins.x) &&
            event.button.x <= (pos_moins.x + moins->w) &&
            mise > 2) { //moins
          mise --;
          itoa(mise, char_mise);
          texte_mise = TTF_RenderText_Blended(police, char_mise, couleurblanche);
          enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_imido);
          if (mise == 2)
            SDL_BlitSurface(texte_imido, NULL, ecran, &pos_imido);
          else
            SDL_BlitSurface(texte_mise, NULL, ecran, &pos_mise);
          SDL_Flip(ecran);
          break;
        }
        if (event.button.x >= (pos_plus.x) &&
            event.button.x <= (pos_plus.x + plus->w) &&
            mise < 40) { //plus
          mise ++;
          itoa(mise, char_mise);
          texte_mise = TTF_RenderText_Blended(police, char_mise, couleurblanche);
          enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_imido);
          SDL_BlitSurface(texte_mise, NULL, ecran, &pos_mise);
          SDL_Flip(ecran);
          break;
        }
        if (event.button.x >= (pos_imido.x) &&
            event.button.x <= (pos_imido.x + texte_imido->w) &&
            mise == 2) {
          continuer = 0;
          break;
        }
        if (event.button.x >= (pos_carre.x + carre->w / 2 - texte_mise->w / 2) &&
            event.button.x <= (pos_carre.x + carre->w / 2 + texte_mise->w / 2) &&
            mise > 2) {
          continuer = 0;
          break;
        }
      }
      case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        _exit(0);
        break;
      default:
        break;
      }
    }
  }
  SDL_Flip(ecran);
  TTF_CloseFont(police);
  SDL_FreeSurface(plus);
  SDL_FreeSurface(moins);
  SDL_FreeSurface(texte_hordago);
  SDL_FreeSurface(texte_paso);
  SDL_FreeSurface(texte_imido);
  SDL_FreeSurface(texte_mise);
  return mise;
}

//Hordago avant
int phase_de_mise_hordago(SDL_Surface *ecran, SDL_Surface *carre, SDL_Rect pos_carre) {
  int mise, continuer = 1;
  SDL_Rect pos_tira, pos_kanta;
  SDL_Color couleurblanche = {255, 255, 255};
  TTF_Font *police = NULL;
  SDL_Surface *texte_tira = NULL, *texte_kanta = NULL;
  SDL_Event event;
  police = TTF_OpenFont(CHOIX_POLICE(30));
  texte_kanta = TTF_RenderText_Blended(police, "Kanta", couleurblanche);
  texte_tira = TTF_RenderText_Blended(police, "Tira", couleurblanche);
  pos_kanta.x = pos_carre.x + carre->w / 2 - texte_kanta->w / 2;
  pos_kanta.y = pos_carre.y + carre->h / 4 - texte_kanta->h / 2;
  pos_tira.x = pos_carre.x + carre->w / 2 - texte_tira->w / 2;
  pos_tira.y = pos_carre.y + 3 * carre->h / 4 - texte_tira->h / 2;
  SDL_BlitSurface(texte_kanta, NULL, ecran, &pos_kanta);
  SDL_BlitSurface(texte_tira, NULL, ecran, &pos_tira);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
      if (event.button.x >= pos_kanta.x && event.button.x <= pos_kanta.x + texte_kanta->w &&
          event.button.y >= pos_kanta.y && event.button.y <= pos_kanta.y + texte_kanta->h) { //Kanta
        mise = -2;
        continuer = 0;
        break;
      }
      if (event.button.x >= pos_tira.x && event.button.x <= pos_tira.x + texte_tira->w &&
          event.button.y >= pos_tira.y && event.button.y <= pos_tira.y + texte_kanta->h) { //Tira
        mise = 1;
        continuer = 0;
        break;
      }
      break;
      case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        _exit(0);
        break;
      default:
        break;
      }
    }
  }
  SDL_Flip(ecran);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte_tira);
  SDL_FreeSurface(texte_kanta);
  return mise;
}

//Iduki du partenaire
int phase_de_mise_iduki(SDL_Surface *ecran, SDL_Surface *carre, SDL_Rect pos_carre) {
  int mise, continuer = 1;
  char char_mise[4];
  SDL_Rect pos_hordago, pos_iduki, pos_gehiago, pos_plus, pos_moins, pos_mise;
  SDL_Color couleurblanche = {255, 255, 255};
  SDL_Surface *plus = IMG_Load("ressource/plus.png"), *moins = IMG_Load("ressource/moins.png"), *fond_noir = NULL;
  TTF_Font *police = NULL;
  SDL_Surface *texte_hordago = NULL, *texte_iduki = NULL, *texte_gehiago = NULL, *texte_mise = NULL;
  SDL_Event event;
  police = TTF_OpenFont(CHOIX_POLICE(30));
  mise = 2;
  itoa(mise, char_mise);
  texte_gehiago = TTF_RenderText_Blended(police, "Gehiago", couleurblanche);
  texte_iduki = TTF_RenderText_Blended(police, "Iduki", couleurblanche);
  texte_hordago = TTF_RenderText_Blended(police, "Hordago", couleurblanche);
  texte_mise = TTF_RenderText_Blended(police, char_mise, couleurblanche);
  pos_hordago.x = pos_carre.x + carre->w / 4 - texte_hordago->w / 2;
  pos_hordago.y = pos_carre.y + carre->h / 4 - texte_hordago->h / 2;
  pos_iduki.x = pos_carre.x + 3 * carre->w / 4 - texte_iduki->w / 2;
  pos_iduki.y = pos_carre.y + carre->h / 4 - texte_iduki->h / 2;
  pos_gehiago.x = pos_carre.x + 0.55 * carre->w - texte_gehiago->w / 2;
  pos_gehiago.y = pos_carre.y + 3 * carre->h / 4 - texte_gehiago->h / 2;
  pos_plus.x = pos_carre.x + 7 * carre->w / 8 - plus->w / 2;
  pos_plus.y = pos_carre.y + 3 * carre->h / 4 - plus->h / 2;
  pos_moins.x = pos_carre.x + carre->w / 8 - moins->w / 2;
  pos_moins.y = pos_carre.y + 3 * carre->h / 4 - moins->h / 2;
  pos_mise.x = pos_carre.x +  0.3 * carre->w - texte_mise->w / 2;
  pos_mise.y = pos_carre.y + 3 * carre->h / 4 - texte_mise->h / 2;
  fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, 2 * texte_mise->w, texte_mise->h, 32, 0, 0, 0, 0);
  SDL_BlitSurface(texte_gehiago, NULL, ecran, &pos_gehiago);
  SDL_BlitSurface(texte_iduki, NULL, ecran, &pos_iduki);
  SDL_BlitSurface(texte_mise, NULL, ecran, &pos_mise);
  SDL_BlitSurface(texte_hordago, NULL, ecran, &pos_hordago);
  SDL_BlitSurface(moins, NULL, ecran, &pos_moins);
  SDL_BlitSurface(plus, NULL, ecran, &pos_plus);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
      if (event.button.y >= pos_hordago.y && event.button.y <= pos_hordago.y + texte_hordago->h) {
        if (event.button.x >= pos_hordago.x &&
            event.button.x <= pos_hordago.x + texte_hordago->w) {
          mise = -1;
          continuer = 0;
          break;
        }
        if (event.button.x >= pos_iduki.x &&
            event.button.x <= pos_iduki.x + texte_iduki->w) {
          mise = -3;
          continuer = 0;
          break;
        }
      }
      if (event.button.y >= (pos_gehiago.y) &&
          event.button.y <= (pos_gehiago.y + texte_gehiago->h)) { //Ligne du bas
        if (event.button.x >= (pos_moins.x) &&
            event.button.x <= (pos_moins.x + moins->w) &&
            mise > 2) { //moins
          mise --;
          itoa(mise, char_mise);
          texte_mise = TTF_RenderText_Blended(police, char_mise, couleurblanche);
          enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_mise);
          SDL_BlitSurface(texte_mise, NULL, ecran, &pos_mise);
          SDL_Flip(ecran);
          break;
        }
        if (event.button.x >= (pos_plus.x) &&
            event.button.x <= (pos_plus.x + plus->w) &&
            mise < 40) { //plus
          mise ++;
          itoa(mise, char_mise);
          texte_mise = TTF_RenderText_Blended(police, char_mise, couleurblanche);
          enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_mise);
          SDL_BlitSurface(texte_mise, NULL, ecran, &pos_mise);
          SDL_Flip(ecran);
          break;
        }
        if (event.button.x >= (pos_gehiago.x) &&
            event.button.x <= (pos_gehiago.x + texte_gehiago->w)) { //On valide la mise
          continuer = 0;
          break;
        }
      }
      case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        _exit(0);
        break;
      default:
        break;
      }
    }
  }
  SDL_Flip(ecran);
  TTF_CloseFont(police);
  SDL_FreeSurface(plus);
  SDL_FreeSurface(moins);
  SDL_FreeSurface(texte_hordago);
  SDL_FreeSurface(texte_iduki);
  SDL_FreeSurface(texte_gehiago);
  SDL_FreeSurface(texte_mise);
  return mise;
}

//Mise avant
int phase_de_mise_surenchir(SDL_Surface *ecran, SDL_Surface *carre, SDL_Rect pos_carre) {
  int mise, continuer = 1;
  char char_mise[4];
  SDL_Rect pos_hordago, pos_tira, pos_iduki, pos_gehiago, pos_plus, pos_moins, pos_mise;
  SDL_Color couleurblanche = {255, 255, 255};
  SDL_Surface *plus = IMG_Load("ressource/plus.png"), *moins = IMG_Load("ressource/moins.png"), *fond_noir = NULL;
  TTF_Font *police = NULL;
  SDL_Surface *texte_hordago = NULL, *texte_tira = NULL, *texte_iduki = NULL, *texte_gehiago = NULL, *texte_mise = NULL;
  SDL_Event event;
  police = TTF_OpenFont(CHOIX_POLICE(30));
  mise = 2;
  itoa(mise, char_mise);
  texte_tira = TTF_RenderText_Blended(police, "Tira", couleurblanche);
  texte_iduki = TTF_RenderText_Blended(police, "Iduki", couleurblanche);
  texte_gehiago = TTF_RenderText_Blended(police, "Gehiago", couleurblanche);
  texte_hordago = TTF_RenderText_Blended(police, "Hordago", couleurblanche);
  texte_mise = TTF_RenderText_Blended(police, char_mise, couleurblanche);
  pos_hordago.x = pos_carre.x + carre->w / 5 - texte_hordago->w / 2;
  pos_hordago.y = pos_carre.y + carre->h / 4 - texte_hordago->h / 2;
  pos_tira.x = pos_carre.x + 8 * carre->w / 15 - texte_tira->w / 2;
  pos_tira.y = pos_carre.y + carre->h / 4 - texte_tira->h / 2;
  pos_iduki.x = pos_carre.x + 5 * carre->w / 6 - texte_iduki->w / 2;
  pos_iduki.y = pos_carre.y + carre->h / 4 - texte_iduki->h / 2;
  pos_gehiago.x = pos_carre.x + 0.55 * carre->w - texte_gehiago->w / 2;
  pos_gehiago.y = pos_carre.y + 3 * carre->h / 4 - texte_gehiago->h / 2;
  pos_plus.x = pos_carre.x + 7 * carre->w / 8 - plus->w / 2;
  pos_plus.y = pos_carre.y + 3 * carre->h / 4 - plus->h / 2;
  pos_moins.x = pos_carre.x + carre->w / 8 - moins->w / 2;
  pos_moins.y = pos_carre.y + 3 * carre->h / 4 - moins->h / 2;
  pos_mise.x = pos_carre.x +  0.3 * carre->w - texte_mise->w / 2;
  pos_mise.y = pos_carre.y + 3 * carre->h / 4 - texte_mise->h / 2;
  SDL_BlitSurface(texte_hordago, NULL, ecran, &pos_hordago);
  SDL_BlitSurface(texte_tira, NULL, ecran, &pos_tira);
  SDL_BlitSurface(texte_iduki, NULL, ecran, &pos_iduki);
  SDL_BlitSurface(texte_gehiago, NULL, ecran, &pos_gehiago);
  SDL_BlitSurface(texte_mise, NULL, ecran, &pos_mise);
  SDL_BlitSurface(plus, NULL, ecran, &pos_plus);
  SDL_BlitSurface(moins, NULL, ecran, &pos_moins);
  SDL_Flip(ecran);
  fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, 2 * texte_mise->w, texte_mise->h, 32, 0, 0, 0, 0);
  while (continuer) { //Appuie sur les mises
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
      if (event.button.y >= (pos_hordago.y) &&
          event.button.y <= (pos_hordago.y + texte_hordago->h)) { //Cas de la ligne du haut
        if (event.button.x >= (pos_iduki.x) &&
            event.button.x <= (pos_iduki.x + texte_iduki->w)) { //Cas d'appuie sur iduki
          mise = -3;
          continuer = 0;
          break;
        }
        if (event.button.x >= (pos_tira.x) &&
            event.button.x <= (pos_tira.x + texte_tira->w)) { //Cas d'appuie sur tira
          mise = 1;
          continuer = 0;
          break;
        }
        if (event.button.x >= (pos_hordago.x) &&
            event.button.x <= (pos_hordago.x + texte_hordago->w)) { //Cas d'appuie sur hordago
          mise = -1;
          continuer = 0;
          break;
        }
      }
      if (event.button.y >= (pos_gehiago.y) &&
          event.button.y <= (pos_gehiago.y + texte_gehiago->h)) { //Ligne du bas
        if (event.button.x >= (pos_moins.x) &&
            event.button.x <= (pos_moins.x + moins->w) &&
            mise > 2) { //moins
          mise --;
          itoa(mise, char_mise);
          texte_mise = TTF_RenderText_Blended(police, char_mise, couleurblanche);
          enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_mise);
          SDL_BlitSurface(texte_mise, NULL, ecran, &pos_mise);
          SDL_Flip(ecran);
          break;
        }
        if (event.button.x >= (pos_plus.x) &&
            event.button.x <= (pos_plus.x + plus->w) &&
            mise < 40) { //plus
          mise ++;
          itoa(mise, char_mise);
          texte_mise = TTF_RenderText_Blended(police, char_mise, couleurblanche);
          enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_mise);
          SDL_BlitSurface(texte_mise, NULL, ecran, &pos_mise);
          SDL_Flip(ecran);
          break;
        }
        if (event.button.x >= (pos_gehiago.x) &&
            event.button.x <= (pos_gehiago.x + texte_gehiago->w)) { //On valide la mise
          continuer = 0;
          break;
        }
      }
      case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        _exit(0);
        break;
      default:
        break;
      }
    }
  }
  SDL_Flip(ecran);
  TTF_CloseFont(police);
  SDL_FreeSurface(plus);
  SDL_FreeSurface(moins);
  SDL_FreeSurface(texte_hordago);
  SDL_FreeSurface(texte_tira);
  SDL_FreeSurface(texte_iduki);
  SDL_FreeSurface(texte_gehiago);
  SDL_FreeSurface(texte_mise);
  return mise;
}

////////////////////////////////////////////////////////////////
////
////         Affichage et mise à jour des scores et phase
////
////////////////////////////////////////////////////////////////

void graphique_init_score(SDL_Surface *ecran) {
  SDL_Surface *boite = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w / 6, ecran->h / 6, 32, 0, 0, 0, 0);
  SDL_Color couleur_blanche = {255, 255, 255};
  SDL_Surface *texte_equipe1 = NULL, *texte_equipe2 = NULL, *score1 = NULL, *score2 = NULL, *manche1 = NULL, *manche2 = NULL;
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(15));
  SDL_Rect pos_boite, pos_equipe1, pos_equipe2, pos_score1, pos_score2, pos_manche1, pos_manche2;
  pos_boite.x = 0;
  pos_boite.y = 0;
  texte_equipe1 = TTF_RenderText_Blended(police, "Equipe 1 : ", couleur_blanche);
  texte_equipe2 = TTF_RenderText_Blended(police, "Equipe 2 : ", couleur_blanche);
  score1 = TTF_RenderText_Blended(police, "0", couleur_blanche);
  score2 = TTF_RenderText_Blended(police, "0", couleur_blanche);
  manche1 = TTF_RenderText_Blended(police, "(0)", couleur_blanche);
  manche2 = TTF_RenderText_Blended(police, "(0)", couleur_blanche);
  pos_equipe1.x = 20;
  pos_equipe1.y = boite->h / 4 - texte_equipe1->h / 2;
  pos_equipe2.x = 20;
  pos_equipe2.y = 3 * boite->h / 4 - texte_equipe2->h / 2;
  pos_score1.x = ecran->w / 10 - score1->w / 2;
  pos_score1.y = pos_equipe1.y;
  pos_score2.x = ecran->w / 10 - score2->w / 2;
  pos_score2.y = pos_equipe2.y;
  pos_manche1.x = ecran->w / 7 - manche1->w / 2;
  pos_manche1.y = pos_score1.y;
  pos_manche2.x = ecran->w / 7 - manche2->w / 2;
  pos_manche2.y = pos_equipe2.y;
  SDL_FillRect(boite, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  SDL_SetAlpha(boite, SDL_SRCALPHA, 180);
  SDL_BlitSurface(boite, NULL, ecran, &pos_boite);
  SDL_BlitSurface(texte_equipe1, NULL, ecran, &pos_equipe1);
  SDL_BlitSurface(score1, NULL, ecran, &pos_score1);
  SDL_BlitSurface(manche1, NULL, ecran, &pos_manche1);
  SDL_BlitSurface(texte_equipe2, NULL, ecran, &pos_equipe2);
  SDL_BlitSurface(score2, NULL, ecran, &pos_score2);
  SDL_BlitSurface(manche2, NULL, ecran, &pos_manche2);
  SDL_Flip(ecran);
  SDL_FreeSurface(boite);
  SDL_FreeSurface(score1);
  SDL_FreeSurface(score2);
  SDL_FreeSurface(texte_equipe1);
  SDL_FreeSurface(texte_equipe2);
  SDL_FreeSurface(manche1);
  SDL_FreeSurface(manche2);
  TTF_CloseFont(police);
}

void graphique_mise_a_jour_score(SDL_Surface *ecran, Partie *partie) {
  char score1[2], score2[2];
  itoa(partie->score[0], score1);
  itoa(partie->score[1], score2);
  SDL_Surface *texte_score1 = NULL, *texte_score2 = NULL, *test = NULL, *fond_noir = NULL;
  SDL_Color couleur_blanche = {255, 255, 255};
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(15));
  SDL_Rect pos_score1, pos_score2;
  texte_score1 = TTF_RenderText_Blended(police, score1, couleur_blanche);
  texte_score2 = TTF_RenderText_Blended(police, score2, couleur_blanche);
  test = TTF_RenderText_Blended(police, "10", couleur_blanche);
  // if (texte_score1->w > texte_score2->w)
  //   fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, texte_score1->w, texte_score1->h, 32, 0, 0, 0, 0);
  // else
  fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, test->w, test->h, 32, 0, 0, 0, 0);
  pos_score1.x = ecran->w / 10 - texte_score1->w / 2;
  pos_score1.y = ecran->h / 24 - texte_score1->h / 2;
  pos_score2.x = ecran->w / 10 - texte_score2->w / 2;
  pos_score2.y = ecran->h / 8 - texte_score2->h / 2;
  enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_score1);
  enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_score2);
  SDL_BlitSurface(texte_score1, NULL, ecran, &pos_score1);
  SDL_BlitSurface(texte_score2, NULL, ecran, &pos_score2);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond_noir);
  SDL_FreeSurface(texte_score1);
  SDL_FreeSurface(texte_score2);
}

void graphique_mise_a_jour_manche(SDL_Surface *ecran, Partie *partie) {
  char manche1[4], manche2[4], aux[2];
  itoa(partie->manche[0], aux);
  manche1[0] = '(';
  manche1[1] = aux[0];
  manche1[2] = ')';
  manche1[3] = 0;
  itoa(partie->manche[1], aux);
  manche2[0] = '(';
  manche2[1] = aux[0];
  manche2[2] = ')';
  manche2[3] = 0;
  SDL_Surface *texte_manche1 = NULL, *texte_manche2 = NULL, *fond_noir = NULL;
  SDL_Color couleur_blanche = {255, 255, 255};
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(15));
  SDL_Rect pos_manche1, pos_manche2;
  texte_manche1 = TTF_RenderText_Blended(police, manche1, couleur_blanche);
  texte_manche2 = TTF_RenderText_Blended(police, manche2, couleur_blanche);
  fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, texte_manche1->w, texte_manche1->h, 32, 0, 0, 0, 0);
  pos_manche1.x = ecran->w / 7 - texte_manche1->w / 2;
  pos_manche1.y = ecran->h / 24 - texte_manche1->h / 2;
  pos_manche2.x = ecran->w / 7 - texte_manche2->w / 2;
  pos_manche2.y = ecran->h / 8 - texte_manche2->h / 2;
  enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_manche1);
  enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos_manche2);
  SDL_BlitSurface(texte_manche1, NULL, ecran, &pos_manche1);
  SDL_BlitSurface(texte_manche2, NULL, ecran, &pos_manche2);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond_noir);
  SDL_FreeSurface(texte_manche1);
  SDL_FreeSurface(texte_manche2);
}

void init_score_phase(SDL_Surface *ecran) {
  SDL_Surface *boite = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w / 6, ecran->h / 6, 32, 0, 0, 0, 0);
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(15));
  SDL_Color couleur_blanche = {255, 255, 255};
  SDL_Surface *texte_haundia = NULL, *texte_tipia = NULL, *texte_pariak = NULL, *texte_jokua = NULL;
  SDL_Rect pos_boite, pos_haundia, pos_tipia, pos_pariak, pos_jokua;
  SDL_FillRect(boite, NULL, COULEUR_FOND);
  texte_haundia = TTF_RenderText_Blended(police, "Haundia :", couleur_blanche);
  texte_tipia = TTF_RenderText_Blended(police, "Tipia :", couleur_blanche);
  texte_pariak = TTF_RenderText_Blended(police, "Pariak :", couleur_blanche);
  texte_jokua = TTF_RenderText_Blended(police, "Jokua :", couleur_blanche);
  pos_boite.x = 0;
  pos_boite.y = ecran->h - boite->h;
  pos_haundia.x = 20;
  pos_haundia.y = pos_boite.y + 2 * boite->h / 10 - texte_haundia->h / 2;
  pos_tipia.x = 20;
  pos_tipia.y = pos_boite.y + 4 * boite->h / 10 - texte_tipia->h / 2;
  pos_pariak.x = 20;
  pos_pariak.y = pos_boite.y + 6 * boite->h / 10 - texte_pariak->h / 2;
  pos_jokua.x = 20;
  pos_jokua.y = pos_boite.y + 8 * boite->h / 10 - texte_jokua->h / 2;
  SDL_BlitSurface(boite, NULL, ecran, &pos_boite);
  SDL_FillRect(boite, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  SDL_SetAlpha(boite, SDL_SRCALPHA, 180);
  SDL_BlitSurface(boite, NULL, ecran, &pos_boite);
  SDL_BlitSurface(texte_haundia, NULL, ecran, &pos_haundia);
  SDL_BlitSurface(texte_tipia, NULL, ecran, &pos_tipia);
  SDL_BlitSurface(texte_pariak, NULL, ecran, &pos_pariak);
  SDL_BlitSurface(texte_jokua, NULL, ecran, &pos_jokua);
  SDL_Flip(ecran);
}

void enleve_phase(SDL_Surface *ecran, SDL_Rect pos, SDL_Surface *texte) {
  SDL_Surface *fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, texte->w, texte->h, 32, 0, 0, 0, 0);
  enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos);
}

void mise_a_jour_phase_actuel(SDL_Surface *ecran, Gppj phase) {
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(15));
  TTF_Font *police1 = TTF_OpenFont(CHOIX_POLICE(15));
  SDL_Color couleur_blanche = {255, 255, 255};
  SDL_Surface *texte = NULL;
  SDL_Rect pos, pos_boite;
  int boite_h = ecran->h / 6;
  pos.x = 20;
  pos_boite.y = 5 * ecran->h / 6;
  TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE);
  if (phase == GRAND) {
    texte = TTF_RenderText_Blended(police, "Haundia :", couleur_blanche);
    pos.y = pos_boite.y + 2 * boite_h / 10 - texte->h / 2;
    enleve_phase(ecran, pos, texte);
  }
  else if (phase == PETIT) {
    texte = TTF_RenderText_Blended(police, "Haundia :", couleur_blanche);
    pos.y = pos_boite.y + 2 * boite_h / 10 - texte->h / 2;
    enleve_phase(ecran, pos, texte);
    texte = TTF_RenderText_Blended(police1, "Haundia :", couleur_blanche);
    SDL_BlitSurface(texte, NULL, ecran, &pos);
    texte = TTF_RenderText_Blended(police, "Tipia :", couleur_blanche);
    pos.y = pos_boite.y + 4 * boite_h / 10 - texte->h / 2;
    enleve_phase(ecran, pos, texte);
  }
  else if (phase == PAIRE) {
    texte = TTF_RenderText_Blended(police, "Tipia :", couleur_blanche);
    pos.y = pos_boite.y + 4 * boite_h / 10 - texte->h / 2;
    enleve_phase(ecran, pos, texte);
    texte = TTF_RenderText_Blended(police1, "Tipia :", couleur_blanche);
    SDL_BlitSurface(texte, NULL, ecran, &pos);
    texte = TTF_RenderText_Blended(police, "Pariak :", couleur_blanche);
    pos.y = pos_boite.y + 6 * boite_h / 10 - texte->h / 2;
    enleve_phase(ecran, pos, texte);
  }
  else if (phase == FAUXJEU) {
    texte = TTF_RenderText_Blended(police, "Pariak :", couleur_blanche);
    pos.y = pos_boite.y + 6 * boite_h / 10 - texte->h / 2;
    enleve_phase(ecran, pos, texte);
    texte = TTF_RenderText_Blended(police1, "Pariak :", couleur_blanche);
    SDL_BlitSurface(texte, NULL, ecran, &pos);
    texte = TTF_RenderText_Blended(police, "Pundia :", couleur_blanche);
    pos.y = pos_boite.y + 8 * boite_h / 10 - texte->h / 2;
    enleve_phase(ecran, pos, texte);
  }
  else {
    texte = TTF_RenderText_Blended(police, "Pariak :", couleur_blanche);
    pos.y = pos_boite.y + 6 * boite_h / 10 - texte->h / 2;
    enleve_phase(ecran, pos, texte);
    texte = TTF_RenderText_Blended(police1, "Pariak :", couleur_blanche);
    SDL_BlitSurface(texte, NULL, ecran, &pos);
    texte = TTF_RenderText_Blended(police, "Jokua :", couleur_blanche);
    pos.y = pos_boite.y + 8 * boite_h / 10 - texte->h / 2;
    enleve_phase(ecran, pos, texte);
  }
  SDL_BlitSurface(texte, NULL, ecran, &pos);
  SDL_Flip(ecran);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
}

void mise_a_jour_phase_score(SDL_Surface *ecran, Phase phase) {
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(15));
  SDL_Color couleur_blanche = {255, 255, 255};
  SDL_Surface *texte_mise = NULL, *fond_noir = NULL, *texte_gagnant = NULL;
  SDL_Rect pos, pos_boite;
  int boite_h = ecran->h / 6;
  char mise[3], gagnant[5];
  fond_noir = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 15, 32, 0, 0, 0, 0);
  itoa(phase.mise, mise);
  texte_mise = TTF_RenderText_Blended(police, mise, couleur_blanche);
  pos.x = ecran->w / 9 - texte_mise->w / 2;
  pos_boite.y = 5 * ecran->h / 6;
  if (phase.phase == GRAND) {
    pos.y = pos_boite.y + 2 * boite_h / 10 - texte_mise->h / 2;
  }
  else if (phase.phase == PETIT) {
    pos.y = pos_boite.y + 4 * boite_h / 10 - texte_mise->h / 2;

  }
  else if (phase.phase == PAIRE) {
    pos.y = pos_boite.y + 6 * boite_h / 10 - texte_mise->h / 2;
  }
  else {
    pos.y = pos_boite.y + 8 * boite_h / 10 - texte_mise->h / 2;
  }
  if (phase.gagnant == AUCUN) {
    gagnant[0] = '(';
    gagnant[1] = '?';
    gagnant[2] = ')';
    gagnant[3] = 0;
  }
  else if (phase.gagnant == NOJOUEUR) {
    gagnant[0] = '(';
    gagnant[1] = 'x';
    gagnant[2] = ')';
    gagnant[3] = 0;
  }
  else {
    itoa(phase.gagnant, gagnant);
    gagnant[1] = gagnant[0] + 1;
    gagnant[0] = '(';
    gagnant[2] = ')';
    gagnant[3] = 0;
  }
  texte_gagnant = TTF_RenderText_Blended(police, gagnant, couleur_blanche);
  enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos);
  SDL_BlitSurface(texte_mise, NULL, ecran, &pos);
  pos.x += 20;
  enleve_ecriture_sur_fond_noir(ecran, fond_noir, pos);
  SDL_BlitSurface(texte_gagnant, NULL, ecran, &pos);
  SDL_Flip(ecran);
}

////////////////////////////////////////////////////////////////
////
////         Affichage message gagnant et fin tour
////
////////////////////////////////////////////////////////////////

void message_joueur_suivant(SDL_Surface *ecran, Partie *partie, int joueur) {
  SDL_Surface *texte = NULL, *fond = NULL;
  char txt[100] = "C'est au joueur ";
  char txt1[100] = " de jouer";
  strcat(txt, partie->joueurs[joueur].nom);
  strcat(txt, txt1);
  SDL_Color couleur_blanche = {255, 255, 255};
  SDL_Event event;
  int continuer = 1;
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(20));
  SDL_Rect pos_texte;
  texte = TTF_RenderText_Blended(police, txt, couleur_blanche);
  pos_texte.x = ecran->w / 2 - texte->w / 2;
  pos_texte.y = ecran->h / 2 - texte->h / 2;
  fond = SDL_CreateRGBSurface(SDL_HWSURFACE, texte->w, texte->h, 32, 0, 0, 0, 0);
  SDL_BlitSurface(texte, NULL, ecran, &pos_texte);
  graphique_affiche_main_cachee(ecran);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_KEYDOWN:
      continuer = 0;
      break;
    }
  }
  SDL_FillRect(fond, NULL, COULEUR_FOND);
  SDL_BlitSurface(fond, NULL, ecran, &pos_texte);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}

void message_fin_tour(SDL_Surface *ecran) {
  SDL_Surface *fond = NULL, *texte = NULL;
  SDL_Color couleur_blanche = {255, 255, 255};
  SDL_Event event;
  int continuer = 1;
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(20));
  SDL_Rect pos_texte;
  texte = TTF_RenderText_Blended(police, "Appuyer sur une touche pour continuer", couleur_blanche);
  pos_texte.x = ecran->w / 2 - texte->w / 2;
  pos_texte.y = ecran->h / 2 - texte->h / 2;
  fond = SDL_CreateRGBSurface(SDL_HWSURFACE, texte->w, texte->h, 32, 0, 0, 0, 0);
  SDL_BlitSurface(texte, NULL, ecran, &pos_texte);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_KEYDOWN:
      continuer = 0;
      break;
    }
  }
  SDL_FillRect(fond, NULL, COULEUR_FOND);
  SDL_BlitSurface(fond, NULL, ecran, &pos_texte);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}

void affiche_message_oui_non(SDL_Surface *ecran, Direction d, bool oui_non) {
  SDL_Surface *texte = NULL;
  SDL_Color couleur_blanche = {255, 255, 255};
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(20));
  SDL_Rect pos;
  if (oui_non)
    texte = TTF_RenderText_Blended(police, "Ba", couleur_blanche);
  else
    texte = TTF_RenderText_Blended(police, "Ez", couleur_blanche);
  if (d == BAS || d == HAUT) {
    pos.x = ecran->w / 2 - texte->w / 2;
    if (d == BAS)
      pos.y = ecran->h - 1.5 * LONGUEUR_CARTE;
    else
      pos.y = 1.5 * LONGUEUR_CARTE;
  }
  else {
    pos.y = ecran->h / 2 - texte->h / 2;
    if (d == DROITE)
      pos.x = ecran->w - 1.5 * LONGUEUR_CARTE;
    else
      pos.x = 1.5 * LONGUEUR_CARTE;
  }
  SDL_BlitSurface(texte, NULL, ecran, &pos);
  SDL_Flip(ecran);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
}

void enleve_message_oui_non(SDL_Surface *ecran, Direction d) {
  SDL_Surface *fond = SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32, 32, 0, 0, 0, 0);
  SDL_Rect pos;
  SDL_FillRect(fond, NULL, COULEUR_FOND);
  if (d == BAS || d == HAUT) {
    pos.x = ecran->w / 2 - 20;
    if (d == BAS)
      pos.y = ecran->h - 1.5 * LONGUEUR_CARTE;
    else
      pos.y = 1.5 * LONGUEUR_CARTE;
  }
  else {
    pos.y = ecran->h / 2 - 20;
    if (d == DROITE)
      pos.x = ecran->w - 1.5 * LONGUEUR_CARTE;
    else
      pos.x = 1.5 * LONGUEUR_CARTE;
  }
  SDL_BlitSurface(fond, NULL, ecran, &pos);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond);
}

void message_oui_non(SDL_Surface *ecran, Partie *partie, bool tab_joueur[]) {
  graphique_affiche_main_cachee(ecran);
  int esku = partie->nb_tours % 4;
  enlever_nom_joueurs(ecran);
  affiche_nom_joueurs(ecran, partie, modulo_4_neg(esku));
  enlever_paquet_4_endroit(ecran);
  affiche_paquet_esku(ecran, 0);
  for (int i = 0; i < 4; i++) {
    affiche_message_oui_non(ecran, i, tab_joueur[(esku + i) % 4]);
    SDL_Delay(500);
  }
  for (int i = 0; i < 4; i++)
    enleve_message_oui_non(ecran, i);
}

void affiche_gagnant_manche(SDL_Surface *ecran, int gagnant) {
  SDL_Surface *fond = NULL, *texte = NULL;
  SDL_Color couleur_blanche = {255, 255, 255};
  SDL_Event event;
  int continuer = 1;
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(20));
  SDL_Rect pos_texte;
  char txt[100] = "";
  char *equipe = "L'equipe ";
  char num[2];
  char *a_gagne = " a gagne cette manche";
  itoa(gagnant, num);
  strcat(txt, equipe);
  strcat(txt, num);
  strcat(txt, a_gagne);
  texte = TTF_RenderText_Blended(police, txt, couleur_blanche);
  pos_texte.x = ecran->w / 2 - texte->w / 2;
  pos_texte.y = ecran->h / 2 - texte->h / 2;
  fond = SDL_CreateRGBSurface(SDL_HWSURFACE, texte->w, texte->h, 32, 0, 0, 0, 0);
  SDL_BlitSurface(texte, NULL, ecran, &pos_texte);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_KEYDOWN:
      continuer = 0;
      break;
    }
  }
  SDL_FillRect(fond, NULL, COULEUR_FOND);
  SDL_BlitSurface(fond, NULL, ecran, &pos_texte);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}

void affiche_gagnant_partie(SDL_Surface *ecran, int gagnant) {
  SDL_Surface *fond = NULL, *texte = NULL;
  SDL_Color couleur_blanche = {255, 255, 255};
  SDL_Event event;
  int continuer = 1;
  TTF_Font *police = TTF_OpenFont(CHOIX_POLICE(20));
  SDL_Rect pos_texte;
  char txt[100] = "";
  char *equipe = "L'equipe ";
  char num[2];
  char *a_gagne = " a gagne la partie";
  itoa(gagnant, num);
  strcat(txt, equipe);
  strcat(txt, num);
  strcat(txt, a_gagne);
  texte = TTF_RenderText_Blended(police, txt, couleur_blanche);
  pos_texte.x = ecran->w / 2 - texte->w / 2;
  pos_texte.y = ecran->h / 2 - texte->h / 2;
  fond = SDL_CreateRGBSurface(SDL_HWSURFACE, texte->w, texte->h, 32, 0, 0, 0, 0);
  SDL_BlitSurface(texte, NULL, ecran, &pos_texte);
  SDL_Flip(ecran);
  while (continuer) {
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_KEYDOWN:
      continuer = 0;
      break;
    }
  }
  SDL_FillRect(fond, NULL, COULEUR_FOND);
  SDL_BlitSurface(fond, NULL, ecran, &pos_texte);
  SDL_Flip(ecran);
  SDL_FreeSurface(fond);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}



