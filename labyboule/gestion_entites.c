#include "gestion_entites.h"

void creer_entite(SDL_Window *window, SDL_Renderer *renderer, int pos_prec, int pos_cour, int vitesse, int vertical, int horizontal, entite_t **pentite, char *chemin)
{
    *pentite = (entite_t *)malloc(sizeof(entite_t));
    if (*pentite)
    {
        (*pentite)->pos_prec = pos_prec;
        (*pentite)->pos_cour = pos_cour;
        (*pentite)->vitesse = vitesse;
        (*pentite)->vertical = vertical;
        (*pentite)->horizontal = horizontal;
        charger_texture(window, renderer, *pentite, chemin);
    }
}

void charger_texture(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, char *chemin)
{
    SDL_Texture *my_texture = NULL;
    my_texture = IMG_LoadTexture(renderer, chemin);
    if (my_texture == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    entite->texture = my_texture;
}

void liberer(entite_t *entite)
{
    free(entite);
    entite = NULL;
}

//retourne 0 si pas de collision
int collision(entite_t *perso, entite_t *liste_boule[NB_BOULES])
{
    int res = 0;
    for (int k = 0; k < NB_BOULES; ++k)
    {
        res = res || (perso->pos_cour == liste_boule[k]->pos_cour);
    }
    return res;
}