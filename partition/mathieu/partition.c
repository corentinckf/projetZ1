#include "partition.h"

int main()
{
    int **tab = NULL;
    int n = 11;
    creer_partition_tab(tab, n);
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
int creer_partition_tab(int **tab, int n)
{
    int k = 0;
    int succes = 0;
    tab = malloc(sizeof(int *) * 2);
    if (tab != NULL)
    {
        while (tab[k] != NULL && k < 2)
        {
            tab[k] = malloc(sizeof(int) * n);
            k++;
        }
        if (tab[k] == NULL)
        {
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
    return succes;
}