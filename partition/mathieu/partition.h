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

#define NB_ELT_MAX 10


void creer_partition(int tab[2][NB_ELT_MAX]);
void afficher_partition(int tab[2][NB_ELT_MAX]);

int recuperer_classe(int tab[2][NB_ELT_MAX], int elt);

void fichier_graphviz(int *tas);

#endif