#ifndef __UTIL_SDL_H__
#define __UTIL_SDL_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

SDL_Window * initWindow(int , int, int, int, char *);
void end_sdl(char,char const *, SDL_Window*, SDL_Renderer*, int *);
int test_fenetre(SDL_Window *fenetre);
#endif