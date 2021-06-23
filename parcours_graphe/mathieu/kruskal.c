#include "kruskal.h"

int main_kruskal()
{
    //generation graph arete
    graph_l_arete_t *graph = NULL;
    graph = init_graph_arete_en_grille();
    graphviz_affiche_graph_arete(graph);

    /* //réer une partition dont les éléments sont les nœuds du graphe
    int part_connexe[2][N];
    int hauteur_part[N];
    creer_partition_arbo(part_connexe, hauteur_part);
    connexe_graph_arete(part_connexe, hauteur_part, graph);
    graphviz_affiche_arbo(part_connexe);
*/
    //en calculer une forêt couvrante de poids minimal
    graph_l_arete_t *arbre_couvrant = NULL;
    arbre_couvrant = calcul_foret_couvrant(graph);
    graphviz_affiche_graph_arete(arbre_couvrant);

    liberer_graph_arete(graph);
    liberer_graph_arete(arbre_couvrant);

    return 0;
}

graph_l_arete_t *calcul_foret_couvrant(graph_l_arete_t *graph)
{

    //Ordonner par ordre croissant les arete de graph en fct de leur poids

    graph_l_arete_t *arbre = (graph_l_arete_t *)malloc(sizeof(graph_l_arete_t));
    int part[2][N];
    int hauteur[N];
    creer_partition_arbo(part, hauteur);
    afficher_partition(part);
    if (arbre)
    {
        arbre->nb_noeud = N;
        arbre->nb_arete = 0;
        arete_t *arete_tmp = malloc(sizeof(arete_t) * graph->nb_arete);
        int a, b;
        printf("nb arete totale = %d\n", graph->nb_arete);
        for (int i = 0; i < graph->nb_arete; i++)
        {
            a = graph->liste_arete[i].a;
            b = graph->liste_arete[i].b;
            if (recuperer_classe_arbo(part, a) != recuperer_classe_arbo(part, b))
            {
                fusion_arbo(part, hauteur, b, a);
                arete_tmp[arbre->nb_arete] = graph->liste_arete[i];
                arbre->nb_arete++;

            }
        }

        arbre->liste_arete = (arete_t *)malloc(sizeof(arete_t) * arbre->nb_arete);
        for (int k = 0; k < arbre->nb_arete; k++)
        {
            arbre->liste_arete[k] = arete_tmp[k];
        }
        free(arete_tmp);
    }
    return arbre;
}

graph_l_arete_t *calcul_quasi_foret_couvrant(graph_l_arete_t *graph, float p)
{
    //Ordonner par ordre croissant les arete de graph en fct de leur poids

    graph_l_arete_t *arbre = (graph_l_arete_t *)malloc(sizeof(graph_l_arete_t));
    int part[2][N];
    int hauteur[N];
    creer_partition_arbo(part, hauteur);
    afficher_partition(part);
    if (arbre)
    {
        arbre->nb_noeud = N;
        arbre->nb_arete = 0;
        arete_t *arete_tmp = malloc(sizeof(arete_t) * graph->nb_arete);
        int a, b;
        float alpha;
        for (int i = 0; i < graph->nb_arete; i++)
        {
            a = graph->liste_arete[i].a;
            b = graph->liste_arete[i].b;
            
            printf("alpha=%f\n", alpha);
            alpha = (float)(rand() % 100) / (float)100;
            if (recuperer_classe_arbo(part, a) != recuperer_classe_arbo(part, b))
            {
                fusion_arbo(part, hauteur, b, a);
                arete_tmp[arbre->nb_arete] = graph->liste_arete[i];
                arbre->nb_arete++;
            }
            else if (alpha < p)
            {
                arete_tmp[arbre->nb_arete] = graph->liste_arete[i];
                arbre->nb_arete++;
            }
        }

        arbre->liste_arete = (arete_t *)malloc(sizeof(arete_t) * arbre->nb_arete);
        for (int k = 0; k < arbre->nb_arete; k++)
        {
            arbre->liste_arete[k] = arete_tmp[k];
        }
        free(arete_tmp);
    }
    return arbre;
}