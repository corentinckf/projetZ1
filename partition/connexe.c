#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "connexe.h"

/*
void matrice_adjacence(int mat[LIGNES][COLONNES])
{
    for (int i=0;i<LIGNES;i++)
    {   
        for (int j=0;j<i;j++)
        {
            mat[i][j] = mat[j][i];
        }
        mat[i][i] = 0;
        for (int j=i+1;j<COLONNES;j++)
        {
            mat[i][j] = rand()%2;
        }
    }
}

void graph_matrice(FILE *fichier, int mat[LIGNES][COLONNES])
{
    fprintf(fichier, "graph {\n");
    int min = fmin(LIGNES,COLONNES);

    for (int i=0;i<LIGNES;i++)
    {   
        fprintf(fichier,"\t%d\n",i);
        for (int j=i+1;j<min;j++)
        {
            if (mat[i][j] == 1) fprintf(fichier,"\t%d -- %d\n",i,j);
        }
        for (int j=min;j<COLONNES;j++)
        {
            fprintf(fichier,"\t%d\n",j);
        }
    }
    fprintf(fichier, "}");
}

void composantes_connexes(int mat[LIGNES][COLONNES], int *classes, int *hauteurs)
{
    creer(classes,hauteurs);

    for (int i=0;i<LIGNES;i++)
    {
        for (int j=0;j<COLONNES;j++)
        {
            if (mat[i][j] == 1) fusion(i,j,classes,hauteurs);
        }
    }

    FILE *fichiergraph = NULL;
    fichiergraph = fopen("composantes_connexes.dot","w");


    if (fichiergraph)
    {
        graph_partition(//printf("ok\n");
*/

//fonction de passage d'un noeud a son entier
int noeud_entier(int i)
{
    return i; //le numero du noeud correspond a son entier
}

int *allocation(int *tab, int *taille)
{
    *taille = (*taille) * 2;
    int *nouvtab = (int *)malloc((*taille) * sizeof(int));

    for (int k = 0; k < (*taille) / 2; k++)
    {
        nouvtab[k] = tab[k];
    }
    return nouvtab;
}

void ajouter(int **tab, int *taille, int *nb_elements, int i, int j)
{
    if (*taille == *nb_elements)
    {
        *tab = allocation(*tab, taille);
        //printf("taille augmentee\n");
    }
    //printf("a        i : %d j: %d\n", i, j);

    (*tab)[*nb_elements] = i;
    (*nb_elements)++;
    (*tab)[*nb_elements] = j;
    (*nb_elements)++;
    //printf(" tab i,j = %d,%d\n", tab[*nb_elements-2], tab[*nb_elements-1]);
}

void draw_graph(int *noeuds, int *aretes, FILE *fichier, int nb_elements)
{
    fprintf(fichier, "graph {\n");
    int k = 0;

    for (int l = 0; l < TAILLE; l++)
    {
        fprintf(fichier, "\t%d\n", noeuds[l]);
    }

    while (k < nb_elements)
    {
        fprintf(fichier, "\t%d -- %d\n", noeud_entier(aretes[k]), noeud_entier(aretes[k + 1]));
        k += 2;
    }
    fprintf(fichier, "}");
}

void composantes_connexes(int *aretes, int nb_elements, int *classes, int *hauteurs)
{
    int k = 0;
    while (k < nb_elements)
    {
        fusion(noeud_entier(aretes[k]), noeud_entier(aretes[k + 1]), classes, hauteurs);
        k += 2;
    }

    FILE *fichiergraph = NULL;
    fichiergraph = fopen("composantes_connexes.dot", "w");

    if (fichiergraph)
    {
        graph_partition(fichiergraph, classes);
        //system("display nom");
        fclose(fichiergraph);
    }
}

int main_connexe()
{
    /*
    int mat[LIGNES][COLONNES];
    int classes[TAILLE];
    int hauteurs[TAILLE];
    srand(time(NULL));

    FILE *fichier = NULL;
    fichier = fopen("graph_matrice.dot", "w");

    if (fichier == NULL)
    {
        printf("erreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    */

    int classes[TAILLE];
    int hauteurs[TAILLE];
    srand(time(NULL));

    int noeuds[TAILLE];
    //int aretes[8 * TAILLE]; //s'assurer que le nombre de cases est pair (couple d'entiers)
    int *aretes = (int *) malloc(8*TAILLE*sizeof(int));
    int taille = 8 * TAILLE;
    int nb_elements = 0;

    //initialisation
    for (int i = 0; i < TAILLE; i++)
    {
        noeuds[i] = i;
    }

    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = i + 1; j < TAILLE; j++)
        {
            int valeur = rand() % 2;
            if (valeur)
            {
                ajouter(&aretes, &taille, &nb_elements, i, j);//
            }
        }
    }

    FILE *fichier = NULL;
    fichier = fopen("graph.dot", "w");

    if (fichier)
    {
        draw_graph(noeuds, aretes, fichier, nb_elements);
        creer(classes, hauteurs);
        composantes_connexes(aretes, nb_elements, classes, hauteurs);
        //system("dot -Tjpg graph.dot -o graph.jpg");
        //system("dot -Tjpg composantes_connexes.dot -o composantes_connexes.jpg");
        fclose(fichier);
    }
    return 0;
}
