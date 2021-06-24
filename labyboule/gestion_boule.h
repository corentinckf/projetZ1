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


#endif