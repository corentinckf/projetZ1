#include "kruskal.h"


void kruskal(graphe_t * graphe)
{
    int ** partition = NULL;
    int  * hauteurs = NULL;
    partition = creer(graphe->n_sommet, &hauteurs);

    arrete_t * liste_arrete = (arrete_t *) malloc(graphe->n_sommet *
                                                  graphe->n_sommet * 
                                                  sizeof(arrete_t)
                                                  / 2);
    /*un petit coup d'affichage initial*/
    visualiser_graph(partition, graphe->n_sommet);

    /*Calcul de la composante connexe*/
    connexe_graph2(partition, hauteurs, graphe);
    /*Pour chaque arête*/
    for(int i = 0; graphe->n_arrete;++i)
    {

    }

}