#ifndef __gestion_bombes_h__
#define __gestion_bombes_h__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "const.h"

void creer_bombe(SDL_Window *window, SDL_Renderer *renderer,
                 int pos_cour, int rayon_action, int temps, int pose_bombe,
                 bombe_t **pbombe);

void ajouter_bombe(SDL_Window *window, SDL_Renderer *renderer,
                   bombe_t *liste_bombes[NB_BOMBES], int *nb_bombes,
                   entite_t *perso);

void charger_texture_bombe(SDL_Window *window, SDL_Renderer *renderer,
                           bombe_t *bombe, char *chemin);

SDL_bool check_deja_bombe(bombe_t *liste_bombes[NB_BOMBES], int pos);

void affichage_liste_bombes(SDL_Window *window, SDL_Renderer *renderer,
                            bombe_t *liste_bombes[NB_BOMBES]);

void affichage_bombe(SDL_Window *window, SDL_Renderer *renderer,
                     bombe_t *bombe);

void liberer_bombe(bombe_t **p_bombe);
int explosion(bombe_t *bombe, entite_t *perso, entite_t *tab_boule[NB_BOULES], int map[NB_LIGNE_LABY][NB_COLONNE_LABY]);
int collision_bombe(entite_t *perso, entite_t *tab_boule[NB_BOULES], int i, int j);

#endif