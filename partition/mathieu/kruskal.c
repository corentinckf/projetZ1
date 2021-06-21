#include "kruskal.h"

int main()
{
    //generation graph couple
    graph_couple_t *graph = NULL;
    graph = init_graph_couple_alea();
    graphviz_affiche_graph_couple(graph);

    /* //réer une partition dont les éléments sont les nœuds du graphe
    int part_connexe[2][N];
    int hauteur_part[N];
    creer_partition_arbo(part_connexe, hauteur_part);
    connexe_graph_couple(part_connexe, hauteur_part, graph);
    graphviz_affiche_arbo(part_connexe);
*/
    //en calculer une forêt couvrante de poids minimal
    graph_couple_t *arbre_couvrant = NULL;
    arbre_couvrant = calcul_foret_couvrant(graph);
    graphviz_affiche_graph_couple(arbre_couvrant);

    liberer_graph_couple(graph);
    liberer_graph_couple(arbre_couvrant);

    return 0;
}

graph_couple_t *calcul_foret_couvrant(graph_couple_t *graph)
{

    graph_couple_t *arbre = (graph_couple_t *)malloc(sizeof(graph_couple_t));
    int part[2][N];
    if (arbre)
    {
        arbre->nb_noeud = N;
        arbre->nb_arete = 0;
        couple_t *couple_tmp = malloc(sizeof(couple_t) * graph->nb_arete);
        int a, b;

        for (int i = 0; i < graph->nb_arete; i++)
        {
            a = graph->liste_couple[i].a;
            b = graph->liste_couple[i].b;
            if (recuperer_classe(part, a) != recuperer_classe(part, b))
            {
                fusion(part, a,b);
                couple_tmp[i] = graph->liste_couple[i];
                arbre->nb_arete++;
            }
        }

        arbre->liste_couple = (couple_t *)malloc(sizeof(couple_t) * arbre->nb_arete);
        for (int k = 0; k < arbre->nb_arete; k++)
        {
            arbre->liste_couple[k].a = couple_tmp[k].a;
            arbre->liste_couple[k].b = couple_tmp[k].b;
        }
        free(couple_tmp);
    }
    return arbre;
}