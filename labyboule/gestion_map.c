#include "gestion_map.h"

void init_map(int map[NB_LIGNE_MAT][NB_COLONNE_LABY])
{
    float p = 0.05;

    //generation graph arete
    graph_l_arete_t *graph = NULL;
    graph = init_graph_arete_en_grille();

    //affiche le graphe
    //graphviz_affiche_graph_arete(graph);

    melange_fisher_yates_arete(graph);

    //Generation quasi arbre
    graph_l_arete_t *quasi_arbre = NULL;
    quasi_arbre = calcul_quasi_foret_couvrant(graph, p);

    liberer_graph_arete(graph);

    //afficher quasi_arbre
    //graphviz_affiche_graph_arete(quasi_arbre);

    construire_map(map, quasi_arbre);
    liberer_graph_arete(quasi_arbre);
}

void map_bis(int map_bonne[NB_LIGNE_LABY][NB_COLONNE_LABY], int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *tab[NB_BOULES], int boule_cour)
{
    int position;
    int i, j;

    for (int i = 0; i < NB_LIGNE_LABY; ++i)
    {
        for (j = 0; j < NB_COLONNE_LABY; ++j)
        {
            map[i][j] = map_bonne[i][j];
        }
    }

    for (int k = 0; k < NB_BOULES; k++)
    {
        if (k != boule_cour)
        {
            position = (tab[k])->pos_cour;
            i = position / NB_COLONNE_LABY;
            j = position % NB_COLONNE_LABY;
            map[i][j] = 15;

            if (i == 0 && j == 0) //case en haut a gauche
            {
                map[i][j + 1] += 4; //mur ouest sur case a droite
                map[i + 1][j] += 2; //mur nord sur case en dessous
            }
            else if (i == 0 && j + 1 == NB_COLONNE_LABY) //case en haut a droite
            {
                map[i + 1][j] += 2; //mur nord sur case en dessous
                map[i][j - 1] += 1; //mur est sur case a gauche
            }
            else if (i == 0) //premiere ligne sans les deux extremites
            {
                map[i + 1][j] += 2; //mur nord sur case en dessous
                map[i][j - 1] += 1; //mur est sur case a gauche
                map[i][j + 1] += 4; //mur ouest sur case a droite
            }
            else if (i == NB_LIGNE_LABY && j == 0) //case en bas a gauche
            {
                map[i - 1][j] += 8; //mur sud sur case au dessus
                map[i][j + 1] += 4; //mur ouest sur case a droite
            }
            else if (j == 0) //premiere colonne sans les deux extremites
            {
                map[i - 1][j] += 8; //mur sud sur case au dessus
                map[i + 1][j] += 2; //mur nord sur case en dessous
                map[i][j + 1] += 4; //mur ouest sur case a droite
            }
            else if (i == NB_LIGNE_LABY && j + 1 == NB_COLONNE_LABY) //case en bas a droite
                map[i][j - 1] += 1;                                  //mur est sur case a gauche
            map[i - 1][j] += 8;                                      //mur sud sur case au dessus
        }
        else if (i == NB_LIGNE_LABY) //derniere ligne sans les deux extremites
        {
            map[i - 1][j] += 8; //mur sud sur case au dessus
            map[i][j - 1] += 1; //mur est sur case a gauche
            map[i][j + 1] += 4; //mur ouest sur case a droite
        }
        else if (j == NB_COLONNE_LABY) //derniere colonne sans les deux extremites
        {
            map[i - 1][j] += 8; //mur sud sur case au dessus
            map[i + 1][j] += 2; //mur nord sur case en dessous
            map[i][j - 1] += 1; //mur est sur case a gauche
        }
        else //toutes les autres cases
        {
            map[i - 1][j] += 8; //mur sud sur case au dessus
            map[i][j - 1] += 1; //mur est sur case a gauche
            map[i + 1][j] += 2; //mur nord sur case en dessous
            map[i][j + 1] += 4; //mur ouest sur case a droite
        }
    }
}
