#include "util_sdl.h"

#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 400
#define NOM_FENETRE "Animation texture Corentin"

int main(int argc, char **argv)
{
    int code_retour_sdl;
    int fait = 0;
    SDL_Window * window = initWindow(LARGEUR_FENETRE,
                                     HAUTEUR_FENETRE,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     NOM_FENETRE);
    SDL_Renderer * renderer;
    SDL_DisplayMode screen;

    SDL_GetCurrentDisplayMode(0, &screen);
    
    if(window == NULL) end_sdl(0,
     "ERROR WINDOW CREATION",
     window,
     renderer,
     &code_retour_sdl
    );

    renderer = SDL_CreateRenderer(
           window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL)
    end_sdl(0,
     "ERROR RENDERER CREATION",
     window,
     renderer,
     &code_retour_sdl
    );

    /*Load texture*/
    SDL_Texture * sun = load_texture_from_image("../../exemples_executables/img/sun.png", window, renderer);
    SDL_Texture * ken = load_texture_from_image("../../exemples_executables/img/player-spritemap-v9.png", window, renderer);
    SDL_Texture * bg = load_texture_from_image("../../exemples_executables/img/nasa-xFO2Xt33xgI-unsplash.jpg", window, renderer);

    while (!fait)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {   
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
                fait = 1;
        }

    }
    end_sdl(1,"Normal ending", window, renderer, &code_retour_sdl);
    IMG_Quit();
    if(code_retour_sdl == -1) exit(EXIT_FAILURE);

    return 0;
}