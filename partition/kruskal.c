#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kruskal.h"

//fonction de passage d'un noeud a son entier
int noeud_entier(int i)
{
    return i;   //le numero du noeud correspond a son entier
}

int *alloc(int *tab, int *taille)
{
    *taille *= 2;
    int *nouvtab = (int *) malloc((*taille) * sizeof(int));
    for (int k=0;k<(*taille)/2;k++)
    {
        nouvtab[k] = tab[k];
    }
    return nouvtab;
}

void ajouter(int *tab, int *taille, int *nb_elements, int i, int j)
{
    if (*taille == nb_elements)
    {
        tab = alloc(tab,taille);
    }
    tab[*nb_elements] = i;
    (*nb_elements)++;
    tab[*nb_elements] = j;
    (*nb_elements)++;
}

void draw_graph(int *noeuds, int aretes[4*TAILLE], FILE *fichier, int nb_elements)
{
    fprintf(fichier,"graph {\n");
    int k=0;

    for (int l=0;l<TAILLE;l++)
    {
        fprintf(fichier,"\t%d\n",noeuds[l]);
    }

    while (k < nb_elements)
    {
        fprintf(fichier,"\t%d -- %d\n", noeud_entier(aretes[k]),noeud_entier(aretes[k+1]));
        k += 2;
    }
    fprintf(fichier,"}");
}

void arbre_couvrant(int *nouv_aretes, int *nb_aretes, int *aretes, int *nb_elements, int *classes, int *hauteurs, FILE *fichier)
{
    int k = 0;
    int i = 0;
    while (k < *nb_elements)
    {
        while (i < *nb_aretes)
        {
            if (aretes[k] != nouv_aretes[i] || aretes[k+1] != nouv_aretes[i+1])
            {
                nouv_aretes[i] = aretes[k];
                nouv_aretes[i+1] = aretes[k+1];
                fusion(nouv_aretes[i],nouv_aretes[i+1],classes,hauteurs);
                *nb_aretes += 2;
            }
            i += 2;
        }
        nouv_aretes[i] = aretes[k];
        nouv_aretes[i+1] = aretes[k+1];
        fusion(nouv_aretes[i],nouv_aretes[i+1],classes,hauteurs);
        *nb_aretes += 2;
        k += 2;
    }
    graph_partition(fichier,classes);
}

int main()
{
    int classes[TAILLE];
    int hauteurs[TAILLE];
    //srand(time(NULL));
    srand(42);

    int noeuds[TAILLE];
    int aretes[4*TAILLE];    //s'assurer que le nombre de cases est pair (couple d'entiers)
    int taille = 2*TAILLE;
    int nb_elements = 0;

    int nouv_aretes[4*TAILLE];
    int nb_aretes = 0;

    //initialisation
    for (int i=0;i<TAILLE;i++)
    {
        noeuds[i] = i;
    }

    for (int i=0;i<TAILLE;i++)
    {   
        for (int j=i+1;j<TAILLE;j++)
        {
            int valeur = rand()%2;
            if (valeur)
            {
                ajouter(aretes,&taille,&nb_elements,i,j);
            }
        }
    }

    FILE *fichier = NULL;
    fichier = fopen("graph.dot","w");
    FILE *foret = NULL;
    foret = fopen("foret.dot","w");

    if (fichier && foret)
    {
        //printf("ok\n");
        draw_graph(noeuds, aretes,fichier,nb_elements);
        creer(classes,hauteurs);
        arbre_couvrant(nouv_aretes,&nb_aretes,aretes,&nb_elements,classes,hauteurs,foret);
        system("dot -Tjpg graph.dot -o graph.jpg");
        fclose(fichier);
    }
}