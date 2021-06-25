#include "perso.h"

void deplacement_perso(int map[NB_LIGNE_LABY][NB_COLONNE_LABY],entite_t* perso,int* v,int*h)
{

    int i = perso->pos_prec / NB_COLONNE_LABY;
    int j = perso->pos_prec % NB_COLONNE_LABY;

    perso->pos_prec = perso->pos_cour;

    if(*h==1) ++perso->pos_cour;
    else if(*h==-1) --perso->pos_cour;
    perso->vertical = *h;
    
    if(*v==1) perso->pos_cour += NB_COLONNE_LABY;
    else if(*v==-1) perso->pos_cour -= NB_COLONNE_LABY;
    perso->horizontal = *v;
    

}
