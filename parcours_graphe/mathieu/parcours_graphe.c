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
    parent[r] = 0;
    distance[r] = 0;
}

void relachement(int u, int v, int p_u_v, int distance[N], int parent[N], tas_binaire_t *tas)
{
    if (distance[v] == -1 || distance[v] > distance[u] + p_u_v)
    {
        distance[v] = distance[u] + p_u_v;
        parent[v] = u;

        couple_t val_couple;
        val_couple.d = distance[v];
        val_couple.n = v;
        if (tas->indice_tas[v] == -1)
            ajouter_elt(tas, val_couple);
        else
            diminuer_cle(tas, val_couple);
    }
}

void dijkstra(graph_l_arete_t *graph, int r, int distance[N], int parent[N])
{
    dijkstra_init(r, distance, parent);
    tas_binaire_t *file;
    couple_t *pt_tas = (couple_t *)malloc(sizeof(couple_t));
    pt_tas->d = 0;
    pt_tas->n = r;
    graph_l_arete_t *graph_copie;
    graph_copie = copie_graph(graph);

    file = creer_tas_b(*pt_tas);

    int u;
    int v;
    int p_u_v;

    while (file->nb_elt != 0)
    {
        pt_tas = retirer_elt(file);
        file->indice_tas[pt_tas->n] = -2;
        for (int k = 0; k < graph_copie->nb_arete; ++k)
        {

            u = graph_copie->liste_arete[k].a;
            v = graph_copie->liste_arete[k].b;
            p_u_v = graph_copie->liste_arete[k].poids;

            if (pt_tas->n == u || pt_tas->n == v)
            {
                relachement(u, v, p_u_v, distance, parent, file);
                //relachement(v, u, p_u_v, distance, parent, file);
                //graph_copie->nb_arete--;
            }
        }
    }
    //liberer_graph_arete(graph_copie);
}

graph_l_arete_t *copie_graph(graph_l_arete_t *graph)
{
    graph_l_arete_t *copie;
    copie = (graph_l_arete_t *)malloc(sizeof(graph));
    if (copie)
    {
        copie->liste_arete = (arete_t *)malloc(sizeof(arete_t) * graph->nb_arete);
        if (copie->liste_arete)
        {
            copie->nb_noeud = graph->nb_noeud;
            copie->nb_arete = graph->nb_arete;
            for (int k = 0; k < graph->nb_arete; ++k)
                copie->liste_arete[k] = graph->liste_arete[k];
        }
    }
    return copie;
}