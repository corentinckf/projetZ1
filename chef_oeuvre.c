#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define LIGNES 50
#define COLONNES 10

//gestion des items

void init(int grille[LIGNES][COLONNES])
{
    int i,j;

    for (i=0;i<LIGNES;i++)
    {
        for (j=0;j<COLONNES;j++)
        {
            grille[i][j] = 0;
        }
    }
}

void evolution(int grille[LIGNES][COLONNES],int *etape)
{
    int valeur = rand()%5;     //valeur entre 0 et 4
    int signe = 2 * rand()%2 - 1; //signe vaut -1 ou 1
    int j;

    for (j=0;j<COLONNES;j++)
    {
        grille[*etape][j] = valeur * signe;
    }
}

void draw(SDL_Renderer* renderer, int grille[LIGNES][COLONNES], SDL_Texture *planche, int *etape, int *hauteur_pixel, int *largeur_pixel)
{
    SDL_Rect 
             source = {0},
             destination = {0},
             state = {0};
    
    SDL_QueryTexture(planche,NULL, NULL, &source.w, &source.h);

    int offset_x = source.w / 4;
    int offset_y = source.h / 4;
    int i,j;
    int ligne = 0;

    float zoom = 0.5;
    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;

    state.w = offset_x;
    state.h = offset_y;
    
    for (i=0;i<LIGNES;i++)
    {
        //fprintf(stdout,"premier for\n");
        ligne = (*etape + i) % LIGNES;
        destination.x = i * (*hauteur_pixel);

        for (j=0;j<COLONNES;j++)
        {
            //fprintf(stdout,"deuxieme for\n");
            destination.y = j * (*largeur_pixel);
            switch (grille[ligne][j])
            {
                //fprintf(stdout,"valeur : %d\n", grille[ligne][j]);
                case 0:
                    //ne rien afficher : on voit le background
                    break;
                case -1:
                    state.x = 0;
                    state.y = 0;
                    break;
                case 1:
                    state.x = offset_x;
                    state.y = 0;
                    break;
                case -2:
                    state.x = 2 * offset_x;
                    state.y = 0;
                    break;
                case 2:
                    state.x = 3 * offset_x;
                    state.y = 0;
                    break;
                case -3:
                    state.x = 0;
                    state.y = offset_y;
                    break;
                case 3:
                    state.x = offset_x;
                    state.y = offset_y;
                    break;
                case -4:
                    state.x = 2 * offset_x;
                    state.y = offset_y;
                    break;
                case 4:
                    state.x = 3 * offset_x;
                    state.y = offset_y;
                    break;
                default:
                    fprintf(stdout,"valeur dans grille incoherente");
                    break;
            }
            SDL_RenderCopy(renderer,planche,&state,&destination);  
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
            //SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
        }
    }   
}

int main()
{
    int grille[LIGNES][COLONNES];
    int etape = 0;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Jeu de la vie",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED, 600,
                        600,
                        SDL_WINDOW_OPENGL);
    if (window == NULL) fprintf(stderr,"erreur lors de l'ouverture de la fenêtre");

    renderer = SDL_CreateRenderer(
                window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) fprintf(stderr,"erreur lors de l'ouverture du rendu\n");

    int hauteur_pixel = 600 / LIGNES;
    int largeur_pixel = 1000 / COLONNES;

    SDL_Texture *planche = NULL;

    planche = IMG_LoadTexture(renderer,"./exemples_executables/img2/buttons.png");
    if (planche == NULL) 
    {
        fprintf(stderr,"erreur lors de l'ouverture des boutons\n");
    }

    SDL_bool program_on = SDL_TRUE;

    init(grille);
    //fprintf(stdout,"grille initialisee\n");

    while (program_on)
    {
        SDL_Event event;

        while (program_on && SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
        //fprintf(stdout,"on rentre dans la boucle\n");
        draw(renderer,grille,planche,&etape,&hauteur_pixel,&largeur_pixel);
        //fprintf(stdout,"dessin fait\n");
        //evolution(grille,&etape);
        etape++;
    }
    SDL_DestroyTexture(planche);
    IMG_Quit();
}