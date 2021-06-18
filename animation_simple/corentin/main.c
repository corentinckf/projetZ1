#include "util_sdl.h"

#define LARGEUR_FENETRE 400
#define HAUTEUR_FENETRE 300
#define NOM_FENETRE "Fenêtre"


SDL_Rect initRect(SDL_Renderer * renderer, int x,int y, int w, int h)
{
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer,                                
                              0,0,0,      
                              255);                                 
    SDL_RenderFillRect(renderer, &rect);

    return rect;
}

void updateRect(SDL_Rect rect,int * speed, int * r, int * g, int * b)
{
    //update de la vitesse
    if(rect.x <= 2 *(LARGEUR_FENETRE - rect.w))
        *speed += 10;
    else
        *speed -= 10;
    //update de la couleur
    srand(time(NULL));
    *r = rand() % 256;
    *g = rand() % 256;
    *b = rand() % 256;
}

void drawRect(SDL_Renderer * renderer,SDL_Rect rect,int * speed, int * r, int * g, int * b)
{
        rect.x += *speed;
        rect.y += *speed;
    SDL_SetRenderDrawColor(renderer,                                
                              *r,*g,*b,      
                              255);                                 
    SDL_RenderFillRect(renderer, &rect);

}

int main(int argc, char **argv)
{
    int code_retour_sdl;
    int fait = 0;
    int r = 200, g = 200, b = 200, speed = 10;
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

    SDL_Rect rect = initRect(renderer,0,0,20,20);

    while (!fait)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {   
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
                fait = 1;

        }
        
        updateRect(rect,&speed,&r,&g,&b);
        drawRect(renderer,rect,&speed,&r,&g,&b);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);

    }
    end_sdl(1,"Normal ending", window, renderer, &code_retour_sdl);

    if(code_retour_sdl == -1) exit(EXIT_FAILURE);

    return 0;
}