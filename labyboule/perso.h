#ifndef __PERSO_H__
#define __PERSO_H__

#include "const.h"

void deplacement_perso(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *, int *, int *);
void deplacement_perso_alternatif(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *perso, int *v, int *h);

#endif