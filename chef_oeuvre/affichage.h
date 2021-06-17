#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define TAILLE_FONT 65
#define PATH_FONT "/home/local.isima.fr/mavilledie4/shared/projetZ1/exemples_executables/fonts/arial.ttf"

void affichage_texte(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, char *texte, int taille, int x, int y);

#endif