#ifndef __ANIMATION_SIMPLE__
#define __ANIMATION_SIMPLE__

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
void draw(SDL_Renderer *renderer, int x_pos, int y_pos);
void affichage_perso(SDL_Renderer *renderer, int x_pos, int y_pos);

#endif