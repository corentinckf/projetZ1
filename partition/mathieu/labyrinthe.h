#ifndef __LABYRINTHE_H__
#define __LABYRINTHE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.h"
#include "connexe.h"
#include "partition.h"
#include "kruskal.h"

enum murs
{
    rien = 0,      //0
    mur_est = 1,   //1
    mur_nord = 2,  //2
    mur_ouest = 4, //4
    mur_sud = 8    //8
};

int main_labyrinthe(int map[NB_LIGNE_LABY][NB_COLONNE_LABY]);

void permute_a_b(int *a, int *b);
void melange_fisher_yates_arete(graph_couple_t *graph);

void construire_map(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], graph_couple_t *graph);

void dessiner(SDL_Window *window, SDL_Renderer *renderer, int map[NB_LIGNE_LABY][NB_COLONNE_LABY]);
void trace_mur(SDL_Window *window, SDL_Renderer *renderer, int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int i, int j);

void play_texture_mur(SDL_Window *window, SDL_Renderer *renderer, int map[NB_LIGNE_LABY][NB_COLONNE_LABY]);

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);

#endif