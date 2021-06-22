#include <stdio.h>
#include <stdlib.h>
#include "arborescence.h"
#include "connexe.h"

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