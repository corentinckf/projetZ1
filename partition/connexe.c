#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
        FILE *fichiergraph = NULL;
        char nom[70];
        sprintf(nom, "composante_%d.dot", k);
        fichiergraph = fopen(nom,"w");


        if (fichiergraph)
        {
            graphviz_composante_connexe(mat,k,liste_classes,fichiergraph);
            system("dot -Tjpg nom -o nom.jpg");
            //system("display nom");
            fclose(fichiergraph);        
        }
    }
}   

void graphviz_composante_connexe(int mat[LIGNES][COLONNES], int k, cellule_t *liste_classes[TAILLE], FILE *fichierg)
{
    cellule_t *cour = liste_classes[k];
    int i;

    fprintf(fichierg,"graph {\n");
    while (cour != NULL)
    {
        i = cour->indice;
        for(int j=i-1;j>=0;j--)
        {
            if (mat[i][j] == 1)
            {
                fprintf(fichierg,"\t%d -- %d\n",i,j);
                //fprintf(fichierg,"azerty\n");
                printf("ici\n");
            }
        }
        cour = cour->suiv;       
    }
    fprintf(fichierg,"}\n");
}

int main()
{
    int mat[LIGNES][COLONNES];
    int classes[TAILLE];
    int hauteurs[TAILLE];
    cellule_t *liste_classes[TAILLE];
    srand(45);

    for (int k=0;k<TAILLE;k++)
    {
        liste_classes[k] = NULL;
    }

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
        composantes_connexes(mat,liste_classes,classes,hauteurs);
        fclose(fichier);
    }
}