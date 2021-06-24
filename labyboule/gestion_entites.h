#ifndef __gestion_boules_h__
#define __gestion_boules_h__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "const.h"

typedef struct entite{
    int pos_prec;
    int pos_cour;
    int vitesse;
    int vertical;
    int horizontal;
    SDL_Texture *texture;
}entite_t;

void creer_entite(SDL_Window *window, SDL_Renderer *renderer, int pos_prec, int pos_cour, int vitesse, int vertical, int horizontal, entite_t *entite, char *chemin);
void charger_texture(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, char *chemin);
void liberer(entite_t *entite);

#endif