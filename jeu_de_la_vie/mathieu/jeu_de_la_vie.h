#ifndef __JEU_DE_LA_VIE__
#define __JEU_DE_LA_VIE__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HAUTEUR_FENETRE 600
#define LARGEUR_FENETRE 1000

#define HAUTEUR_GRILLE 30
#define LARGEUR_GRILLE 50

//conserver le meme ratio
//HAUTEUR_FENETRE / LARGEUR_FENETRE et HAUTEUR_GRILLE / LARGEUR_GRILLE

#define TAILLE_PIXEL 20

#define HAUTEUR_PIXEL LARGEUR_FENETRE / HAUTEUR_GRILLE
#define LARGEUR_PIXEL LARGEUR_FENETRE / LARGEUR_GRILLE

#define NB_COULEURS 2
#define TRUE 1
#define FALSE 0

#define N 500
#define VITESSE_BASE 100

int couleurs[NB_COULEURS][3] = {{255, 255, 255}, //0 mort blanc : 255 255 255
                                {0, 0, 0}};      //1 vivant : 0 0 0

//B0123478/S01234678
int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 1, 1};
int survie[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0};

void placement_config_depart_alea(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE]);
void init_map(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE]);
void etape(int super_grille[2][HAUTEUR_GRILLE][LARGEUR_GRILLE], int n);
int cb_nb_voisins(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], int x, int y);
void draw(SDL_Renderer *renderer, int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], int couleur[NB_COULEURS][3]);

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);

void placement_cellule_souris(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], int i, int j);

#endif