#include "gestion_boule.h"

void deplacement_boule(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *boule, int pos_perso)
{
    int map_bis[NB_LIGNE_LABY][NB_COLONNE_LABY];
    //calcul map_bis

    int distance[N];
    int parent[N];
    dijkstra(map_bis, pos_perso, distance, parent);

    if (parent[boule->pos_cour] != -1)
    {
        //for (int i = 0; i < boule->vitesse; ++i)
        //{
        boule->pos_prec = boule->pos_cour;
        boule->pos_cour = parent[pos];
        //}

        int dir = boule->pos_cour - boule->pos_prec;
        boule->horizontal = 0;
        boule->vertical = 0;

        if (dir == 1)
            boule->horizontal = 1;
        else if (dir == -1)
            boule->horizontal = -1;
        else if (dir == NB_COLONNE_LABY)
            boule->vertical = 1;
        else if (dir == -NB_COLONNE_LABY)
            boule->vertical = -1;
    }
    else
    {
        printf("chemin impossilbe\n");
    }
}