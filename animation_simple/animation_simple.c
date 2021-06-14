#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 800

//gcc  animation_simple.c -o animation_simple -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{ // renderer à fermer
    char msg_formated[255];
    int l;

    if (ok)
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
        exit(EXIT_FAILURE);
    }
}


void draw(SDL_Renderer * renderer)
{

}








int main(int argc, char **argv)
{

    SDL_DisplayMode screen;

    SDL_Window *fenetre = NULL;
    SDL_Renderer *renderer = NULL;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    /************** creation fenetre ****************/
    fenetre = SDL_CreateWindow(
        "Animation Simple",
        (screen.w - LARGEUR_FENETRE) / 2, (screen.h - HAUTEUR_FENETRE) / 2,
        LARGEUR_FENETRE, HAUTEUR_FENETRE,
        SDL_WINDOW_RESIZABLE);

    if (fenetre == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", fenetre, renderer);

    /************** creation renderer ****************/
    renderer = SDL_CreateRenderer(
        fenetre, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", fenetre, renderer);

    /**************On dessine dans le renderer *************/

    draw(renderer);              // appel de la fonction qui crée l'image
    SDL_RenderPresent(renderer); // affichage
    SDL_Delay(1000);             // Pause exprimée en ms
    /******************************************************/



    end_sdl(0, "Fin normal", fenetre, renderer);
    return EXIT_SUCCESS;
}