#ifndef __CONST_H__
#define __CONST_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TAILLE_FONT 65

#define PATH_IMG_MUR "./kenney_roadtextures_2/Tilesheet/roadTextures_tilesheet@2.png"
#define PATH_IMG_PERSO "./textures/character.png"
#define PATH_IMG_BOULE "./textures/pokeboulev2.png"
#define PATH_FONT "./fonts/Pacifico.ttf"

#define PERSO_POS 312



#define HAUTEUR_FENETRE 800
#define LARGEUR_FENETRE 1000

#define NB_LIGNE_LABY 25
#define NB_COLONNE_LABY 25

#define NB_ELT_MAX (NB_LIGNE_LABY * NB_COLONNE_LABY)

#define N (NB_LIGNE_LABY * NB_COLONNE_LABY)
#define NB_LIGNE_MAT N
#define NB_COLONNE_MAT N

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define ALEA_GEN 10
#define GRAINE 10
#define P_ALEA_MUR 0.05

#define LARGEUR_CASE (LARGEUR_FENETRE / NB_COLONNE_LABY)
#define HAUTEUR_CASE (HAUTEUR_FENETRE / NB_LIGNE_LABY)

#define VITESSE_MIN -1
#define VITESSE_MAX 1

#define NB_BOULES 4


typedef struct couple
{
    int d;
    int n;
} couple_t;

typedef struct arete
{
    int a;
    int b;
    int poids;
} arete_t;

typedef struct graph_l_arete
{
    int nb_noeud;
    int nb_arete;
    arete_t *liste_arete;
} graph_l_arete_t;

typedef struct tas_binaire
{
    couple_t tas[N];
    int nb_elt;
    int info_n[N];
    int indice_tas[N];
} tas_binaire_t;

typedef struct entite
{
    int pos_prec;
    int pos_cour;
    int vitesse;
    int vertical;
    int horizontal;
    SDL_Texture *texture;
} entite_t;

typedef struct bombe
{
    int pos_cour;
    int rayon_action;
    int temps;
    SDL_Texture *texture;
} bombe_t;

#include "ui.h"
#include "gestion_bombes.h"
#include "perso.h"
#include "gestion_entites.h"
#include "gestion_boule.h"
#include "gestion_map.h"
#include "tas_binaire.h"
#include "liste_chainee.h"
#include "partition.h"
#include "connexe.h"
#include "labyrinthe.h"
#include "kruskal.h"
#include "parcours_graphe.h"

#endif