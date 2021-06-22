#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "connexe.h"

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
        graph_partition(fichiergraph,classes);
        system("dot -Tjpg composantes_connexes.dot -o composantes_connexes.jpg");
        //system("display nom");
        fclose(fichiergraph);        
    }
}   

int main()
{
    int mat[LIGNES][COLONNES];
    int classes[TAILLE];
    int hauteurs[TAILLE];
    srand(time(NULL));

    FILE *fichier = NULL;
    fichier = fopen("graph_matrice.dot", "w");
    /*
    FILE *fichier2 = NULL;
    fichier2 = fopen("graph_partition_test.dot", "w");
    */
        
    if (fichier == NULL)
    {
        printf("erreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if (fichier)
    {
        matrice_adjacence(mat);
        graph_matrice(fichier,mat);
        composantes_connexes(mat,classes,hauteurs);
        fclose(fichier);
    }
}