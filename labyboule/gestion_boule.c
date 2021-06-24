#include "gestion_boule.h"

void deplacement_boule(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *boule, int pos_perso)
{
    int distance[N];
    int parent[N];
    dijkstra(map, pos_perso, distance, parent);
    //affficher_tab(parent, N);
    //printf("pos=%d et parent[]%d\n", boule->pos_cour, parent[boule->pos_cour]);
    if (parent[boule->pos_cour] != -1) //chemin existe
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
            boule->vertical = 1;
        else if (dir == -1)
            boule->vertical = -1;
        else if (dir == NB_COLONNE_LABY)
            boule->horizontal = 1;
        else if (dir == -NB_COLONNE_LABY)
            boule->horizontal = -1;
    }
    else
    {
        printf("chemin impossible\n");
    }
}

void deplacement_toutes_boules(int map[NB_LIGNE_LABY][NB_COLONNE_LABY],
                               entite_t *liste_boules[NB_BOULES], int pos_perso)
{
    int map_bis_tab[NB_LIGNE_LABY][NB_COLONNE_LABY];
    for (int k = 0; k < NB_BOULES; ++k)
        if (liste_boules[k] != NULL)
        {
            //calcul map_bis
            map_bis(map, map_bis_tab, liste_boules, k);
            deplacement_boule(map, liste_boules[k], pos_perso);
        }
}

void liberer_liste_boule(entite_t *liste_boule[NB_BOULES])
{
    for (int k = 0; k < NB_BOULES; ++k)
        liberer_entite(liste_boule[k]);
}
