#include "gestion_boule.h"

void deplacement_boule(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *boule, int pos_perso)
{
    int map_bis[NB_LIGNE_LABY][NB_COLONNE_LABY];
    //calcul map_bis

    int distance[N];
    int parent[N];
    dijkstra(map_bis, pos_perso, distance, parent);
    //affficher_tab(parent, N);

    if (parent[0] != -1) //chemin existe
    {
        //for (int i = 0; i < boule->vitesse; ++i)
        //{
        boule->pos_prec = boule->pos_cour;
        boule->pos_cour = parent[boule->pos_cour];
        //}

        /**********Gestion de l'orientation du perso **********/
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
        printf("chemin impossible\n");
    }
}

void deplacement_toutes_boules(int map[NB_LIGNE_LABY][NB_COLONNE_LABY],
                               entite_t *liste_boules[NB_BOULES], int pos_perso)
{
    for (int k = 0; k < NB_BOULES; ++k)
        if (liste_boules[k] != NULL)
        {
            deplacement_boule(map, liste_boules[k], pos_perso);
        }
}