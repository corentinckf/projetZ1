#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "creation_map.h"

void map_bis(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], entite_t *tab[NB_BOULES], int i)
{
    int position;
    for (int k=0;k < NB_BOULES; k++)
    {
        position = (tab[k])->pos_cour;
        int i = position /  NB_COLONNE_LABY;
        int j = position %  NB_COLONNE_LABY;
        map[i][j] = 15;

        if (i == 0 && j == 0)    //case en haut a gauche
        {
            mat[i][j+1] = 4;    //mur ouest sur case a droite
        }
        else if (i == 0 && j+1 == NB_COLONNE_LABY)  //case en haut a droite
        {
            mat[i+1][j] = 2;    //mur nord sur case en dessous
            mat[i][j-1] = 1;    //mur est sur case a gauche
        }
        else if (i == 0)    //premiere ligne sans les deux extremites
        {
            mat[i+1][j] = 2;    //mur nord sur case en dessous
            mat[i][j-1] = 1;    //mur est sur case a gauche
            mat[i][j+1] = 4;    //mur ouest sur case a droite
        }
                
        else if (i != 0 && j == 0) //premiere colonne sans la premiere case
        {
             mat[i-1][j] = 8;   //mur sud sur case au dessus
             mat[i][j+1] = 4;   //mur ouest sur case a droite
        }
        else if (i != 0 && j+1 == COLONNES)    //derniere colonne sans la premiere case
        {
            mat[i][j-1] = 1;    //mur est sur case a gauche
            mat[i-1][j] = 8;    //mur sud sur case au dessus
        }
        else if (i > 0 && j+1 < COLONNES)
        {
            ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_suiv);
            ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_dessus);
        }   
    }
}