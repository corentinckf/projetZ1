#include "kruskal.h"


graphe_t * kruskal(graphe_t * graphe)
{
    int ** partition = NULL;
    int  * hauteurs = NULL;
    graphe_t * foret = (graphe_t *) malloc(sizeof(graphe_t));
    partition = creer(graphe->n_sommet, &hauteurs);

    /*un petit coup d'affichage initial*/
    //visualiser_graph(partition, graphe->n_sommet);

    /*Pour chaque arête*/
    if(foret)
    {
        foret->n_sommet = graphe->n_sommet;
        foret->n_arrete = 0;
        arrete_t * l_a = (arrete_t*) malloc(graphe->n_arrete * sizeof(arrete_t));
        for(int i = 0; i < graphe->n_arrete;++i)
        {
            sommet a = graphe->liste_arrete[i].a;
            sommet b = graphe->liste_arrete[i].b;

            int classe_a = recuperer_classe_arbo(partition, a);
            int classe_b = recuperer_classe_arbo(partition, b);

            
            if(classe_a != classe_b)
            {
                //fusionner les arrêtes
                fusion_arbo(partition,hauteurs, a, b);
                //Et ajouter l'arrête à liste_arrete
                l_a[foret->n_arrete] = graphe->liste_arrete[i];
                ++foret->n_arrete;
            }

        }

        foret->liste_arrete = (arrete_t *) malloc(foret->n_arrete * sizeof(arrete_t));
        for(int i = 0; i < foret->n_arrete;++i)
        {
            foret->liste_arrete[i] = l_a[i];
        }

        free(l_a);
    }

    return foret;
    
}
