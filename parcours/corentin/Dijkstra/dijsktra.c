#include "dijkstra.h"
int alloc_tableaux(int n_sommet,int** distance,int** parent,int**visite)
{
    int code_retour = 0;
    *distance  = (int *) calloc(n_sommet, sizeof(int));
    *parent  = (int *) calloc(n_sommet, sizeof(int));
    *visite  = (int *) calloc(n_sommet, sizeof(int));
    if(*distance && *parent && *visite)
        code_retour = 1;
    return code_retour;
}

void initialiser_tableaux(int sommet_depart, graphe_t * graphe,int* distance,int* parent,int* visite, tas_binaire_t ** tas)
{
    *tas = (tas_binaire_t*) malloc(sizeof(tas_binaire_t));
    if(tas)
    {
        for(int i = 0; i < graphe->n_sommet;++i)
        {
            
            parent[i] = AUCUN;
            visite[i] = 0;
            distance[i] = INFINI;
            if(i==sommet_depart)
            {
                visite[i] = 1;
                distance[i] = 0;
            } 
        }

    }
    
}