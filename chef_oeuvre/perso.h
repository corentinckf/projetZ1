#ifndef __PERSO_H__
#define __PERSO_H__

#include "main.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NB_IMG_PERSO 9
#define NB_MAX_CHAR_PATH 500
#define PATH_IMG_PERSO "/home/local.isima.fr/mavilledie4/shared/projetZ1/chef_oeuvre/img2/redfighter000"
#define PATH_IMG_PERSO_EXT ".png"

#define LARGEUR_PERSO 1
#define HAUTEUR_PERSO 1

#define X_POS_PERSO_DEPART 0
#define Y_POS_PERSO_DEPART 0

typedef struct perso
{
    SDL_Texture *sprite[NB_IMG_PERSO];
    SDL_Rect info;
    int direction;
    int score;
} perso_t;

int main_perso(SDL_Window *, SDL_Renderer *);

perso_t *creer_perso(SDL_Window *window, SDL_Renderer *renderer);
void supp_perso(perso_t *perso);

void deplacement_perso(perso_t *perso, int *vitesse);
int calcul_dir_anim_perso(int a);

void play_with_texture_perso(perso_t *perso, SDL_Window *window, SDL_Renderer *renderer);
char *path_perso_determine(int n);

void play_texture_xy(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);

#endif