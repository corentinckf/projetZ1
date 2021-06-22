#ifndef __PARCOURS_GRAPHE_H__
#define __PARCOURS_GRAPHE_H__

#include "const.h"

int main_parcours_graphe();

void dijkstra_init(int r, int distance[N], int parent[N]);
void relachement(graph_couple_t *graph, couple_t *arc, int distance[N], int parent[N]);

#endif