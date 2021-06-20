#ifndef __TAS_BINAIRE_H__
#define __TAS_BINAIRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_ELT_MAX 1000000

/* Strucutre du tas binaire min
tableaa avec case 0 = nb elt
*/

/*

gcc tas_binaire.c -o tas_binaire -Wall -Wextra
./tas_binaire
dot -Tjpg graph_tas.dot -o img.jpg

fichier_graphiz(tas);
system("dot -Tjpg graph_tas.dot -o img.jpg");
system("eog ./img.jpg 2> /dev/null");

*/

void affficher_tab(int *tab, int nb_elt);
void remplir_tab(int tab[NB_ELT_MAX]);
void init_tab(int tab[NB_ELT_MAX]);

int *creer_tas_b(int *tab, int nb_elt);

int f_d(int i);
int f_g(int i);
int pere(int i);

void ajouter_elt(int *, int);
int retirer_elt(int *);

void permute_a_b(int *a, int *b);

void entasser(int *tas, int i);
void detasser(int *tas, int i);

void modifier_cle(int *tas, int indice, int val_ajoutee);
void diminuer_cle(int *tas, int indice, int val_ajoutee);

void fichier_graphiz(int *tas);

int *tri_tas_min(int *tab_valeur, int nb_elt);

static int compare(void const *a, void const *b);

#endif