#ifndef __connexe_h__
#define __connexe_h__

#include "arborescence.h"

void matrice_adjacence(int mat[LIGNES][COLONNES]);
void graph_matrice(FILE *fichier, int mat[LIGNES][COLONNES]);
void composantes_connexes(int mat[LIGNES][COLONNES], int *classes, int *hauteurs);

#endif