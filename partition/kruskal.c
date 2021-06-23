#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kruskal.h"

void arbre_couvrant(int *nouv_aretes, int *nb_aretes, int *aretes, int *nb_elements, int *classes, int *hauteurs, int nouv_taille)
{
    int i = 0, k = 0;
    while (i < *nb_elements)
    {
        int sommet1 = aretes[i];
        int sommet2 = aretes[i+1];
        //printf("couple: %d %d\n", sommet1, sommet2);

        if (classes[sommet1] != classes[sommet2])
        {
            //printf("classes avant : %d %d\n",classes[sommet1],classes[sommet2]);
            //printf("hauteurs avant : %d %d\n",hauteurs[sommet1],hauteurs[sommet2]);
            fusion(sommet1,sommet2,classes,hauteurs);
            //printf("hauteurs apres : %d %d\n",hauteurs[sommet1],hauteurs[sommet2]);
            //printf("classes apres : %d %d\n\n",classes[sommet1],classes[sommet2]);
            ajouter(nouv_aretes,nouv_taille,nb_aretes,sommet1,sommet2);
            k += 2;
        }
        i+= 2;
    }
}

int main()
{
    int classes[TAILLE];
    int hauteurs[TAILLE];
    //srand(time(NULL));
    srand(42);

    int noeuds[TAILLE];
    int aretes[8*TAILLE];    //s'assurer que le nombre de cases est pair (couple d'entiers)
    int taille = 8*TAILLE;
    int nb_elements = 0;

    int nouv_aretes[8*TAILLE];
    int nb_aretes = 0;
    int nouv_taille = 8*TAILLE;

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
                ajouter(aretes,taille,&nb_elements,i,j);
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
        draw_graph(noeuds,aretes,fichier,nb_elements);
        creer(classes,hauteurs);
        arbre_couvrant(nouv_aretes,&nb_aretes,aretes,&nb_elements,classes,hauteurs,nouv_taille);
        draw_graph(noeuds,nouv_aretes,foret,nb_aretes);
        system("dot -Tjpg graph.dot -o graph.jpg");
        system("dot -Tjpg foret.dot -o foret.jpg");
        fclose(fichier);
    }
}