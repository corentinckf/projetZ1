#ifndef __connexe_h__
#define __connexe_h__

#include "arborescence.h"

int noeud_entier(int i);
int *allocation(int *tab, int *taille);
void ajouter(int **tab, int *taille, int *nb_elements, int i, int j);
void draw_graph(int *noeuds, int *aretes, FILE *fichier, int nb_elements);
void composantes_connexes(int *aretes, int nb_elements, int *classes, int *hauteurs);

/*
void matrice_adjacence(int mat[LIGNES][COLONNES]);
void graph_matrice(FILE *fichier, int mat[LIGNES][COLONNES]);
void composantes_connexes(int mat[LIGNES][COLONNES], int *classes, int *hauteurs);
*/

#endif