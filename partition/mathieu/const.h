#ifndef __CONST_H__
#define __CONST_H__

#define HAUTEUR_FENETRE 900
#define LARGEUR_FENETRE 500

#define NB_LIGNE_LABY 4
#define NB_COLONNE_LABY 5

#define NB_ELT_MAX (NB_LIGNE_LABY *NB_COLONNE_LABY)

#define N NB_ELT_MAX //def dans partition.h
#define NB_LIGNE_MAT N
#define NB_COLONNE_MAT N

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define ALEA_GEN 2

#endif