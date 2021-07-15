#ifndef __KRUSKAL_H__
#define __KRUSKAL_H__

#include "const.h"
#include "connexe.h"

int main_kruskal();
graph_l_arete_t *calcul_foret_couvrant(graph_l_arete_t *graph);
graph_l_arete_t *calcul_quasi_foret_couvrant(graph_l_arete_t *graph, float p);

#endif