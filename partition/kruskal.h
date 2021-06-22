#ifndef __kruskal_h__
#define __kruskal_h__

#include "arborescence.h"

int noeud_entier(int i);
void draw_graph(int *noeuds, int aretes[4*TAILLE], FILE *fichier, int nb_elements);
void arbre_couvrant(int *nouv_aretes, int *nb_aretes, int *aretes, int *nb_elements, int *classes, int *hauteurs, FILE *fichier);

#endif