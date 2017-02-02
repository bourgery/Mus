#include "jeu.h"
#include "jeu_IA.h"
#include "affichage.h"
#include <stdio.h>

int main() {
  init_rand();
  SDL_Surface *ecran = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  const SDL_VideoInfo *info_ecran = SDL_GetVideoInfo();
  ecran = SDL_SetVideoMode(info_ecran->current_w, info_ecran->current_h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
  SDL_FillRect(ecran, NULL, COULEUR_FOND);
  SDL_Flip(ecran);
  jeu(ecran);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
