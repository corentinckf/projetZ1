#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Affichage d'une texture sur la totalité de la fenêtre
void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,SDL_Renderer *renderer) 
{
    SDL_Rect 
            source = {0},                         // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                 // Création de l'élément à afficher
    SDL_RenderPresent(renderer);                  // Affichage
    SDL_Delay(2000);                              // Pause en ms

    SDL_RenderClear(renderer);                    // Effacer la fenêtre
}

void move_texture(SDL_Texture* my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect 
        source = {0},                             // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(                                
      window, &window_dimensions.w,                 
      &window_dimensions.h);                      // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,         
                   &source.w,&source.h);

    int colonnes=9,lignes=3;
    float zoom=2;
    int offset_x = source.w/colonnes;
    int offset_y = source.h/lignes;

    state.x = 0 ;                          // La première vignette est en début de ligne
    state.y = 0;                            // On s'intéresse à la 4ème ligne, le bonhomme qui court
    state.w = offset_x;                    // Largeur de la vignette
    state.h = offset_y;                    // Hauteur de la vignette

    destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran
    destination.y = (window_dimensions.h - destination.h) /2;
    destination.x = (window_dimensions.w - destination.w) /2;

    int x=0,y=0;

    for (y=0;y<source.h;y+=offset_y)
    {
        state.y=y;
        for (x=0;x<source.w:x+=offset_x)
        {
            state.x=x;
        }
        SDL_RenderClear(renderer);
        SDL_SetTextureAlphaMod(my_texture,(1.0-1.0*i/nb_it)*255);      // L'opacité va passer de 255 à 0 au fil de l'animation
        SDL_RenderCopy(renderer, my_texture, &source, &destination);   // Préparation de l'affichage
        SDL_RenderPresent(renderer);                  // Affichage de la nouvelle image
        SDL_Delay(30);                                // Pause en ms
    }                                                 
    SDL_RenderClear(renderer);
    }
}

int main()
{
    SDL_Texture *my_texture;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 600,
                            600,
                            SDL_WINDOW_OPENGL);
    if (window == NULL) fprintf(stderr,"erreur lors de l'ouverture de la fenêtre");

    renderer = SDL_CreateRenderer(
                window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) fprintf(stderr,"erreur lors de l'ouverture du rendu\n");

    SDL_SetRenderDrawColor(renderer,0,0,0,255);  

    my_texture = IMG_LoadTexture(renderer,"./secsample.png");
    if (my_texture == NULL) 
    {
        //end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
        fprintf(stderr,"erreur lors de l'ouverture de la texture\n");
    }

    //play_with_texture_1(my_texture,window,renderer);
    move_texture(my_texture,window,renderer);

    SDL_DestroyTexture(my_texture);
    IMG_Quit(); 
}