#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Affichage d'une texture sur la totalité de la fenêtre
void affiche_texture(SDL_Texture *my_texture, SDL_Window *window,SDL_Renderer *renderer) 
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

void affiche_texture_1(SDL_Texture *my_texture, SDL_Window *window,SDL_Renderer *renderer) 
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
    SDL_RenderCopy(renderer, my_texture,&source,&destination); 
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
    SDL_QueryTexture(my_texture, NULL, NULL,&source.w,&source.h);

    int colonnes=9,lignes=3;
    int nb_images=colonnes*lignes-3;
    //float zoom=4;
    int offset_x = source.w/colonnes;
    int offset_y = source.h/lignes;

    int i=0,x=0,y=0;
    SDL_Rect state[24];

    for (y = 0; y < source.h - 1; y += offset_y)
    {
        for (x = 0; x < source.w; x += offset_x)
        {
            state[i].x = x;
            state[i].y = y;
            state[i].w = offset_x;
            state[i].h = offset_y;
            i++;
        }
    }
    //la derniere ligne est incomplete
    for (x = 0; x < source.w - 2*offset_x; x += offset_x)
    {
        state[i].x = x;
        state[i].y = y;
        state[i].w = offset_x;
        state[i].h = offset_y;
        i++;
    }

    int cpt=0;
    i=0;

    for (cpt = 0; cpt < nb_images; cpt++)
    {
        affiche_texture_1(my_texture, window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i ++;                  // Passage à l'image suivante
        SDL_RenderPresent(renderer);              // Affichage
        SDL_Delay(100);                           // Pause en ms
    }
    SDL_RenderClear(renderer);
}

int main()
{
    SDL_Texture *my_texture;
    SDL_Texture *my_image;
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

    my_texture = IMG_LoadTexture(renderer,"./supports/maps/secsample.png");
    if (my_texture == NULL) 
    {
        //end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
        fprintf(stderr,"erreur lors de l'ouverture de la texture\n");
    }

    my_image = IMG_LoadTexture(renderer,"./supports/PNG/Player/player_tilesheet.png");
    if (my_image == NULL) 
    {
        //end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
        fprintf(stderr,"erreur lors de l'ouverture de l'image\n");
    }

    //affiche_texture(my_texture,window,renderer);
    move_texture(my_image,window,renderer);

    SDL_DestroyTexture(my_texture);
    IMG_Quit(); 
}