#include "dijkstra.h"
int alloc_tableaux(int n_sommet,int** distance,int** parent)
{
    int code_retour = 0;
    *distance  = (int *) calloc(n_sommet, sizeof(int));
    *parent  = (int *) calloc(n_sommet, sizeof(int));
    if(*distance && *parent)
        code_retour = 1;
    return code_retour;
}

void initialiser_tableaux(int n_sommet,int* distance,int* parent)
{
    for(int i = 0; i < n_sommet;++i)
    {
        distance[i] = INFINI;
        parent[i] = AUCUN;
    }
}