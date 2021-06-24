#include "gestion_bombes.h"

void creer_bombe(SDL_Window *window, SDL_Renderer *renderer, int pos_cour, int rayon_action, int temps, bombe_t **pbombe, char *chemin)
{
    *pbombe = (bombe_t *)malloc(sizeof(bombe_t));
    if (*pbombe)
    {
        (*pbombe)->pos_cour = pos_cour;
        (*pbombe)->rayon_action = rayon_action;
        (*pbombe)->temps = temps;
        charger_texture(window, renderer, *pbombe, chemin);
    }
}

void charger_texture(SDL_Window *window, SDL_Renderer *renderer, bombe_t *bombe, char *chemin)
{
    SDL_Texture *my_texture = NULL;
    my_texture = IMG_LoadTexture(renderer, chemin);
    if (my_texture == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    bombe->texture = my_texture;
}

void liberer_bombe(bombe_t *bombe)
{
    free(bombe);
    bombe = NULL;
    SDL_DestroyTexture(bombe->texture);
}

void explosion(bombe_t *bombe, entite_t *perso, entite_t *tab_boule[NB_BOULES], int map[NB_LIGNE_LABY][NB_COLONNE_LABY])
{
    int rayon_action = bombe->rayon_action;

    for (int k=0;k<rayon_action;k++)
    {
        int position = bombe->pos_cour;
        int i = position / NB_COLONNE_LABY;
        int j = position % NB_COLONNE_LABY;
        unsigned mur = (unsigned)map[i][j];
        if (mur && mur_est)
        {
            collision(perso, tab_boule, map,i-1,j);
            collision(perso, tab_boule, map,i+1,j);
            collision(perso, tab_boule, map,i,j-1);
        }

        if (mur && (unsigned)mur_ouest)
        {
            collision(perso, tab_boule, map,i-1,j);
            collision(perso, tab_boule, map,i+1,j);
            collision(perso, tab_boule, map,i,j+1);
        }

        if (mur && (unsigned)mur_nord)
        {
            collision(perso, tab_boule, map,i+1,j);
            collision(perso, tab_boule, map,i,j+1);
            collision(perso, tab_boule, map,i,j-1);
        }
        if (mur && (unsigned)mur_sud)
        {
            collision(perso, tab_boule, map,i-1,j);
            collision(perso, tab_boule, map,i,j+1);
            collision(perso, tab_boule, map,i,j-1);
        }
    }
}
    

int collision_bombe(entite_t *perso, entite_t *tab_boule[NB_BOULES], int map[NB_LIGNE_LABY][NB_COLONNE_LABY],int i, int j)
{
    int erreur = 0;
    int position_perso = perso->pos_cour;
    int ligne_perso = position_perso / NB_COLONNE_LABY;
    int colonne_perso = position_perso % NB_COLONNE_LABY;

    if (map[ligne_perso][colonne_perso] == map[i][j])
    {
        //le perso saute !
        erreur = 1;
    }

    int k=0;
    while (k < NB_BOULES && tab_boule[k] != NULL])
    {
        entite_t *boule = tab_boule[k];
        int position_boule = boule->pos_cour;
        int ligne_boule = position_boule / NB_COLONNE_LABY;
        int colonne_boule = position_boule % NB_COLONNE_LABY;

        if (map[ligne_boule][colonne_boule] == map[i][j])
        {
            //supprimer la bombe
            liberer_entite(boule);
        }
        k++;
    }
    return erreur;  //0 : pas d'erreur ; 1 : tuer le perso
}