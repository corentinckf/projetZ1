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

#define HAUTEUR_FENETRE 1000
#define LARGEUR_FENETRE 500

#define HAUTEUR_GRILLE 20
#define LARGEUR_GRILLE 10

#define HAUTEUR_PIXEL HAUTEUR_FENETRE/HAUTEUR_GRILLE
#define LARGEUR_PIXEL LARGEUR_FENETRE/LARGEUR_GRILLE




void end_sdl(char,char const *, SDL_Window*, SDL_Renderer*);


#endif