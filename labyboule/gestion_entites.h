#ifndef __gestion_entites_h__
#define __gestion_entites_h__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "const.h"

void creer_entite(SDL_Window *window, SDL_Renderer *renderer, int pos_prec, int pos_cour, int vitesse, int vertical, int horizontal, entite_t **pentite, char *chemin);
void charger_texture(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, char *chemin);
void liberer_entite(entite_t *entite);
void affichage_entite(SDL_Window *, SDL_Renderer *,entite_t*, int *temps);
int collision(entite_t *perso, entite_t *liste_boule[NB_BOULES]);

#endif