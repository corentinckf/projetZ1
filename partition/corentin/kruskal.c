#include "kruskal.h"


void kruskal(graphe_t * graphe)
{
    int ** partition = NULL;
    int  * hauteurs = NULL;
    partition = creer(graphe->n_sommet, hauteurs);

    arrete_t * liste_arrete = (arrete_t *) malloc(graphe->n_sommet *
                                                  graphe->n_sommet * 
                                                  sizeof(arrete_t)
                                                  / 2);
    /*un petit coup d'affichage initial*/
    //visualiser_graph(partition, graphe->n_sommet);

    /*Pour chaque arête*/

    for(int i = 0; graphe->n_arrete;++i)
    {
        printf("ntm");
        sommet a = graphe->liste_arrete[i].a;
        sommet b = graphe->liste_arrete[i].b;

        int classe_a = recuperer_classe(partition, a);
        int classe_b = recuperer_classe(partition, b);

        if(classe_a != classe_b)
        {
            //fusionner les arrêtes
            fusion_arbo(partition,hauteurs, a, b);
            //Et ajouter l'arrête à liste_arrete
        }

    }

    //visualiser_graph(partition, graphe->n_sommet);

}