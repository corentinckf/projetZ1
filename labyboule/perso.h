#ifndef __PERSO_H__
#define __PERSO_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define HAUTEUR_FENETRE 250
#define LARGEUR_FENETRE 250

#define NB_LIGNE_LABY 25
#define NB_COLONNE_LABY 25

#define LARGEUR_CASE LARGEUR_FENETRE / NB_COLONNE_LABY
#define HAUTEUR_CASE HAUTEUR_FENETRE / NB_LIGNE_LABY

#define NB_IMG_PERSO 9
#define NB_MAX_CHAR_PATH 500
#define PATH_IMG_PERSO "./textures/character.png"
#define PATH_IMG_PERSO_EXT ".png"

#define LARGEUR_PERSO LARGEUR_PIXEL
#define HAUTEUR_PERSO HAUTEUR_PIXEL

#define VITESSE_HORIZONTAL 2
#define VITESSE_MIN -4
#define VITESSE_MAX 4

#define X_POS_PERSO_DEPART 0
#define Y_POS_PERSO_DEPART 0


void affichage_entite(SDL_Window *, SDL_Renderer *,SDL_Texture *,int*, int*, int*, int*);
int end_sdl(char , char const *, SDL_Window *, SDL_Renderer *);



#endif