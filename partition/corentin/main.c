#include "partition.h"

int main()
{
    int  * hauteurs = NULL;
    int ** partition = creer(PART_SIZE, &hauteurs);
    printf("Partition initiale :\n");
    afficher_partition(partition,2,PART_SIZE);

    //printf("\n Classe de %d est %d ! \n", 4, recuperer_classe(partition, 4));

    fusion_arbo(partition,hauteurs,0,1);

    visualiser_graph(partition, PART_SIZE);
    system("dot -Tjpg graph_partition.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");

    fusion_arbo(partition,hauteurs,2,3);

    visualiser_graph(partition, PART_SIZE);
    system("dot -Tjpg graph_partition.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");

    fusion_arbo(partition,hauteurs,10,3);

    visualiser_graph(partition, PART_SIZE);
    system("dot -Tjpg graph_partition.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");

    fusion_arbo(partition,hauteurs,5,9);

    visualiser_graph(partition, PART_SIZE);
    system("dot -Tjpg graph_partition.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");

    fusion_arbo(partition,hauteurs,4,6);

    visualiser_graph(partition, PART_SIZE);
    system("dot -Tjpg graph_partition.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");

    fusion_arbo(partition,hauteurs,8,7);

    visualiser_graph(partition, PART_SIZE);
    system("dot -Tjpg graph_partition.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");

    fusion_arbo(partition,hauteurs,7,9);

    visualiser_graph(partition, PART_SIZE);
    system("dot -Tjpg graph_partition.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");

    fusion_arbo(partition,hauteurs,6,8);

    visualiser_graph(partition, PART_SIZE);
    system("dot -Tjpg graph_partition.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
    /*fusion(partition,3,2);
    fusion(partition,5,6);
    fusion(partition,6,7);
    fusion(partition,6,8);
    fusion(partition,3,10);
    fusion(partition,5,4);
    fusion(partition,7,9);*/

    printf("\n");
    printf("Partition avec diverses fusions :\n");
    afficher_partition(partition,2,PART_SIZE);

    printf("\n");
    printf("Tableau des hauteurs :\n");
    afficher_hauteurs(hauteurs,PART_SIZE);


    //lister_partition(partition, 11);

    return 0;
}