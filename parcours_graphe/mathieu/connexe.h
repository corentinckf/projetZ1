#ifndef __GRAPH_MAT_H__
#define __GRAPH_MAT_H__

#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "partition.h"

typedef struct couple
{
    int a;
    int b;
} couple_t;

typedef struct graph_couple
{
    int nb_noeud;
    int nb_arete;
    couple_t *liste_couple;
} graph_couple_t;

int main_connexe();

void afficher_matrice(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);

void init_mat_alea(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);
graph_couple_t *init_graph_couple_alea();
graph_couple_t *init_graph_couple_en_grille();

void fichier_graphviz_graph_mat(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);
void graphviz_affiche_graph_mat(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);

void connexe_graph_mat(int part[2][N], int hauteur[N], int mat[N][N]);
void connexe_graph_couple(int part_connexe[2][N], int hauteur_part[N], graph_couple_t *graph);

void fichier_graphviz_graph_couple(graph_couple_t *graph);
void graphviz_affiche_graph_couple(graph_couple_t *graph);

void liberer_graph_couple(graph_couple_t *graph);


#endif