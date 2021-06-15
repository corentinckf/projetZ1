#ifndef __MAIN_H__
#define __MAIN_H__
#include "util_sdl.h"

#define IMG_BACKGROUND "/home/local.isima.fr/mavilledie4/shared/projetZ1/exemples_executables/img/nasa-xFO2Xt33xgI-unsplash.jpg"
#define IMG_TROU_NOIR "/home/local.isima.fr/mavilledie4/shared/projetZ1/exemples_executables/img/trou-noir.png"
#define IMG_SPRITE "/home/local.isima.fr/mavilledie4/shared/projetZ1/exemples_executables/img/player-spritemap-v9.png"

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 1000
#define NOM_FENETRE "Fenêtre"

#define LARGEUR_MATRICE 100
#define HAUTEUR_MATRICE 100

#define TAILLE_PIXEL 10

void draw(SDL_Renderer *renderer, int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int couleurs[10][3]);
void init_map(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE]);
void placement_perso(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int x_perso, int y_perso);
void effacement_perso(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int x_perso, int y_perso);
int dessine_perso(int i, int j);

void play_texture_full_window(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_texture_xy(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, int x, int y);

#endif
