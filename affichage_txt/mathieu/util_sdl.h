#ifndef __UTIL_SDL_H__
#define __UTIL_SDL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define HAUTEUR_FENETRE 600
#define LARGEUR_FENETRE 1000


SDL_Window * initWindow(int , int, int, int, char *);
int end_sdl(char,char const *, SDL_Window*, SDL_Renderer*);
#endif