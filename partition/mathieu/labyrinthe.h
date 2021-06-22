#ifndef __LABYRINTHE_H__
#define __LABYRINTHE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.h"
#include "connexe.h"
#include "partition.h"
#include "kruskal.h"



int main_labyrinthe();

void permute_a_b(int *a, int *b);
void melange_fisher_yates_arete(graph_couple_t *graph);

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);

#endif