#include <SDL2/SDL.h>
#include <stdio.h>

int main()
{
    SDL_Window *window = NULL;
    int largeur=0, hauteur=0;
    int i=0,j=0;
    int aux;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf(stderr,"erreur lors de l'ouverture de SDL");
        exit(EXIT_FAILURE);
    }
    for (i=0;i<3;i++)
    {
        window = SDL_CreateWindow(
            "Fenêtre à gauche",
            largeur,hauteur,
            400,200,
            SDL_WINDOW_RESIZABLE);
        
        if (window == NULL)
        {
            printf(stderr,"erreur lors de l'ouverture de la fenêtre");
            SDL_Quit();
            exit(EXIT_FAILURE);
        }

        largeur+=400;
        hauteur+=200;
        SDL_Delay(1000);
    }
    aux=largeur;
    sauv=hauteur-2*200;
    largeur-=400;
    for (j=0;j<2;j++)
    {
        window = SDL_CreateWindow(
            "Fenêtre à gauche",
            largeur,hauteur,
            400,200,
            SDL_WINDOW_RESIZABLE);
        
        if (window == NULL)
        {
            printf(stderr,"erreur lors de l'ouverture de la fenêtre");
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
        hauteur+=200;
        SDL_Delay(1000);
    }
    
    largeur=aux;
    hauteur=sauv;
    for (i=0;i<2;i++)
    {
        window = SDL_CreateWindow(
            "Fenêtre à gauche",
            largeur,hauteur,
            400,200,
            SDL_WINDOW_RESIZABLE);
        
        if (window == NULL)
        {
            printf(stderr,"erreur lors de l'ouverture de la fenêtre");
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
        largeur+=400;
        hauteur-=200;
        SDL_Delay(1000);
    }

    SDL_Delay(3000);
    for (j=7;j>0;j--)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}