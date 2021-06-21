#include "partition.h"

int main()
{
    int ensemble[] = {0,1,2,3,4,5,6,7,8,9,10};
    int ** partition = creer(ensemble, 11);
    afficher_partition(partition,2,11);
    return 0;
}