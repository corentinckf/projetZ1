#ifndef __gestion_bombes_h__
#define __gestion_bombes_h__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "const.h"

void creer_bombe(SDL_Window *window, SDL_Renderer *renderer, int pos_cour, int rayon_action, int temps, int pose_bombe, bombe_t **pbombe, char *chemin);
void charger_texture_bombe(SDL_Window *window, SDL_Renderer *renderer, bombe_t *bombe, char *chemin);
void affichage_bombe(SDL_Window *window, SDL_Renderer *renderer, bombe_t *bombe);
void liberer_bombe(bombe_t *bombe);
int explosion(bombe_t *bombe, entite_t *perso, entite_t *tab_boule[NB_BOULES], int map[NB_LIGNE_LABY][NB_COLONNE_LABY]);
int collision_bombe(entite_t *perso, entite_t *tab_boule[NB_BOULES],int i, int j);

#endif