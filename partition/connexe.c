#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "connexe.h"
#include "arborescence.h"

#define LIGNES 8
#define COLONNES 7
#define TAILLE LIGNES*COLONNES

void matrice_adjacence(int mat[LIGNES][COLONNES])
{
    for (int i=0;i<LIGNES;i++)
    {   
        for (int j=0;j<i+1;j++)
        {
            mat[i][j] = 0;
        }
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
            if (mat[i][j] == 1) fprintf(fichier,"\t%d -- %d\n",i,j);
        }
    }
    fprintf(fichier, "}");
}

void composantes_connexes(int mat[LIGNES][COLONNES], cellule_t *liste_classes[TAILLE], int *classes, int *hauteurs)
{
    creer(classes,hauteurs);

    for (int i=0;i<LIGNES;i++)
    {
        for (int j=0;j<COLONNES;j++)
        {
            if (mat[i][j] == 1) fusion(i,j,classes,hauteurs);
        }
    }
    lister_partition(classes,liste_classes); //liste chainee de tete liste_classe[k] est une composante connexe

    for (int k=0;k<TAILLE;k++)
    {
        FILE *fichier = NULL;
        fichier = fopen("composantek.dot","w");

        if (fichier)
        {
            graphviz_composante_connexe(k,liste_classes,fichier);
            fclose(fichier);        
        }
    }
}   

void graphviz_composante_connexe(int mat[LIGNES][COLONNES], int k, cellule_t *liste_classes[TAILLE], FILE *fichier)
{
    int cour = liste_classes[k];
    int i;

    while (cour != NULL)
    {
        i = cour->indice;
        for(int j=i+1;j<COLONNES;j++)
        {
            if (mat[i][j] == 1) fprintf(fichier,"\t%d -- %d\n",i,j);
        }
        cour = cour->suiv;       
    }
}


int main()
{
    int mat[LIGNES][COLONNES];
    int classes[TAILLE];
    int hauteurs[TAILLE];
    cellule_t *liste_classes[TAILLE];
    srand(42);

    FILE *fichier = NULL;
    fichier = fopen("graph_matrice.dot", "w");
    
    if (fichier == NULL)
    {
        printf("erreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if (fichier)
    {
        matrice_adjacence(mat);
        graph_matrice(fichier,mat);
        composantes_connexes(mat,liste_classes,classes,hauteurs);
        fclose(fichier);
    }
}