#ifndef __MAIN_H__
#define __MAIN_H__
#include "util_sdl.h"

#define IMG_BACKGROUND "./img/nasa-xFO2Xt33xgI-unsplash.jpg"
#define IMG_TROU_NOIR "./img/trou-noir.png"
#define IMG_SPRITE "./img/player-spritemap-v9.png"
#define IMG_SUN "./img/sun.png"
#define IMG_SHADOW "./img/shadow-80x70.png"

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 800
#define NOM_FENETRE "Fenêtre"

#define LARGEUR_MATRICE 100
#define HAUTEUR_MATRICE 80

#define TAILLE_PIXEL 10

void play_texture_full_window(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_texture_xy(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_texture_anime(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_texture_sprite_courir(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_texture_sprite_avec_bg(SDL_Texture *bg_texture, SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_texture_xy_taille(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, float taille);

void animation(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *bg_texture, SDL_Texture *trou_noir, SDL_Texture *sprite);
#endif



