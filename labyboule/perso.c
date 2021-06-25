#include "perso.h"

void deplacement_perso(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *perso, int *v, int *h)
{

    int i = perso->pos_cour / NB_COLONNE_LABY;
    int j = perso->pos_cour % NB_COLONNE_LABY;

    int peut_d = 1, peut_g = 1, peut_h = 1, peut_b = 1;

    unsigned mur = (unsigned)map[i][j];

    if ((perso->pos_cour + 1) % NB_COLONNE_LABY != 0 && !(mur & (unsigned)mur_est))
        peut_d = 1;
    else
        peut_d = 0;

    if (perso->pos_cour - 1 > 0 && !(mur & (unsigned)mur_ouest))
        peut_g = 1;
    else
        peut_g = 0;

    if (perso->pos_cour - NB_COLONNE_LABY > 0 && !(mur & (unsigned)mur_nord))
        peut_h = 1;
    else
        peut_h = 0;

    if (perso->pos_cour + NB_COLONNE_LABY < N && !(mur & (unsigned)mur_sud))
        peut_b = 1;
    else
        peut_b = 0;

    perso->pos_prec = perso->pos_cour;

    if (*h == 1 && peut_d)
    {
        ++perso->pos_cour;
        perso->vertical = 1;
    }
    else if (*h == -1 && peut_g)
    {
        --perso->pos_cour;
        perso->vertical = -1;
    }
    else
        perso->vertical = 0;

    if (*v == 1 && peut_b)
    {
        perso->pos_cour += NB_COLONNE_LABY;
        perso->horizontal = 1;
    }
    else if (*v == -1 && peut_h)
    {
        perso->pos_cour -= NB_COLONNE_LABY;
        perso->horizontal = -1;
    }
    else
        perso->horizontal = 0;
}
