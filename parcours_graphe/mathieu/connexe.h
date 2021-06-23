#ifndef __GRAPH_MAT_H__
#define __GRAPH_MAT_H__

#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "partition.h"



int main_connexe();

void afficher_matrice(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);

void init_mat_alea(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);
graph_l_arete_t *init_graph_arete_alea();
graph_l_arete_t *init_graph_arete_en_grille();

void fichier_graphviz_graph_mat(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);
void graphviz_affiche_graph_mat(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);

void connexe_graph_mat(int part[2][N], int hauteur[N], int mat[N][N]);
void connexe_graph_arete(int part_connexe[2][N], int hauteur_part[N], graph_l_arete_t *graph);

void fichier_graphviz_graph_arete(graph_l_arete_t *graph);
void graphviz_affiche_graph_arete(graph_l_arete_t *graph);

void liberer_graph_arete(graph_l_arete_t *graph);


#endif