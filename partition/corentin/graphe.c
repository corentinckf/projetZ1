#include "graphe.h"

void initialiser_arrete(arrete_t * arrete, sommet a, sommet b)
{
    arrete->a = a;
    arrete->b = b;
}

graphe_t * initialiser_graphe(int nb_noeuds)
{
    graphe_t * graphe = (graphe_t *) malloc(sizeof(graphe_t));
    if(graphe)
    {
        arrete_t * liste_arrete = (arrete_t*) malloc(nb_noeuds * nb_noeuds * sizeof(arrete_t)/2);
        if(liste_arrete)
        {
            for(int i = 0; i < nb_noeuds;++i)
            {
                for(int j = 0; j < nb_noeuds;++j)
                {
                    int val = (rand() % 10) + 1;
                    if(val==1)
                    {   
                        initialiser_arrete(&liste_arrete[graphe->n_sommet],i,j);
                        ++graphe->n_sommet;
                    }
                }
            }
        }

        graphe->liste_arrete = (arrete_t *) malloc(graphe->n_sommet * sizeof(arrete_t));
        for(int i = 0; i < graphe->n_sommet;++i)
        {
            initialiser_arrete(&graphe->liste_arrete[i], liste_arrete[i].a, liste_arrete[i].b);
            ++graphe->n_arrete;
        }
            
        
        free(liste_arrete);
    }
    
    return graphe;
}
/*
void ajouter_arrete(arrete_t *, graphe_t*);
void supprimer_arrete(int, graphe_t*);*/
void afficher_graphe(graphe_t * graph)
{
    FILE * fichier = NULL;
    fichier = fopen("graphe_graphe.dot", "w");
    if(fichier == NULL)
        exit(EXIT_FAILURE);
    

    fprintf(fichier, "graph {\n");

    for(int i = 0;i < graph->n_sommet;++i)
    {
        fprintf(fichier, "\n\t%d--%d", graph->liste_arrete[i].a, graph->liste_arrete[i].b);  
    }

    fprintf(fichier, "\n}");

    fclose(fichier);

    system("dot -Tjpg graphe_graphe.dot -o img3.jpg");
    system("display ./img3.jpg 2> /dev/null");
}