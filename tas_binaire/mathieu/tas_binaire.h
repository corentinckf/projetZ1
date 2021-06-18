#ifndef __TAS_BINAIRE_H__
#define __TAS_BINAIRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_ELT_MAX 20

/*
gcc tas_binaire.c -o tas_binaire -Wall -Wextra
./tas_binaire
dot -Tjpg graph_tas.dot -o img.jpg

*/

typedef struct tas_binaire
{
    int nb_elt;
    int arbre[NB_ELT_MAX];
} tas_binaire_t;

void affficher_tab(int tab[NB_ELT_MAX]);
void remplir_tab(int tab[NB_ELT_MAX]);
void init_tab(int tab[NB_ELT_MAX]);

tas_binaire_t *creer_tas_b(int tab[NB_ELT_MAX], int valeur[NB_ELT_MAX]);
void entasser(tas_binaire_t *tas, int i);

int f_d(int i);
int f_g(int i);
int pere(int i);


void permute_a_b(int *a, int *b);


void fichier_graphiz(tas_binaire_t *tas);

#endif