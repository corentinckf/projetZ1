#ifndef __GESTION_MAP_H__
#define __GESTION_MAP_H__

#include "const.h"
#include "gestion_entites.h"

void init_map(int map[NB_LIGNE_MAT][NB_COLONNE_LABY]);
void map_bis(int map[NB_LIGNE_LABY][NB_COLONNE_LABY],int map_bis_tab[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *tab[NB_BOULES], int boule_cour);

#endif