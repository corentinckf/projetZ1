#include "graphe.h"

graphe_t * initialiser_graphe(int nb_noeuds)
{
    graphe_t * graphe = (graphe_t *) malloc(sizeof(graphe_t));
    if(graphe)
    {
        graphe->n_sommet = nb_noeuds;
        graphe->n_arrete = 0;
        arrete_t * l_a = (arrete_t*) malloc(nb_noeuds * nb_noeuds * sizeof(arrete_t)/2);
        if(l_a)
        {
            for(int i = 0; i < nb_noeuds;++i)
            {
                for(int j = i+1; j < nb_noeuds;++j)
                {
                    int val = (rand() % 5) + 1;
                    if(val==1)
                    {   
                        l_a[graphe->n_arrete].a = i;
                        l_a[graphe->n_arrete].b = j;
                        l_a[graphe->n_arrete].poids = 1;
                        ++graphe->n_arrete;
                    }
                }
            }
        }

        graphe->liste_arrete = (arrete_t *) malloc(graphe->n_arrete * sizeof(arrete_t));
        for(int i = 0; i < graphe->n_arrete;++i)
        {
            graphe->liste_arrete[i].a = l_a[i].a;
            graphe->liste_arrete[i].b = l_a[i].b;
        }
        free(l_a);
    }
    
    return graphe;
}
/*
void ajouter_arrete(arrete_t *, graphe_t*);
void supprimer_arrete(int, graphe_t*);*/
void afficher_graphe(graphe_t * graph)
{
    FILE * fichier = NULL;
    fichier = fopen("graphe.dot", "w");
    if(fichier == NULL)
        exit(EXIT_FAILURE);
    

    fprintf(fichier, "graph {\n");

    for(int i = 0;i < graph->n_arrete;++i)
    {
        fprintf(fichier, "\n\t%d--%d", graph->liste_arrete[i].a, graph->liste_arrete[i].b);  
    }

    for(int i = 0;i < graph->n_sommet;++i)
    {
        fprintf(fichier, "\n\t%d", i);  
    }

    fprintf(fichier, "\n}");

    fclose(fichier);

    system("dot -Tjpg graphe.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
}