#include "window.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Window * initWindow(int width, int height, char * window_name)
{
    SDL_Window * window;

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
        window_name,                       // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Error : Window initialisation - %s\n", SDL_GetError());
        window = NULL;
    }

    return window;

}