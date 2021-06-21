#ifndef __GRAPH_MAT_H__
#define __GRAPH_MAT_H__

#include <stdio.h>
#include <stdlib.h>

#include "partition.h"

#define N 20
#define NB_LIGNE_MAT N
#define NB_COLONNE_MAT N

void afficher_matrice(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);

void init_mat_alea(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);

void fichier_graphviz_graph_mat(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);
void graphviz_affiche_graph_mat(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT]);

void connexe_graph_mat(int part[2][N], int hauteur[N], int mat[N][N]);

#endif