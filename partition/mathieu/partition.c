#include "partition.h"


int main_partition()
{
    int partition[2][NB_ELT_MAX];
    int hauteur[NB_ELT_MAX];
    int classe[NB_ELT_MAX];
    int x, y;

    creer_partition_arbo(partition, hauteur);

    graphviz_affiche(partition);

    //printf("%d\n", recuperer_classe(partition, 5));
    //afficher_partition(partition);

    x = 0;
    y = 1;
    printf("Fusion de %d et %d\n", x, y);
    fusion_arbo(partition, hauteur, x, y);
    //afficher_partition(partition);
    graphviz_affiche(partition);

    x = 2;
    y = 3;
    printf("Fusion de %d et %d\n", x, y);
    fusion_arbo(partition, hauteur, x, y);
    //afficher_partition(partition);
    graphviz_affiche(partition);

    x = 10;
    y = 3;
    printf("Fusion de %d et %d\n", x, y);
    fusion_arbo(partition, hauteur, x, y);
    //afficher_partition(partition);
    graphviz_affiche(partition);

    x = 5;
    y = 9;
    printf("Fusion de %d et %d\n", x, y);
    fusion_arbo(partition, hauteur, x, y);
    //afficher_partition(partition);
    graphviz_affiche(partition);

    x = 4;
    y = 6;
    printf("Fusion de %d et %d\n", x, y);
    fusion_arbo(partition, hauteur, x, y);
    //afficher_partition(partition);
    graphviz_affiche(partition);

    x = 8;
    y = 7;
    printf("Fusion de %d et %d\n", x, y);
    fusion_arbo(partition, hauteur, x, y);
    //afficher_partition(partition);
    graphviz_affiche(partition);

    x = 7;
    y = 9;
    printf("Fusion de %d et %d\n", x, y);
    fusion_arbo(partition, hauteur, x, y);
    //afficher_partition(partition);
    graphviz_affiche(partition);

    x = 6;
    y = 8;
    printf("Fusion de %d et %d\n", x, y);
    fusion_arbo(partition, hauteur, x, y);
    //afficher_partition(partition);
    graphviz_affiche(partition);

    //printf("nb_elt %d\n", lister_classe(partition, 3, classe));

    //lister_partition(partition);

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
void creer_partition_arbo(int part[2][NB_ELT_MAX], int hauteur[NB_ELT_MAX])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        hauteur[i] = 0;
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

int recuperer_classe_arbo(int part[2][NB_ELT_MAX], int x)
{
    if (x == part[1][x])
        return part[1][x];
    else
        return recuperer_classe_arbo(part, part[1][x]);
}

void fusion_arbo(int part[2][NB_ELT_MAX], int hauteur[NB_ELT_MAX], int x, int y)
{
    int c_x = recuperer_classe_arbo(part, x);
    int c_y = recuperer_classe_arbo(part, y);
    //printf("c_x=%d, x=%d, hauteur=%d\n", c_x, x, hauteur[x]);
    //printf("c_y=%d, y=%d, hauteur=%d\n", c_y, y, hauteur[y]);
    if (c_x != c_y)
    {
        if (hauteur[c_x] > hauteur[c_y])
        {
            part[1][c_y] = c_x;
        }
        else if (hauteur[c_x] < hauteur[c_y])
        {
            part[1][c_x] = c_y;
        }
        else
        {
            part[1][c_y] = c_x;
            hauteur[c_x] += 1;
        }
        //afficher_partition(part);
    }
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
            printf("| %d ", classe[nb_elt]);
            nb_elt++;
        }
    }
    printf("|\n");
    return nb_elt;
}

int lister_classe(int part[2][NB_ELT_MAX], int etiquette, int classe[NB_ELT_MAX])
{
    int nb_elt = 0;
    printf("Classe %d : ", etiquette);
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        if (part[1][i] == etiquette)
        {
            classe[nb_elt] = part[0][i];
            printf("| %d ", classe[nb_elt]);
            nb_elt++;
        }
    }
    printf("|\n");
    return nb_elt;
}

void lister_partition(int part[2][NB_ELT_MAX])
{
    cellule_t **classe = malloc(sizeof(cellule_t) * NB_ELT_MAX);
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

void fichier_graphviz_arbo(int part[2][NB_ELT_MAX])
{
    FILE *fichier = NULL;
    system("rm graph.dot");
    fichier = fopen("graph.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    int k = 0;

    fprintf(fichier, "digraph { ");
    while (k < NB_ELT_MAX)
    {
        fprintf(fichier, "\n\t%d->%d", part[0][k], part[1][k]);
        k++;
    }
    fprintf(fichier, "\n} ");

    fclose(fichier);
}

void graphviz_affiche_arbo(int part[2][NB_ELT_MAX])
{
    fichier_graphviz_arbo(part);
    system("dot -Tjpg graph.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
}
