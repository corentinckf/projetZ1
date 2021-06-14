#ifndef __ANIMATION_SIMPLE__
#define __ANIMATION_SIMPLE__

#include <SDL2/SDL.h>
#include <stdio.h>

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 800


void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
void draw(SDL_Renderer *renderer, int x_pos, int y_pos);
void affichage_perso(SDL_Renderer *renderer, int x_pos, int y_pos);

#endif