#include "kruskal.h"

int main_kruskal()
{
    //generation graph couple
    graph_couple_t *graph = NULL;
    graph = init_graph_couple_en_grille();
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

    //Ordonner par ordre croissant les arete de graph en fct de leur poids

    graph_couple_t *arbre = (graph_couple_t *)malloc(sizeof(graph_couple_t));
    int part[2][N];
    int hauteur[N];
    creer_partition_arbo(part, hauteur);
    afficher_partition(part);
    if (arbre)
    {
        arbre->nb_noeud = N;
        arbre->nb_arete = 0;
        couple_t *couple_tmp = malloc(sizeof(couple_t) * graph->nb_arete);
        int a, b;
        printf("nb arete totale = %d\n", graph->nb_arete);
        for (int i = 0; i < graph->nb_arete; i++)
        {
            a = graph->liste_couple[i].a;
            b = graph->liste_couple[i].b;
            //printf("(a,b)=(%d,%d)\n", a,b);
            //printf("classe cl(a)=%d, cl(b)=%d\n", recuperer_classe(part, a), recuperer_classe(part, b));
            if (recuperer_classe_arbo(part, a) != recuperer_classe_arbo(part, b))
            {
                fusion_arbo(part, hauteur, b, a);
                couple_tmp[arbre->nb_arete] = graph->liste_couple[i];
                arbre->nb_arete++;
                //printf("arete ajoutee = %d\n", arbre->nb_arete);
                //printf("\n");
                //afficher_partition(part);
            }
        }

        arbre->liste_couple = (couple_t *)malloc(sizeof(couple_t) * arbre->nb_arete);
        for (int k = 0; k < arbre->nb_arete; k++)
        {
            arbre->liste_couple[k] = couple_tmp[k];
        }
        free(couple_tmp);
    }
    return arbre;
}

graph_couple_t *calcul_quasi_foret_couvrant(graph_couple_t *graph, float p)
{
    //Ordonner par ordre croissant les arete de graph en fct de leur poids

    graph_couple_t *arbre = (graph_couple_t *)malloc(sizeof(graph_couple_t));
    int part[2][N];
    int hauteur[N];
    creer_partition_arbo(part, hauteur);
    afficher_partition(part);
    if (arbre)
    {
        arbre->nb_noeud = N;
        arbre->nb_arete = 0;
        couple_t *couple_tmp = malloc(sizeof(couple_t) * graph->nb_arete);
        int a, b;
        float alpha;
        for (int i = 0; i < graph->nb_arete; i++)
        {
            a = graph->liste_couple[i].a;
            b = graph->liste_couple[i].b;
            
            printf("alpha=%f\n", alpha);
            alpha = (float)(rand() % 100) / (float)100;
            if (recuperer_classe_arbo(part, a) != recuperer_classe_arbo(part, b))
            {
                fusion_arbo(part, hauteur, b, a);
                couple_tmp[arbre->nb_arete] = graph->liste_couple[i];
                arbre->nb_arete++;
            }
            else if (alpha < p)
            {
                couple_tmp[arbre->nb_arete] = graph->liste_couple[i];
                arbre->nb_arete++;
            }
        }

        arbre->liste_couple = (couple_t *)malloc(sizeof(couple_t) * arbre->nb_arete);
        for (int k = 0; k < arbre->nb_arete; k++)
        {
            arbre->liste_couple[k] = couple_tmp[k];
        }
        free(couple_tmp);
    }
    return arbre;
}