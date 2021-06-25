#ifndef __GESTION_BOULE_H__
#define __GESTION_BOULE_H__

#include "const.h"

void deplacement_boule(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *boule, int pos_perso);

void deplacement_toutes_boules(int map[NB_LIGNE_LABY][NB_COLONNE_LABY],
                               entite_t *liste_boules[NB_BOULES], int pos_perso);
void liberer_liste_boule(entite_t *liste_boule[NB_BOULES]);

#endif