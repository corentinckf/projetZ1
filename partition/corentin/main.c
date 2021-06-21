#include "partition.h"
#include "connexe.h"

int main()
{
    int ** mat_adj = NULL;
    srand(42);
    mat_adj = init_adj_mat(MAT_SIZE, MAT_SIZE);
    afficher_matrice(mat_adj, MAT_SIZE, MAT_SIZE);
    visualiser_matrice(mat_adj, MAT_SIZE, MAT_SIZE);
    return 0;
}