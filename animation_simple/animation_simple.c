#include "animation_simple.h"

int main()
{
    int x_perso = 50;
    int y_perso = 80;
    int map[HAUTEUR_MATRICE][LARGEUR_MATRICE];
    int couleurs[6][3] = {{135, 206, 235},
                          {255, 0, 0},
                          {0, 0, 255},
                          {245, 245, 220},
                          {0, 0, 0},
                          {250, 250, 210}};

    //ciel 0    //tete 3
    //jambe 1   //cheveux 4
    //tshirt 2  //ceinture 5

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
        0);

    if (fenetre == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", fenetre, renderer);

    /************** creation renderer ****************/
    renderer = SDL_CreateRenderer(
        fenetre, -1,
        0);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", fenetre, renderer);

    init_map(map);

    placement_perso(map, x_perso, y_perso);

    /**************On dessine dans le renderer *************/
    draw(renderer, map, couleurs); // appel de la fonction qui crée l'image
    SDL_RenderPresent(renderer);   // affichage
    /*SDL_RenderClear(renderer);*/
    /******************************************************/
    printf("fin affichage\n");
    SDL_Delay(5000);

    end_sdl(0, "Fin normal", fenetre, renderer);
    return EXIT_SUCCESS;
}

void end_sdl(char ok,            // fin anormale : ok = 0 ; normale ok = 1
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

void draw(SDL_Renderer *renderer, int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int couleurs[10][3])
{
    SDL_Rect rect;
    int k, i, c;
    for (k = 0; k < HAUTEUR_MATRICE; k++)
    {
        for (i = 0; i < LARGEUR_MATRICE; i++)
        {
            c = map[k][i];
            printf("c=%d\n", c);
            if (c >= 0 && c < 6)
            {
                SDL_SetRenderDrawColor(renderer, couleurs[c][0], couleurs[c][1], couleurs[c][2], 255);
                rect.x = LARGEUR_PIXEL * k;
                rect.y = HAUTEUR_PIXEL * i;
                rect.w = LARGEUR_PIXEL;
                rect.h = HAUTEUR_PIXEL;
                if (rect.y >= 0 && rect.y < HAUTEUR_FENETRE)
                    if (rect.x >= 0 && rect.x < LARGEUR_FENETRE)
                        SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void init_map(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE])
{
    int i, j;

    for (i = 0; i < HAUTEUR_MATRICE; i++)
    {
        for (j = 0; j < LARGEUR_MATRICE; j++)
        {
            map[i][j] = 0;
        }
    }
}



void placement_perso(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int x_pos, int y_pos)
{
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 4; j++)
        {
            y_pos = y_pos - i;
            x_pos = x_pos + j;
            if (y_pos >= 0 && y_pos < HAUTEUR_MATRICE)
                if (x_pos >= 0 && x_pos < LARGEUR_MATRICE)
                    map[x_pos][y_pos] = 5;
        }
    }
}

int dessine_perso(int i, int j)
{
    int partie_perso;
    if (j >= 1 && j <= 2)
    {
        if (i >= 0 && i <= 2)
        {
            partie_perso = 1; //jambes
        }
        else if (i >= 4 && i <= 7)
        {
            partie_perso = 2; //t-shirt
        }
        else if (i == 8)
        {
            partie_perso = 3; //tete
        }
        else if (i == 9)
        {
            partie_perso = 4; //cheveux
        }
        else if (i == 3)
        {
            partie_perso = 5; //ceinture
        }
    }
    else if (j == 3 || j == 0)
    {
        if (i >= 4 && i <= 7)
        {
            partie_perso = 1; //bras
        }
    }
    else
    {
        partie_perso = 0; //ciel
    }
    if (j == 0 && i == 9)
        partie_perso = 4; //casquette
    return partie_perso;
}