#ifndef __UI_H__
#define __UI_H__

#include "const.h"

char *texte_score(int a);
void affichage_texte(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, char *texte, float taille, int x, int y);
void ecran_fin(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, int coll);

#endif
