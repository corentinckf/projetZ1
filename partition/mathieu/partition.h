#ifndef __PARTITION_H__
#define __PARTITION_H__

//gcc partition.c -o partition -Wall -Wextra

#include <stdio.h>
#include <stdlib.h>

int creer_partition_tab(int **tab, int n);
void afficher_partition_tab(int **tab, int taille);
#endif