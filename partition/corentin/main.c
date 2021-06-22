#include "partition.h"
#include "connexe.h"
#include "graphe.h"
#include <time.h>

int main()
{
    //int ** mat_adj = NULL;
    srand(time(NULL));
    /*mat_adj = init_adj_mat(MAT_SIZE, MAT_SIZE);
    afficher_matrice(mat_adj, MAT_SIZE, MAT_SIZE);
    visualiser_matrice(mat_adj, MAT_SIZE, MAT_SIZE);*/
    graphe_t * graphe = initialiser_graphe(10);
    afficher_graphe(graphe);
    return 0;
}