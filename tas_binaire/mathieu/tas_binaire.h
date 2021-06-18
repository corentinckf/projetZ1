#ifndef __TAS_BINAIRE_H__
#define __TAS_BINAIRE_H__

#include <stdio.h>
#include <stdlib.h>

#define NB_ELT_MAX 50

typedef struct tas_binaire
{
    int nb_elt;
    int arbre[NB_ELT_MAX];
}tas_binaire_t;

int creer_tas_b(tas_binaire_t *, int valeur[NB_ELT_MAX]);

int f_d(int i);
int f_g(int i);
int pere(int i);

void percolate_up(tas_binaire_t *tas);
void percolate_down(tas_binaire_t *tas);

void permute_a_b(int *a, int *b);

void ajouter_elt(tas_binaire_t *tas, int elt);
int retirer(tas_binaire_t *tas);

#endif