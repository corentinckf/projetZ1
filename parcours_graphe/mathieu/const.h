#ifndef __CONST_H__
#define __CONST_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define PATH_IMG_MUR "./kenney_roadtextures_2/Tilesheet/roadTextures_tilesheet@2.png"

#define HAUTEUR_FENETRE 800
#define LARGEUR_FENETRE 1500

#define NB_LIGNE_LABY 20
#define NB_COLONNE_LABY 35

#define NB_ELT_MAX (NB_LIGNE_LABY * NB_COLONNE_LABY)

#define N NB_ELT_MAX
#define NB_LIGNE_MAT N
#define NB_COLONNE_MAT N

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define ALEA_GEN 10
#define GRAINE 48

#define LARGEUR_CASE LARGEUR_FENETRE / NB_COLONNE_LABY
#define HAUTEUR_CASE HAUTEUR_FENETRE / NB_LIGNE_LABY

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


#include "tas_binaire.h"
#include "liste_chainee.h"
#include "partition.h"
#include "connexe.h"
#include "labyrinthe.h"
#include "kruskal.h"
#include "parcours_graphe.h"

#endif