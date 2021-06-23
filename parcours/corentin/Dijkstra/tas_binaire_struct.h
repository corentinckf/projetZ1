#ifndef __TAS_BINAIRE_H__
#define __TAS_BINAIRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphe.h"

#define NB_ELT_MAX 9

typedef struct tas_binaire
{
    int nb_elt;
    arrete_t arbre[NB_ELT_MAX];
} tas_binaire_t;

//void affficher_tab(arrete_t  tab[NB_ELT_MAX]);
void remplir_tab(arrete_t  tab[NB_ELT_MAX]);
//void init_tab(arrete_t  tab[NB_ELT_MAX]);

//tas_binaire_t *creer_tas_b(arrete_t  tab[NB_ELT_MAX]);

int f_d(int i);
int f_g(int i);
int pere(int i);

arrete_t retirer_elt(tas_binaire_t *);
void ajouter_arr(tas_binaire_t *, arrete_t);

void permute_a_b(arrete_t *a, arrete_t *b);

void entasser(tas_binaire_t *tas, int i);
void detasser(tas_binaire_t *tas, int i);

//void diminuer_cle(tas_binaire_t *tas, int indice, int val_ajoutee);

//void fichier_graphiz(tas_binaire_t *tas);

#endif