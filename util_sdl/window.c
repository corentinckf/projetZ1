#include "window.h"

SDL_Window * initWindow(int width, int height,int x_pos, int y_pos, char * window_name)
{
    SDL_Window * window;

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
        window_name,                       // window title
        x_pos,                             // initial x position
        y_pos,                             // initial y position
        width,                               // width, in pixels
        height,                               // height, in pixels
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Error : Window initialisation - %s\n", SDL_GetError());
        window = NULL;
    }

    return window;

}