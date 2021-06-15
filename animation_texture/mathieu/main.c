#include "main.h"

int main()
{

    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    /************** initialisation window ****************/
    window = SDL_CreateWindow("Jeu de la Vie",
                              (screen.w - LARGEUR_FENETRE) / 2, (screen.h - HAUTEUR_FENETRE) / 2,
                              LARGEUR_FENETRE, HAUTEUR_FENETRE,
                              0);

    if (window == NULL)
        if (end_sdl(0, "ERROR WINDOW CREATION", window, renderer) == -1)
            return EXIT_FAILURE;

    /************** initialisation renderer ****************/
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        if (end_sdl(0, "ERROR RENDERER CREATION", window, renderer) == -1)
            return EXIT_FAILURE;

    /**** chargement des texture *************/
    SDL_Texture *background;
    SDL_Texture *trou_noir;
    SDL_Texture *sprite;

    background = IMG_LoadTexture(renderer, IMG_BACKGROUND);
    if (background == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    trou_noir = IMG_LoadTexture(renderer, IMG_TROU_NOIR);
    if (background == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    sprite = IMG_LoadTexture(renderer, IMG_SPRITE);
    if (background == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    play_texture_full_window(background, window, renderer);
    SDL_RenderPresent(renderer); // affichage

    SDL_Delay(2000);
    SDL_RenderClear(renderer);

    IMG_Quit();
    end_sdl(1, "Fermeture SDL normale", window, renderer);
    return 0;
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
            partie_perso = 1; //jambes

        else if (i == 4)
            partie_perso = 5; //ceinture
        else if (i >= 5 && i <= 7)
            partie_perso = 2; //t-shirt
        else if (i == 8)
            partie_perso = 3; //tete
        else if (i == 9)
            partie_perso = 4;
    }
    else if (j == 0 || j == 3)
    {
        if (i >= 4 && i <= 7)
            partie_perso = 3; //bras
        else
            partie_perso = 0;
    }
    return partie_perso;
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

/*
void play_texture_xy(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
}

*/