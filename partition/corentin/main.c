#include "partition.h"

int main()
{
    int ** partition = creer(11);
    afficher_partition(partition,2,11);

    //printf("\n Classe de %d est %d ! \n", 4, recuperer_classe(partition, 4));

    fusion(partition,0,1);
    fusion(partition,3,2);
    fusion(partition,5,6);
    fusion(partition,6,7);
    fusion(partition,6,8);
    fusion(partition,3,10);
    fusion(partition,5,4);
    fusion(partition,7,9);
    
    printf("\n");
    afficher_partition(partition,2,11);
    return 0;
}