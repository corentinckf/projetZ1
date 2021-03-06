#include "partition.h"
#include "connexe.h"
#include "graphe.h"
#include "kruskal.h"
#include "labyrinth.h"
#include <time.h>

int main()
{
    srand(17091999);
    graphe_t * graphe = init_graphe_labyrinth(5, 5);
    //graphe_t * graphe = initialiser_graphe(10);
    //afficher_graphe(graphe);
    fisher_yates_shuffle(graphe);
    /*afficher_graphe(graphe);*/
    graphe_t * foret = kruskal(graphe);
    afficher_graphe(foret);
    return 0;
}