#ifndef __gestion_boules_h__
#define __gestion_boules_h__

typedef struct boule{
    int pos_prec;
    int pos_cour;
    int vitesse;
    int vertical;
    int horizontal:
    SDL_Texture *texture;
}boule_t;

#endif