#ifndef __JEU_DE_LA_VIE__
#define __JEU_DE_LA_VIE__

#include <SDL2/SDL.h>
#include <stdio.h>

#define HAUTEUR_FENETRE 300
#define LARGEUR_FENETRE 500

#define HAUTEUR_GRILLE 30
#define LARGEUR_GRILLE 50

#define TAILLE_PIXEL 5

#define HAUTEUR_PIXEL LARGEUR_FENETRE / HAUTEUR_GRILLE
#define LARGEUR_PIXEL LARGEUR_FENETRE / LARGEUR_GRILLE

#define NB_COULEURS 2
#define TRUE 1
#define FALSE 0

#define N 100

int couleurs[NB_COULEURS][3] = {{255, 255, 255}, //0 mort blanc : 255 255 255
                                {0, 0, 0}};      //1 vivant : 0 0 0

//B0123478/S01234678
int naissance[9] = {'1', '1', '1', '1', '1', '0', '0', '1', '1'};
int survie[9] = {'1', '1', '1', '1', '1', '0', '1', '1','1'};


void placement_config_depart(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE]);
void init_map(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE]);
void etape(int super_grille[2][HAUTEUR_GRILLE][LARGEUR_GRILLE], int n);
int cb_nb_voisins(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], int x, int y);
void draw(SDL_Renderer *renderer, int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], int couleur[NB_COULEURS][3]);

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);

#endif