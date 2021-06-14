#include <SDL2/SDL.h>
#include <stdio.h>

int main()
{
    SDL_Window *window = NULL;
    int i=0;

    if (SDL_Init(SDL_Init_Video) != 0)
    {
        printf(stderr,"erreur lors de l'ouverture de SDL");
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
        "Fenêtre à gauche",
        0,0,
        400,300,
        SDL_WINDOW_RESIZABLE);
    
    if (window == NULL)
    {
        printf(stderr,"erreur lors de l'ouverture de la fenêtre");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Delay(2000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}