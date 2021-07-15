#ifndef __vie_h__
#define __vie_h__

void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer);
int devenir(int mat[LIGNES][COLONNES], int *i, int *j);
void evolution(int mat[LIGNES][COLONNES], int matsuiv[LIGNES][COLONNES]);
void draw(SDL_Renderer* renderer, int mat[LIGNES][COLONNES], int *h, int *l);
void init(int mat[LIGNES][COLONNES]);

#endif