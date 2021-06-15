#include "util_sdl.h"

#define LARGEUR_FENETRE 400
#define HAUTEUR_FENETRE 300
#define NOM_FENETRE "Fenêtre"
/*srand(time(NULL));*/

void draw(SDL_Renderer * renderer)
{
    SDL_Rect rectangles[10];
    for(int i = 0; i < 10;++i)
    {
        SDL_SetRenderDrawColor(renderer,                                
                              rand() % 256, rand() % 256, rand() % 256,                               // mode Red, Green, Blue (tous dans 0..255)
                              255); 
        rectangles[i].x += (rand() % LARGEUR_FENETRE+1);
        rectangles[i].y += (rand() % HAUTEUR_FENETRE+1);
        rectangles[i].w = rand() % 101;
        rectangles[i].h = rand() % 101;
        SDL_RenderFillRect(renderer, &rectangles[i]);
        SDL_Delay(50);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

int main(int argc, char **argv)
{
    int code_retour_sdl;
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

    if(renderer == NULL) end_sdl(0,
     "ERROR RENDERER CREATION",
     window,
     renderer,
     &code_retour_sdl
    );

    char c;
    
    while(1){
        draw(renderer);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    end_sdl(1,"Normal ending", window, renderer, &code_retour_sdl);

    if(code_retour_sdl == -1) exit(EXIT_FAILURE);

    return 0;
}