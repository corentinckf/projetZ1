#include "util_sdl.h"

SDL_Window *initWindow(int width, int height, int x_pos, int y_pos, char *window_name)
{
    SDL_Window *window;

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
        window_name, // window title
        x_pos,       // initial x position
        y_pos,       // initial y position
        width,       // width, in pixels
        height,      // height, in pixels
        SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        printf("Error : Window initialisation - %s\n", SDL_GetError());
        window = NULL;
    }

    return window;
}

int end_sdl(char ok,            // fin anormale : ok = 0 ; normale ok = 1
            char const *msg,    // message à afficher
            SDL_Window *window, // fenêtre à fermer
            SDL_Renderer *renderer)
{ // renderer à fermer
    char msg_formated[255];
    int l;
    int code_retour = 0;
    if (!ok)
    {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);

    SDL_Quit();

    if (!ok)
    {
        code_retour = -1; //exit(EXIT_FAILURE)  après
    }
    return code_retour;
}
