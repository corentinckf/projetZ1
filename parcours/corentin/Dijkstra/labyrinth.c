#include "labyrinth.h"

graphe_t * init_graphe_labyrinth(int c_laby, int l_laby)
{
    graphe_t * graphe = (graphe_t *) malloc(sizeof(graphe_t));
    if(graphe)
    {
        graphe->n_sommet = c_laby * l_laby;
        graphe->n_arrete = 0;
        arrete_t * l_a = (arrete_t*) malloc(2 * sizeof(arrete_t) * graphe->n_sommet - c_laby - l_laby);
        if(l_a)
        {
            for(int i = 0; i < graphe->n_sommet;++i)
            {
                if((i + 1) % c_laby != 0)
                {
                    l_a[graphe->n_arrete].a = i;
                    l_a[graphe->n_arrete].b = i + 1;
                    ++graphe->n_arrete;
                }
                if(i + c_laby < graphe->n_sommet)
                {
                    l_a[graphe->n_arrete].a = i;
                    l_a[graphe->n_arrete].b = i + c_laby;
                    ++graphe->n_arrete;
                }
                
            }
        }

        graphe->liste_arrete = (arrete_t *) malloc(graphe->n_arrete * sizeof(arrete_t));
        for(int i = 0; i < graphe->n_arrete;++i)
        {
            graphe->liste_arrete[i].a = l_a[i].a;
            graphe->liste_arrete[i].b = l_a[i].b;
            graphe->liste_arrete[i].poids = 1;
        }
        free(l_a);
    }
    
    return graphe;
}
void fisher_yates_shuffle(graphe_t * graphe)
{
    for(int i = graphe->n_arrete - 1; i >= 1; --i)
    {
        int j = rand() % i + 1;
        change(&graphe->liste_arrete[i].a, &graphe->liste_arrete[j].a);
        change(&graphe->liste_arrete[i].b, &graphe->liste_arrete[j].b);
    }
}

void change(sommet * a, sommet * b)
{
    sommet temp = *a;
    *a = *b;
    *b = temp;
}