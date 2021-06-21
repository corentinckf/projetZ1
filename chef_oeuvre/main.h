#ifndef __MAIN_H__
#define __MAIN_H__

#include "perso.h"
#include "affichage.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PATH_IMG_ITEM "./img2/buttons.png"
#define PATH_IMG_BG "./img2/bg.png"

#define HAUTEUR_FENETRE 900
#define LARGEUR_FENETRE 500

#define HAUTEUR_GRILLE 20
#define LARGEUR_GRILLE 10

#define HAUTEUR_PIXEL HAUTEUR_FENETRE / HAUTEUR_GRILLE
#define LARGEUR_PIXEL LARGEUR_FENETRE / LARGEUR_GRILLE

#define GOAL_SCORE 100

void init_map(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE]);

void end_sdl(char, char const *, SDL_Window *, SDL_Renderer *);
char *texte_score(int a);


void init_grille(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE]);
void evolution(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE],int *etape);
void afficher_grille(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE]);
void draw(SDL_Renderer* renderer, int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], SDL_Texture *planche, int *etape, int *hauteur_pixel, int *largeur_pixel);

#endif