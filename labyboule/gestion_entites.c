#include "gestion_entites.h"

void creer_entite(SDL_Window *window, SDL_Renderer *renderer, int pos_prec, int pos_cour, int vitesse, int vertical, int horizontal, entite_t *entite, char *chemin)
{
    entite->pos_prec = pos_prec;
    entite->pos_cour = pos_cour; 
    entite->vitesse = vitesse;
    entite->vertical = vertical;
    entite->horizontal = horizontal;
    charger_texture(window,renderer,entite,chemin);
}

void charger_texture(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, char *chemin)
{
    SDL_Texture* my_texture = NULL;
    my_texture = IMG_LoadTexture(renderer,chemin);
    if (my_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    entite->texture = my_texture;
}

void liberer(entite_t *entite)
{
    free(entite);
    entite = NULL;
}