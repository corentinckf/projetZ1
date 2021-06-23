#include "parcours_graphe.h"

int main_parcours_graphe()
{

    return 0;
}

void dijkstra_init(int r, int distance[N], int parent[N])
{
    for (int i = 0; i < N; ++i)
    {
        distance[i] = -1; //+infini +oo
        parent[i] = -1;
    }
    distance[r] = 0;
}

void relachement(graph_l_arete_t *graph, int i_arc, int distance[N], int parent[N])
{
    int u = graph->liste_arete[i_arc].a;
    int v = graph->liste_arete[i_arc].b;
    int p_u_v = graph->liste_arete[i_arc].poids;

    if (distance[v] > distance[u] + p_u_v)
    {
        distance[v] = distance[u] + p_u_v;
        parent[v] = u;
    }
}


void dijkstra(graph_l_arete_t*graph, int n_d)
{

}