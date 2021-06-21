#include "partition.h"

int main()
{
    int part[2][NB_ELT_MAX];
    int n = 11;
    creer_partition(part);
    printf("%d\n", recuperer_classe(part, 5));
    afficher_partition(part);
}

void afficher_partition(int tab[2][NB_ELT_MAX])
{

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < NB_ELT_MAX; j++)
        {
            printf("| %d |", tab[i][j]);
        }
        printf("\n");
    }
}

//Creeer un tableau pour partion renvoie 1 si reussi,0 sinon (echec)
void creer_partition(int tab[2][NB_ELT_MAX])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        tab[0][i] = i;
        tab[1][i] = i;
    }
}

//Renvoi -1 si elt en dehors de la taille, et sinon la classe associee
int recuperer_classe(int tab[2][NB_ELT_MAX], int indice)
{
    int classe = -1;
    if (indice < NB_ELT_MAX)
        classe = tab[1][indice];
    else
        printf("Erreur indice indice\n");
    return classe;
}

void fichier_graphviz(int *tas)
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
