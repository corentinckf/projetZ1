#ifndef __PARTITION_H__
#define __PARTITION_H__

//gcc partition.c -o partition -Wall -Wextra
/*
fichier_graphviz(tas);
system("dot -Tjpg graph_tas.dot -o img.jpg");
system("display ./img.jpg 2> /dev/null");

*/

#include <stdio.h>
#include <stdlib.h>

#include "liste_chainee.h"

#define NB_ELT_MAX 10

void creer_partition(int tab[2][NB_ELT_MAX]);
void creer_partition_arbo(int part[2][NB_ELT_MAX], int hauteur[NB_ELT_MAX]);


void afficher_partition(int tab[2][NB_ELT_MAX]);
void fusion(int part[2][NB_ELT_MAX], int x, int y);
void fusion_arbo(int part[2][NB_ELT_MAX],int hauteur[NB_ELT_MAX], int x, int y);

int recuperer_classe(int tab[2][NB_ELT_MAX], int elt);
int lister_classe_a_partir_elt(int part[2][NB_ELT_MAX], int elt, int classe[NB_ELT_MAX]);
int lister_classe(int part[2][NB_ELT_MAX], int etiquette, int classe[NB_ELT_MAX]);

void lister_partition(int part[2][NB_ELT_MAX]);

void fichier_graphviz(int part[2][NB_ELT_MAX]);

#endif