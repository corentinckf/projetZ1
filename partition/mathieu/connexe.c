#include "connexe.h"

int main_connexe()
{
    srand(48);

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

    graph_couple_t *graph = init_graph_couple_alea();

    graphviz_affiche_graph_couple(graph);

    int part_connexe[2][N];
    int hauteur_part[N];
    creer_partition_arbo(part_connexe, hauteur_part);
    connexe_graph_couple(part_connexe, hauteur_part, graph);
    graphviz_affiche_arbo(part_connexe);
    liberer_graph_couple(graph);

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

graph_couple_t *init_graph_couple_en_grille()
{
    graph_couple_t *graph_couple = (graph_couple_t *)malloc(sizeof(graph_couple_t));
    if (graph_couple)
    {
        graph_couple->nb_noeud = N;
        graph_couple->nb_arete = 0;
        couple_t *couple_tmp = malloc(sizeof(couple_t) * 2 * graph_couple->nb_noeud - NB_COLONNE_LABY - NB_LIGNE_LABY);
        int v;
        //On genere le graph avec toutes les aretes sur la grille en tenant compte des voisins
        for (int i = 0; i < graph_couple->nb_noeud; i++)
        {
            if ((i + 1) % NB_COLONNE_LABY != 0)
            {
                couple_tmp[graph_couple->nb_arete].a = i;
                couple_tmp[graph_couple->nb_arete].b = i + 1;
                graph_couple->nb_arete++;
            }
            if (i + NB_COLONNE_LABY < graph_couple->nb_noeud)
            {
                couple_tmp[graph_couple->nb_arete].a = i;
                couple_tmp[graph_couple->nb_arete].b = i + NB_COLONNE_LABY;
                graph_couple->nb_arete++;
            }
        }
        graph_couple->liste_couple = (couple_t *)malloc(sizeof(couple_t) * graph_couple->nb_arete);
        for (int k = 0; k < graph_couple->nb_arete; k++)
        {
            graph_couple->liste_couple[k].a = couple_tmp[k].a;
            graph_couple->liste_couple[k].b = couple_tmp[k].b;
        }
        free(couple_tmp);
    }
    return graph_couple;
}
graph_couple_t *init_graph_couple_alea()
{
    graph_couple_t *graph_couple = (graph_couple_t *)malloc(sizeof(graph_couple_t));
    if (graph_couple)
    {
        graph_couple->nb_noeud = N;
        graph_couple->nb_arete = 0;
        couple_t *couple_tmp = malloc(sizeof(couple_t) * 2 * graph_couple->nb_noeud - NB_COLONNE_LABY - NB_LIGNE_LABY);
        int v;
        
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                v = rand() % ALEA_GEN;
                if (v == 1 )
                {
                    couple_tmp[graph_couple->nb_arete].a = i;
                    couple_tmp[graph_couple->nb_arete].b = j;
                    graph_couple->nb_arete++;
                }
            }
        }
        
        graph_couple->liste_couple = (couple_t *)malloc(sizeof(couple_t) * graph_couple->nb_arete);
        for (int k = 0; k < graph_couple->nb_arete; k++)
        {
            graph_couple->liste_couple[k].a = couple_tmp[k].a;
            graph_couple->liste_couple[k].b = couple_tmp[k].b;
        }
        free(couple_tmp);
    }
    return graph_couple;
}

//inutile
int sont_voisins(int a, int b)
{
    int res = 0;
    int i_a = a / NB_COLONNE_LABY;
    int j_a = a % NB_COLONNE_LABY;
    int i_b = b / NB_COLONNE_LABY;
    int j_b = b % NB_COLONNE_LABY;
    printf("a=%d : i,j=%d,%d\n", a, i_a, j_a);
    printf("b=%d : i,j=%d,%d\n", b, i_b, j_b);
    if (j_a == j_b)
    {
        if (i_b - i_a == 1)
            res = 1; //a mur droite
        else if (i_b - i_a == -1)
            res = 4; //a mur gauche
    }
    else
    {
        if (i_b == i_a)
        {
            if (j_b - j_a == 5)
                res = 8; //a mur bas
            else if (j_b - j_a == -5)
                res = 2; //a mur haut
        }
    }

    /*
    if (abs(a - b) == 1 && (a + b + 1 % NB_COLONNE_LABY) != 0)
        res = 1;
    if (abs(a - b) == NB_COLONNE_LABY)
        res = 1;
    //printf("a=%d, b=%d, abs(a-b)=%d,  (a + b + 1 % NB_COLONNE_LABY)=%d, abs(a - b) \% NB_COLONNE_LABY=%d,  res=%d\n", a, b, abs(a - b), (a + b + 1 % NB_COLONNE_LABY), abs(a - b) % NB_COLONNE_LABY, res);
    */
    return res;
}

void connexe_graph_couple(int part_connexe[2][N], int hauteur_part[N], graph_couple_t *graph)
{
    for (int i = 0; i < graph->nb_arete; i++)
    {
        fusion_arbo(part_connexe, hauteur_part, graph->liste_couple[i].a, graph->liste_couple[i].b);
    }
}

void fichier_graphviz_graph_couple(graph_couple_t *graph)
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
        fprintf(fichier, "\n\t%d--%d", graph->liste_couple[i].a, graph->liste_couple[i].b);
    }
    for (int i = 0; i < graph->nb_noeud; i++)
        fprintf(fichier, "\n\t%d", i);

    fprintf(fichier, "\n} ");

    fclose(fichier);
}

void graphviz_affiche_graph_couple(graph_couple_t *graph)
{
    fichier_graphviz_graph_couple(graph);
    system("dot -Tjpg graph.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
}

void liberer_graph_couple(graph_couple_t *graph)
{
    free(graph->liste_couple);
    free(graph);
}