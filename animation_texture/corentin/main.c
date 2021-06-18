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
    SDL_Texture * sun = load_texture_from_image("/img/sun.png", window, renderer);
    SDL_Texture * ken = load_texture_from_image("img/player-spritemap-v9.png", window, renderer);
    SDL_Texture * trou_noir = load_texture_from_image("img/trou-noir.png", window, renderer);
    SDL_Texture * bg = load_texture_from_image("malik-shibly--ZcQQ7gUj6Y-unsplash.jpg", window, renderer);

    //draw_texture(bg,window,renderer,0.125,0,0);
    animation(window, renderer,
               bg, trou_noir, ken);
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
void play_texture_full_window(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    destination = window_dimensions; //On fixe les dimension de l'affiche == a la taille de la window

    SDL_RenderCopy(renderer, my_texture, &source, &destination);
}

void play_texture_xy(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    float zoom = 0.125;

    destination.h = source.h * zoom;
    destination.w = source.w * zoom;

    destination.x = 0;
    destination.y = 0;
    SDL_RenderCopy(renderer, my_texture, &source, &destination);
}

void play_texture_xy_taille(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, float taille)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    destination.h = source.h * taille;
    destination.w = source.w * taille;

    destination.x = (0.25 * window_dimensions.w - destination.w) / 2;
    destination.y = (0.75 * window_dimensions.h - destination.h) / 2;
    SDL_RenderCopy(renderer, my_texture, &source, &destination);
}

void animation(SDL_Window *window, SDL_Renderer *renderer,
               SDL_Texture *bg_texture, SDL_Texture *trou_noir, SDL_Texture *sprite)
{

    float taille = 0.01;

    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions.w,
                      &window_dimensions.h);
    SDL_QueryTexture(sprite, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source.w, &source.h);
    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    int nb_images = 8;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 2;                      // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h / 4;         // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

    state.x = 0;            // La première vignette est en début de ligne
    state.y = 3 * offset_y; // On s'intéresse à la 4ème ligne, le bonhomme qui court
    state.w = offset_x;     // Largeur de la vignette
    state.h = offset_y;     // Hauteur de la vignette

    destination.w = offset_x * zoom; // Largeur du sprite à l'écran
    destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

    destination.y = 0.1 * window_dimensions.h; // La course se fait en milieu d'écran (en vertical)
    destination.x = 0;

    for (int t = 0; t < 110; t++)
    {
        play_texture_full_window(bg_texture, window, renderer);
        play_texture_xy(trou_noir, window, renderer);

        if (destination.y < 0.5 * window_dimensions.h)
        {
            destination.y += t;
            state.x = 1;
            state.y = 2 * offset_y;
            SDL_RenderCopy(renderer, sprite, &state, &destination);
        }
        else
        {
            destination.x += t; // Position en x pour l'affichage du sprite
            state.x += offset_x; // On passe à la vignette suivante dans l'image
            state.x %= source.w; // La vignette qui suit celle de fin de ligne est
            state.y = 3 * offset_y;
            SDL_RenderCopy(renderer, sprite, &state, &destination);
            
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(60);
    }
}