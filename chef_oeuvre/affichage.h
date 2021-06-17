#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define TAILLE_FONT 65
#define PATH_FONT "../exemples_executables/fonts/arial.ttf"

void affichage_texte(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, char *texte, int taille, int x, int y);
void affichage_bgScroll(SDL_Window * window,SDL_Renderer * renderer, SDL_Texture * bg,SDL_Texture * bg2, int * cordy_bg,int * cordy_bg2);
#endif