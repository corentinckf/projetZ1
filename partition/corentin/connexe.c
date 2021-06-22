#include "connexe.h"

int ** init_adj_mat(int size_l, int size_c)
{
    int ** matrice = (int **) malloc(size_l * sizeof(int *));
    int            i = 0, j = 0;

    if(matrice)
    {
        while(i < size_l && (matrice[i] = (int *) malloc(size_c * sizeof(int))))
            ++i;

        if(i < 2)
        {
            for(j = i; j >= 0;--j)
                free(matrice[i]);
        }

        /*Remplissage partitiongraph.dot de base*/
        for(i = 0; i < size_l;++i)
        {
            for(j = 0; j < size_c;++j)
            {
                if(i!=j)
                {
                    int val = rand() % 100;
                    matrice[i][j] = val ? 1 : 0;
                }
                    
            }
        }
    }
    
    return matrice;
}

void afficher_matrice(int ** matrice, int taille_ligne, int taille_colonne)
{

    int         i, j;
    for(i = 0; i < taille_ligne;++i)
    {
        for(j = 0; j < taille_colonne;++j)
        {
            fprintf(stdout,"| %d |",matrice[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

void visualiser_matrice(int ** matrice, int size_l, int size_c)
{
    FILE * fichier = NULL;
    fichier = fopen("matrice_graphe.dot", "w");
    if(fichier == NULL)
        exit(EXIT_FAILURE);
    

    fprintf(fichier, "graph {\n");

    for(int i = 0;i <size_l;++i)
    {
        for(int j = 0; j < size_c;++j)
        {
            if(matrice[i][j]==1)
                fprintf(fichier, "\n\t%d--%d", i, j);
        }
        
    }

    fprintf(fichier, "\n}");

    fclose(fichier);

    system("dot -Tjpg matrice_graphe.dot -o img2.jpg");
    system("display ./img2.jpg 2> /dev/null");
}
