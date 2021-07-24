#ifndef __UI_H__
#define __UI_H__

#include "const.h"

char *texte_score(int a);
void affichage_texte(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font,
                     char *texte, float taille, int x, int y,
                     int r, int g, int b, int a);
void ecran_fin(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, int coll);
void ecran_debut(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);
void affichage_effet(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *my_texture, enum effet type_effet, int position, int delta, int anim);
void gestion_affichage_effet(SDL_Window *window, SDL_Renderer *renderer, enum effet type_effet, int position, int delta);

void affichage_ecran(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font,
                     int delta, int anim, entite_t *perso,
                     entite_t *liste_boule[NB_BOULES], int *nb_boules,
                     bombe_t *liste_bombes[NB_BOMBES], int *nb_bombes,
                     SDL_Texture *texture_mur, int map[NB_LIGNE_LABY][NB_COLONNE_LABY]);

void affichage_score(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font,
                     entite_t *perso, entite_t *liste_boules[NB_BOULES], bombe_t*liste_bombes[NB_BOMBES]);

void affichage_score_entite(SDL_Window *window, SDL_Renderer *renderer,
                            enum type_objet type, int x_pos, int y_pos);


#endif
