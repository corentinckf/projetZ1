#ifndef __PARTITION_H__
#define __PARTITION_H__

//gcc partition.c -o partition -Wall -Wextra
/*
fichier_graphiz(tas);
system("dot -Tjpg graph_tas.dot -o img.jpg");
system("display ./img.jpg 2> /dev/null");

*/

#include <stdio.h>
#include <stdlib.h>

int** creer_partition_tab( int n);
void afficher_partition_tab(int **tab, int taille);

void fichier_graphiz(int *tas);

#endif