#ifndef __MAIN_H__
#define __MAIN_H__

#include "perso.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define HAUTEUR_FENETRE 800
#define LARGEUR_FENETRE 1000

#define HAUTEUR_GRILLE 100
#define LARGEUR_GRILLE 100

#define HAUTEUR_PIXEL HAUTEUR_FENETRE/HAUTEUR_GRILLE
#define LARGEUR_PIXEL LARGEUR_FENETRE/LARGEUR_GRILLE




void end_sdl(char,char const *, SDL_Window*, SDL_Renderer*);


#endif