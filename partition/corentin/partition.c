#include "partition.h"

void afficher_partition(int ** partition, int taille_ligne, int taille_colonne)
{

    int         i, j;
    for(i = 0; i < taille_ligne;++i)
    {
        for(j = 0; j < taille_colonne;++j)
        {
            fprintf(stdout,"| %d |",partition[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

int ** creer(int * ensemble, int taille_ensemble)
{
    int         ** partition = (int **) malloc(2 * sizeof(int *));
    int            i = 0, j;

    if(partition)
    {
        while(i < 2 && (partition[i] = (int *) malloc(taille_ensemble * sizeof(int))))
            ++i;

        if(i < 2)
        {
            for(j = i; j >= 0;--j)
                free(partition[i]);
        }

        /*Remplissage partition de base*/
        for(i = 0; i < taille_ensemble;++i)
        {
            partition[0][i] = ensemble[i];
            partition[1][i] = ensemble[i];
        }
    }
    
    return partition;

}
    /*crée à partir d'un ensemble E
    la partition où chaque élément est seul dans sa classe*/
int recuperer_classe(int ** partition, int element)
{

}
    /*prend en entrée un élément x∈E et renvoie un identifiant unique de la classe à laquelle appartient x
    */
/*void fusion();*/
    /*prend deux éléments x,y de E en entrée et fusionne les classes de x et de y
    dans la partition*/
/*void lister_classe();*/
    /*prend en entrée une étiquette de classe, et renvoie les éléments de cette classe,*/
/*void lister_partition();*/
    /*renvoie la liste des classes*/