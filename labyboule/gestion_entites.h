#ifndef __gestion_entites_h__
#define __gestion_entites_h__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "const.h"

void creer_entite(SDL_Window *window, SDL_Renderer *renderer, int pos_prec, int pos_cour, float vitesse, int vertical, int horizontal, entite_t **pentite, char *chemin);
void charger_texture(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, char *chemin);
void liberer_entite(entite_t **p_entite);
void affichage_entite(SDL_Window *, SDL_Renderer *, entite_t *, int delta_tps, float anim);
int collision(int delta, entite_t *perso, entite_t *liste_boule[NB_BOULES], int *nb_boules, bombe_t *liste_bombes[NB_BOMBES], int *nb_bombes, int map[NB_LIGNE_LABY][NB_COLONNE_LABY]);
SDL_Rect rectangle_sprite(entite_t *entite, int delta_tps, int zoom);

#endif
