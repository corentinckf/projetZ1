#ifndef __TAS_BINAIRE_H__
#define __TAS_BINAIRE_H__

#include "const.h"


/*

gcc tas_binaire.c -o tas_binaire -Wall -Wextra
./tas_binaire
dot -Tjpg graph_tas.dot -o img.jpg

fichier_graphiz(tas);
system("dot -Tjpg graph_tas.dot -o img.jpg");
system("display ./img.jpg 2> /dev/null");

*/



typedef struct tas_binaire
{
    couple_t tas[N];
    int nb_elt;
    int info_n[N];
    int indice_tas[N];
} tas_binaire_t;

int main_tas_binaire();

/*
void affficher_tab(int *tab, int nb_elt);
void remplir_tab(int tab[NB_ELT_MAX]);
void init_tab(int tab[NB_ELT_MAX]);
*/

tas_binaire_t *creer_tas_b(couple_t val_couple);

int f_d(int i);
int f_g(int i);
int pere(int i);

void ajouter_elt(tas_binaire_t *, couple_t);
couple_t retirer_elt(tas_binaire_t *);

//void permute_a_b(int *a, int *b);

void entasser(tas_binaire_t *tas, int i);
void detasser(tas_binaire_t *tas, int i);

void modifier_cle(tas_binaire_t *tas, int indice, int val_ajoutee);
void diminuer_cle(tas_binaire_t *tas, int indice, int val_ajoutee);

void fichier_graphiz(tas_binaire_t *tas);

int *tri_tas_min(tas_binaire_t *tab_valeur);

static int compare(void const *a, void const *b);

#endif