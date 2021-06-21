#include "partition.h"

int main()
{
    int partition[2][NB_ELT_MAX];
    int n = 11;
    creer_partition(partition);
    printf("%d\n", recuperer_classe(partition, 5));
    afficher_partition(partition);

    printf("Fusion de %d et %d\n", 3,7);
    fusion(partition, 3,7);
    afficher_partition(partition);
    
}

void afficher_partition(int part[2][NB_ELT_MAX])
{

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < NB_ELT_MAX; j++)
        {
            printf("| %d |", part[i][j]);
        }
        printf("\n");
    }
}

//Creeer un partleau pour partion renvoie 1 si reussi,0 sinon (echec)
void creer_partition(int part[2][NB_ELT_MAX])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        part[0][i] = i;
        part[1][i] = i;
    }
}

//Renvoi -1 si elt en dehors de la taille, et sinon la classe associee
int recuperer_classe(int part[2][NB_ELT_MAX], int indice)
{
    int classe = -1;
    if (indice < NB_ELT_MAX)
        classe = part[1][indice];
    else
        printf("Erreur indice indice\n");
    return classe;
}

void fusion(int part[2][NB_ELT_MAX], int x, int y)
{
    if (x < NB_ELT_MAX && y < NB_ELT_MAX)
        part[1][y] = recuperer_classe(part, x);
    else
        printf("Erreur d'indice x=%d, i=%d et NB_ELT_MAX=%d\n", x, y, NB_ELT_MAX);
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
