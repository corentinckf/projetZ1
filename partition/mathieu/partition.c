#include "partition.h"

int main()
{
    int partition[2][NB_ELT_MAX];
    int classe[NB_ELT_MAX];
    int n = 11;
    creer_partition(partition);
    printf("%d\n", recuperer_classe(partition, 5));
    afficher_partition(partition);

    printf("Fusion de %d et %d\n", 3, 7);
    fusion(partition, 3, 7);
    afficher_partition(partition);

    printf("nb_elt %d\n", lister_classe(partition, 3, classe));

    lister_partition(partition);

    return 0;
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

int lister_classe_a_partir_elt(int part[2][NB_ELT_MAX], int elt, int classe[NB_ELT_MAX])
{
    int nb_elt = 0;
    int v_classe = recuperer_classe(part, elt);
    printf("Classe %d : ", v_classe);
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        if (part[1][i] == v_classe)
        {
            classe[nb_elt] = part[0][i];
            printf("| %d ", classe[i]);
            nb_elt++;
        }
    }
    printf("|\n");
    return nb_elt;
}
int lister_classe(int part[2][NB_ELT_MAX], int etiquette, int classe[NB_ELT_MAX])
{
    int nb_elt = 0;
    int v_classe = recuperer_classe(part, etiquette);
    printf("Classe %d : ", v_classe);
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        if (part[1][i] == v_classe)
        {
            classe[nb_elt] = part[0][i];
            printf("| %d ", classe[i]);
            nb_elt++;
        }
    }
    printf("|\n");
    return nb_elt;
}

void lister_partition(int part[2][NB_ELT_MAX])
{
    cellule_t **classe = malloc(sizeof(cellule_t)*NB_ELT_MAX);
    cellule_t *cel;
    //cellule_t *classe[50];

    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        classe[i] = NULL;
    }
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        cel = creer_cellule(part[0][i]);
        ADJ_LCH(cel, &classe[part[1][i]]);
    }

    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        afficher_lch(&classe[i]);
    }
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
