#include "animation_simple.h"

int main()
{
    int i;
    int x_perso = 10;
    int y_perso = 80;
    int map[HAUTEUR_MATRICE][LARGEUR_MATRICE];
    int couleurs[6][3] = {{135, 206, 235},
                          {255, 0, 0},
                          {0, 0, 255},
                          {245, 245, 220},
                          {0, 0, 0},
                          {250, 250, 0}};

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

    /**************On dessine dans le renderer *************/
    init_map(map);
    for (i = 0; i < 20; ++i)
    {
        x_perso += 1 ;
        y_perso -= 1 +  (-1)*(i % 2);
        placement_perso(map, x_perso, y_perso);
        draw(renderer, map, couleurs); // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);   // affichage
        SDL_RenderClear(renderer);
        effacement_perso(map, x_perso, y_perso);
        SDL_Delay(200);
    } /******************************************************/

    SDL_Delay(2000);

    end_sdl(0, "Fin normal", fenetre, renderer);
    return EXIT_SUCCESS;
}

void draw(SDL_Renderer *renderer, int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int couleurs[10][3])
{
    int i, j, c;
    SDL_Rect rect;
    for (i = 0; i < HAUTEUR_MATRICE; i++)
    {
        for (j = 0; j < LARGEUR_MATRICE; j++)
        {
            c = map[i][j];
            SDL_SetRenderDrawColor(renderer, couleurs[c][0], couleurs[c][1], couleurs[c][2], 255);
            rect.x = j * TAILLE_PIXEL;
            rect.y = i * TAILLE_PIXEL;
            rect.w = 1 * TAILLE_PIXEL;
            rect.h = 1 * TAILLE_PIXEL;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void init_map(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE])
{
    int i, j;
    for (i = 0; i < HAUTEUR_MATRICE; i++)
        for (j = 0; j < LARGEUR_MATRICE; j++)
            map[i][j] = 0;
}

void placement_perso(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int x_perso, int y_perso)
{
    int i, j;
    int x = x_perso;
    int y = y_perso;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 4; j++)
        {
            y = y_perso - i;
            x = x_perso + j;
            printf("x=%d; y=%d\n", x, y);
            map[y][x] = dessine_perso(i, j);
        }
    }
}
void effacement_perso(int map[HAUTEUR_MATRICE][LARGEUR_MATRICE], int x_perso, int y_perso)
{
    int i, j;
    int x = x_perso;
    int y = y_perso;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 4; j++)
        {
            y = y_perso - i;
            x = x_perso + j;
            map[y][x] = 0;
        }
    }
}
int dessine_perso(int i, int j)
{
    int partie_perso;
    if (j >= 1 && j <= 2)
    {
        if (i >= 0 && i <= 3)
        {
            partie_perso = 1; //jambes
        }
        else if (i == 4)
        {
            partie_perso = 5; //ceinture
        }
        else if (i >= 5 && i <= 7)
        {
            partie_perso = 2; //t-shirt
        }
        else if (i == 8)
        {
            partie_perso = 3; //tete
        }
        else if (i == 9)
        {
            partie_perso = 4;
        }
    }
    else if (j == 0 || j == 3)
    {
        if (i >= 4 && i <= 7)
        {
            partie_perso = 3; //bras
        }
        else
        {
            partie_perso = 0;
        }
    }
    return partie_perso;
}

/*
*
*/
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
