#include "parcours_graphe.h"

int main_parcours_graphe()
{

    return 0;
}

void dijkstra_init( int r, int distance[N], int parent[N])
{
    for (int i = 0; i < N; ++i)
    {
        distance[i] = -1; //+infini +oo
        parent[i] = -1;
    }
    distance[r] = 0;
}

void relachement(graph_couple_t*graph, couple_t*arc, int distance[N], int parent[N])
{

}





