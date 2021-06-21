#include "partition.h"

int main()
{
    int **tab = NULL;
    int n = 11;
    tab = creer_partition_tab(n);
    //printf("%d\n", tab[0][0]);
    afficher_partition_tab(tab, n);
}

void afficher_partition_tab(int **tab, int taille)
{

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            printf("| %d |", tab[i][j]);
        }
        printf("\n");
    }
}

//Creeer un tableau pour partion renvoie 1 si reussi,0 sinon (echec)
int **creer_partition_tab(int n)
{
    int k = 0;
    int succes = 0;
    int **tab;
    tab = (int **)malloc(sizeof(int *) * 2);
    if (tab != NULL)
    {
        while (k < 2)
        {
            tab[k] = (int *)malloc(sizeof(int) * n);
            k++;
        }
        if (tab[0] == NULL || tab[1] == NULL)
        {
            printf("erreur de malloc\n");
            free(tab[0]);
            free(tab[1]);
            free(tab);
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                tab[0][i] = i;
                tab[1][i] = i;
            }
            succes = 1;
        }
    }
    return tab;
}

void fichier_graphiz(int *tas)
{
    FILE *fichier = NULL;
    fichier = fopen("graph_tas.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    int k = 1;
    /*
    fprintf(fichier, "graph { ");
    while (k <= tas[0])
    {
        if (tas[k] > 0 && tas[f_g(k)] > 0 && f_g(k) <= tas[0])
            fprintf(fichier, "\n\t%d--%d", tas[k], tas[f_g(k)]);

        if (tas[k] > 0 && tas[f_d(k)] > 0 && f_d(k) <= tas[0])
            fprintf(fichier, "\n\t%d--%d", tas[k], tas[f_d(k)]);
        k++;
    }
    fprintf(fichier, "\n} ");
*/
    fclose(fichier);
}
