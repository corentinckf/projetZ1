#include "partition.h"
#include "connexe.h"
#include "graphe.h"
#include "kruskal.h"
#include <time.h>

int main()
{
    srand(time(NULL));
    graphe_t * graphe = initialiser_graphe(10);
    //afficher_graphe(graphe);
    kruskal(graphe);
    return 0;
}