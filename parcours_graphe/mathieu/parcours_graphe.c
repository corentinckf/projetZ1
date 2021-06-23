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

void relachement(graph_l_arete_t *graph, int i_arc, int distance[N], int parent[N], tas_binaire_t *tas)
{
    int u = graph->liste_arete[i_arc].a;
    int v = graph->liste_arete[i_arc].b;
    int p_u_v = graph->liste_arete[i_arc].poids;

    if (distance[v] > distance[u] + p_u_v)
    {
        distance[v] = distance[u] + p_u_v;
        parent[v] = u;
        couple_t val_couple;
        val_couple.d = distance[d];
        val_couple.n = v;

        if (tas->indice_tas[v] == -1) //noeud pas dans le tas
        {
            ajouter_elt(tas, val_couple);
        }
        else if (tas->indice_tas[v] >= 0)
        {
            diminuer_cle(tas, val_couple);
        }
        else
        {
            printf("L'indice dans le tas du noeud %d est %d, si c'est -2 c'est louche parce que je crois qu'on peut pas revisiter un noeud deja visité ou un truc comme ca\n", v, tas->indice_tas[v]);
        }
    }
}

void dijkstra(graph_l_arete_t *graph, int r, int parent[N], int distance[N])
{
    dijkstra_init(r, distance, parent);
    tas_binaire_t *file;
    couple_t u;
    u.d = 0;
    u.n = r;

    file = creer_tas_b(u);

    while (file->nb_elt != 0)
    {
        u = retirer_elt(file);
        for (int k = 0; k < graph->nb_arete; k++)
        {
            relachement(graph, k, distance, parent, tas);
        }
    }
}