#include "gestion_map.h"

void init_map(int map[NB_LIGNE_MAT][NB_COLONNE_LABY])
{
    float p = 0.05;

    //generation graph arete
    graph_l_arete_t *graph = NULL;
    graph = init_graph_arete_en_grille();

    //affiche le graphe
    //graphviz_affiche_graph_arete(graph);

    melange_fisher_yates_arete(graph);

    //Generation quasi arbre
    graph_l_arete_t *quasi_arbre = NULL;
    quasi_arbre = calcul_quasi_foret_couvrant(graph, p);

    liberer_graph_arete(graph);

    //afficher quasi_arbre
    //graphviz_affiche_graph_arete(quasi_arbre);

    construire_map(map, quasi_arbre);
    liberer_graph_arete(quasi_arbre);
}