#include "connexe.h"

int main()
{
    srand(48);

    int graph_mat[NB_LIGNE_MAT][NB_COLONNE_MAT];
    init_mat_alea(graph_mat);

    afficher_matrice(graph_mat);
    graphviz_affiche_graph_mat(graph_mat);

    int part_connexe[2][N];
    int hauteur_part[N];
    creer_partition_arbo(part_connexe, hauteur_part);

    connexe_graph_mat(part_connexe, hauteur_part, graph_mat);

    graphviz_affiche_arbo(part_connexe);

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
                printf("i=%d et j=%d\n", i, j);
                fusion_arbo(part, hauteur, i, j);
            }
        }
    }
}