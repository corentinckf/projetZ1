#ifndef __UI_H__
#define __UI_H__

void affichage_texte(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, char *texte, int taille, int x, int y);
void ecran_fin(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, int coll);

#endif
