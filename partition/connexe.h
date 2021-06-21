#ifndef __connexe_h__
#define __connexe_h__

#define LIGNES 8
#define COLONNES 7
#define TAILLE LIGNES*COLONNES

void matrice_adjacence(int mat[LIGNES][COLONNES]);
void graph_matrice(FILE *fichier, int mat[LIGNES][COLONNES]);
void composantes_connexes(int mat[LIGNES][COLONNES], cellule_t *liste_classes[TAILLE], int *classes, int *hauteurs);
void graphviz_composante_connexe(int mat[LIGNES][COLONNES], int k, cellule_t *liste_classes[TAILLE], FILE *fichier);

#endif