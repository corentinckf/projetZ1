#include "connexe.h"

int main_connexe()
{
    //srand(48);

    /*
    int graph_mat[NB_LIGNE_MAT][NB_COLONNE_MAT];
    init_mat_alea(graph_mat);

    afficher_matrice(graph_mat);
    graphviz_affiche_graph_mat(graph_mat);

    int part_connexe[2][N];
    int hauteur_part[N];
    creer_partition_arbo(part_connexe, hauteur_part);
    connexe_graph_mat(part_connexe, hauteur_part, graph_mat);
    graphviz_affiche_arbo(part_connexe);
*/

    graph_l_arete_t *graph = init_graph_arete_alea();

    graphviz_affiche_graph_arete(graph);

    int part_connexe[2][N];
    int hauteur_part[N];
    creer_partition_arbo(part_connexe, hauteur_part);
    connexe_graph_arete(part_connexe, hauteur_part, graph);
    graphviz_affiche_arbo(part_connexe);
    liberer_graph_arete(graph);

    return 0;
}

void afficher_matrice(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT])
{
    for (int i = 0; i < NB_LIGNE_MAT; i++)
    {
        for (int j = 0; j < NB_COLONNE_MAT; j++)
        {
            printf("| %d ", mat[i][j]);
        }
        printf("\n");
    }
}

void init_mat_alea(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT])
{
    int v;
    for (int i = 0; i < NB_LIGNE_MAT; i++)
    {
        for (int j = i + 1; j < NB_COLONNE_MAT; j++)
        {
            v = rand() % 10;
            if (v == 1)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
        for (int j = 0; j <= i; j++)
        {
            mat[i][j] = 0;
        }
    }
}

void fichier_graphviz_graph_mat(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT])
{
    FILE *fichier = NULL;
    system("rm graph.dot");
    fichier = fopen("graph.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    fprintf(fichier, "graph { ");
    for (int i = 0; i < NB_LIGNE_MAT; i++)
    {
        for (int j = i + 1; j < NB_COLONNE_MAT; j++)
        {
            if (mat[i][j] == 1)
                fprintf(fichier, "\n\t%d--%d", i, j);
            else
                fprintf(fichier, "\n\t%d\n\t%d", i, j);
        }
    }

    fprintf(fichier, "\n} ");

    fclose(fichier);
}

void graphviz_affiche_graph_mat(int mat[NB_LIGNE_MAT][NB_COLONNE_MAT])
{
    fichier_graphviz_graph_mat(mat);
    system("dot -Tjpg graph.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
}

void connexe_graph_mat(int part[2][N], int hauteur[N], int mat[N][N])
{
    for (int i = 0; i < NB_LIGNE_MAT; i++)
    {
        for (int j = i + 1; j < NB_COLONNE_MAT; j++)
        {
            if (mat[i][j] == 1)
            {
                //printf("i=%d et j=%d\n", i, j);
                fusion_arbo(part, hauteur, i, j);
            }
        }
    }
}

graph_l_arete_t *init_graph_arete_en_grille()
{
    graph_l_arete_t *graph_arete = (graph_l_arete_t *)malloc(sizeof(graph_l_arete_t));
    if (graph_arete)
    {
        graph_arete->nb_noeud = N;
        graph_arete->nb_arete = 0;
        arete_t *arete_tmp = malloc(sizeof(arete_t) * 2 * graph_arete->nb_noeud - NB_COLONNE_LABY - NB_LIGNE_LABY);
        //On genere le graph avec toutes les aretes sur la grille en tenant compte des voisins
        for (int i = 0; i < graph_arete->nb_noeud; i++)
        {
            if ((i + 1) % NB_COLONNE_LABY != 0)
            {
                arete_tmp[graph_arete->nb_arete].a = i;
                arete_tmp[graph_arete->nb_arete].b = i + 1;
                arete_tmp[graph_arete->nb_arete].poids = 1;
                graph_arete->nb_arete++;
            }
            if (i + NB_COLONNE_LABY < graph_arete->nb_noeud)
            {
                arete_tmp[graph_arete->nb_arete].a = i;
                arete_tmp[graph_arete->nb_arete].b = i + NB_COLONNE_LABY;
                arete_tmp[graph_arete->nb_arete].poids = 1;
                graph_arete->nb_arete++;
            }
        }
        graph_arete->liste_arete = (arete_t *)malloc(sizeof(arete_t) * graph_arete->nb_arete);
        for (int k = 0; k < graph_arete->nb_arete; k++)
        {
            graph_arete->liste_arete[k] = arete_tmp[k];
        }
        free(arete_tmp);
    }
    return graph_arete;
}
graph_l_arete_t *init_graph_arete_alea()
{
    graph_l_arete_t *graph_arete = (graph_l_arete_t *)malloc(sizeof(graph_l_arete_t));
    if (graph_arete)
    {
        graph_arete->nb_noeud = N;
        graph_arete->nb_arete = 0;
        arete_t *arete_tmp = malloc(sizeof(arete_t) * 2 * graph_arete->nb_noeud - NB_COLONNE_LABY - NB_LIGNE_LABY);
        int v;

        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                v = rand() % ALEA_GEN;
                if (v == 1)
                {
                    arete_tmp[graph_arete->nb_arete].a = i;
                    arete_tmp[graph_arete->nb_arete].b = j;
                    graph_arete->nb_arete++;
                }
            }
        }

        graph_arete->liste_arete = (arete_t *)malloc(sizeof(arete_t) * graph_arete->nb_arete);
        for (int k = 0; k < graph_arete->nb_arete; k++)
        {
            graph_arete->liste_arete[k].a = arete_tmp[k].a;
            graph_arete->liste_arete[k].b = arete_tmp[k].b;
        }
        free(arete_tmp);
    }
    return graph_arete;
}

void connexe_graph_arete(int part_connexe[2][N], int hauteur_part[N], graph_l_arete_t *graph)
{
    for (int i = 0; i < graph->nb_arete; i++)
    {
        fusion_arbo(part_connexe, hauteur_part, graph->liste_arete[i].a, graph->liste_arete[i].b);
    }
}

void fichier_graphviz_graph_arete(graph_l_arete_t *graph)
{
    FILE *fichier = NULL;
    //system("rm graph.dot");
    fichier = fopen("graph.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    fprintf(fichier, "graph { ");
    for (int i = 0; i < graph->nb_arete; i++)
    {
        //printf("i=%d\n", i);
        fprintf(fichier, "\n\t%d--%d [taillabel = \"%d\"]", graph->liste_arete[i].a, graph->liste_arete[i].b, graph->liste_arete[i].poids);
    }
    for (int i = 0; i < graph->nb_noeud; i++)
        fprintf(fichier, "\n\t%d", i);

    fprintf(fichier, "\n} ");

    fclose(fichier);
}

void graphviz_affiche_graph_arete(graph_l_arete_t *graph)
{
    fichier_graphviz_graph_arete(graph);
    system("dot -Tjpg graph.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
}

void liberer_graph_arete(graph_l_arete_t *graph)
{
    free(graph->liste_arete);
    free(graph);
}