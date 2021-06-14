#ifndef __ANIMATION_SIMPLE__
#define __ANIMATION_SIMPLE__

#include <SDL2/SDL.h>
#include <stdio.h>

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 500

#define LARGEUR_MATRICE 300
#define HAUTEUR_MATRICE 200

#define HAUTEUR_PIXEL LARGEUR_FENETRE / HAUTEUR_MATRICE
#define LARGEUR_PIXEL LARGEUR_FENETRE / LARGEUR_MATRICE

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
void init_map(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE]);
void draw(SDL_Renderer *renderer, int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int couleurs[10][3]);

void placement_perso(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int x_pos, int y_pos);
int dessine_perso(int i, int j);

#endif