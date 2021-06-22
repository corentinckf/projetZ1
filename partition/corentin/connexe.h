#ifndef __CONNEXE_H__
#define __CONNEXE_H__


#include <stdio.h>
#include <stdlib.h>
#include "lch.h"

#define MAT_SIZE 10

typedef struct noeud
{
    int a;
    int b;
}noeud_t;

typedef struct graph
{
    int nb_noeuds;
    noeud * liste_arrete;
}graph_t;

int ** init_adj_mat(int, int);
void afficher_matrice(int **, int, int);
void visualiser_matrice(int **, int, int);

#endif