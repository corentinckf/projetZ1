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

void afficher_hauteurs(int * hauteurs, int taille_partition)
{
    int         j;

    for(j = 0; j < taille_partition;++j)
    {
        fprintf(stdout,"| %d |",hauteurs[j]);
    }
}

/*crée à partir d'un ensemble E
    la partition où chaque élément est seul dans sa classe*/
int ** creer(int taille_ensemble, int ** hauteurs)
{
    int         ** partition = (int **) malloc(2 * sizeof(int *));
                   *hauteurs = (int *) calloc(taille_ensemble, sizeof(int));
    int            i = 0, j;

    if(partition && hauteurs)
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
            partition[0][i] = i;
            partition[1][i] = i;
        }
    }
    
    return partition;

}

/*prend en entrée un élément x∈E et renvoie un identifiant unique de la classe à laquelle appartient x
    */
int recuperer_classe(int ** partition, int element)
{
    return partition[1][element];
}

/*prend deux éléments x,y de E en entrée et fusionne les classes de x et de y
    dans la partition*/ 
void fusion(int ** partition, int a, int b)
{
    int classe = recuperer_classe(partition,a);
    partition[1][b] = classe;
}

void fusion_arbo(int ** partition,int * hauteurs, int a, int b)
{
    int classeA = recuperer_classe(partition, a);
    int classeB = recuperer_classe(partition, b);

    if(classeA != classeB)
    {
        if(hauteurs[classeA] > hauteurs[classeB])
        {
            partition[1][classeB] = classeA;
        }else if(hauteurs[classeA] < hauteurs[classeB])
        {   
            partition[1][classeA] = classeB;
        }else
        {
            partition[1][classeB] = classeA;
            ++hauteurs[classeA];
        }
    }
}
    
/*prend en entrée une étiquette de classe, et renvoie les éléments de cette classe,*/
 int * lister_classe(int ** partition, int taille_partition, int classe)
 {
     int * liste = (int *) malloc((taille_partition + 1) * sizeof(int));
     if(liste)
     {
         int nb_element = 1;
         for(int i = 1; i < taille_partition;++i)
         {
             if(partition[1][i]==classe)
             {
                 printf("%d\n", partition[0][i]);
                 liste[nb_element] = partition[0][i];
                 ++nb_element;
             }
                
         }

         liste[0] = nb_element;
         liste = (int *) realloc(liste, nb_element * sizeof(int));
     }

     return liste;
 }

/*renvoie la liste des classes*/
void lister_partition(int ** partition, int taille_partition)
{
    cellule ** gigatab = (cellule **) malloc(taille_partition * sizeof(cellule *));
    for(int i = 0; i < taille_partition;++i)
    {
            cellule * cell = alloc_cellule(partition[0][i], NULL);
            ajouter_cellule(&gigatab[partition[1][i]], cell);
    }

    for(int i = 0; i < taille_partition;++i)
    {
        printf("Classe %d :", i);
        afficher_lch(gigatab[i], stdout);
        printf("\n");
    }
}

void visualiser_graph(int ** partition, int taille_classes)
{
    FILE * fichier = NULL;
    fichier = fopen("graph_partition.dot", "w");
    if(fichier == NULL)
        exit(EXIT_FAILURE);
    

    fprintf(fichier, "digraph {\n");

    for(int i = 0;i <taille_classes;++i)
    {
        fprintf(fichier, "\n\t%d->%d", partition[0][i], partition[1][i]);
    }

    fprintf(fichier, "\n}");

    fclose(fichier);

    system("dot -Tjpg graph_partition.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
}
    