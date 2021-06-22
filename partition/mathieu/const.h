#ifndef __CONST_H__
#define __CONST_H__

#define HAUTEUR_FENETRE 800
#define LARGEUR_FENETRE 1000

#define NB_LIGNE_LABY 10
#define NB_COLONNE_LABY 10

#define NB_ELT_MAX (NB_LIGNE_LABY * NB_COLONNE_LABY)

#define N NB_ELT_MAX 
#define NB_LIGNE_MAT N
#define NB_COLONNE_MAT N

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define ALEA_GEN 10

#define LARGEUR_CASE LARGEUR_FENETRE/NB_COLONNE_LABY
#define HAUTEUR_CASE HAUTEUR_FENETRE/NB_LIGNE_LABY


#endif