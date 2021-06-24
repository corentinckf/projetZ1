#ifndef __PARCOURS_GRAPHE_H__
#define __PARCOURS_GRAPHE_H__

#include "const.h"

int main_parcours_graphe();

void promenade_labyrinthe_dijkstra(SDL_Window *window, SDL_Renderer *renderer);
void dijkstra_init(int r, int distance[N], int parent[N]);
void relachement(int u, int v, int p_u_v, int distance[N], int parent[N], tas_binaire_t *tas);
void dijkstra(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int r, int distance[N], int parent[N]);

graph_l_arete_t *copie_graph(graph_l_arete_t *graph);
int chemin(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int sour, int dest, int chemin_list[N]);

void dessiner_chemin(SDL_Window *window, SDL_Renderer *renderer, int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int chemin_list[N], int taille_chemin);

void A_etoile(int (*fct_distance)(const int, const int), int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int r, int distance[N], int parent[N]);
int d_euclidienne(int a, int b);
int d_tchebychev(int a, int b);
int d_manhattan(int a, int b);
int chemin_a_etoile(int (*fct_distance)(const int, const int), int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int sourc, int dest, int chemin_list[N]);
void promenade_labyrinthe_a_etoile(SDL_Window *window, SDL_Renderer *renderer);

void init_DFS(int couleur[N], int parent[N]);
void DFS_rec(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int u, int couleur[N], int parent[N], int debut[N], int fin[N], int *temps);
void DFS_run(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int r, int couleur[N], int parent[N], int debut[N], int fin[N]);
void utilisation_parcours_en_profondeur();

#endif