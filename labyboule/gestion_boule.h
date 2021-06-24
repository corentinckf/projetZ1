#ifndef __GESTION_BOULE_H__
#define __GESTION_BOULE_H__

#include "const.h"


typedef struct entite{
    int pos_prec;
    int pos_cour;
    int vitesse;
    int vertical;
    int horizontal;
    SDL_Texture *texture;
}entite_t;


void deplacement_boule(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *boule, int pos_perso);

void deplacement_toutes_boules(int map[NB_LIGNE_LABY][NB_COLONNE_LABY],
                               entite_t liste_boules[NB_BOULES], int pos_perso);


#endif