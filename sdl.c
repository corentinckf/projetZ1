#include <SDL2/SDL.h>
#include <stdio.h>

int main()
{

    SDL_Window *window_1 = NULL;
    SDL_Window *window_2 = NULL;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }
}