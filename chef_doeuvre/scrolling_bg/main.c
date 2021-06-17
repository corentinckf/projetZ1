#include "util_sdl.h"

#define LARGEUR_FENETRE 300
#define HAUTEUR_FENETRE 300
#define NOM_FENETRE "Fenêtre"

typedef struct background
{
    SDL_Texture * sprite;
    int cordx,cordy;
} background_t;


background_t * backgroundList(const char * file_name, SDL_Window * window, SDL_Renderer * renderer)
{
    background_t * list[3];
    for(int i = 0; i < 3;++i)
    {
        list[i]->sprite = load_texture_from_image(file_name, window, renderer);
        list[i]->cordx = 0;
        list[i]->cordy = 0;
    }
    return list;
}


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

    /*Loading texture*/
    //SDL_Texture * bglist = initBgList("bg.png", window, renderer);
    SDL_Texture * bg = load_texture_from_image("bg.png", window, renderer);
    SDL_Texture * bg2 = load_texture_from_image("bg.png", window, renderer);
    SDL_bool
        program_on = SDL_TRUE, // Booléen pour dire que le programme doit continuer
        paused = 1;            // Booléen pour dire que le programme est en pause
    int cordy_bg = 0, cordy_bg2 = 0;
    while (program_on)
    {                    // La boucle des évènements
        SDL_Event event; // Evènement à traiter

        while (program_on && SDL_PollEvent(&event))
        { // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
            // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_q:                // 'q'
                    program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                    break;
                case SDLK_p:          // 'p'
                    paused = !paused; // basculement pause/unpause
                    break;
                case SDLK_SPACE:      // 'SPC'
                    paused = !paused; // basculement pause/unpause
                    break;
                case SDLK_KP_PLUS: // '+'

                    break;
                case SDLK_KP_MINUS: // '-'
                    break;
                default:
                    break;
                }
            case SDL_MOUSEBUTTONDOWN: // Click souris
                break;
            default:
                break;
            }
        }


        SDL_Rect
            source = {0},            // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        SDL_GetWindowSize(window, &window_dimensions.w, & window_dimensions.h);
        SDL_QueryTexture(bg,NULL,NULL,&source.w, &source.h);

        destination.h = source.h;
        destination.w = source.w;
        
        destination.x = 0;
        
        if(destination.y >= window_dimensions.h)
        {
            destination.y = 0;
            
        }else
        {
            cordy_bg += 2;
            destination.y += cordy_bg;
            
        }
        SDL_RenderCopy(renderer, bg, &source, &destination);

        printf("\n dépassé de : %d", destination.y - window_dimensions.h);

        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Petite pause
    
    }
    
    end_sdl(1,"Normal ending", window, renderer, &code_retour_sdl);

    if(code_retour_sdl == -1) exit(EXIT_FAILURE);

    return 0;
}