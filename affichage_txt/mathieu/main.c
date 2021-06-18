#include "util_sdl.h"

#define PATH_FONT "/home/local.isima.fr/mavilledie4/shared/projetZ1/exemples_executables/fonts/Pacifico.ttf"
#define TAILLE_FONT 65

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

    /************** creation window ****************/
    window = SDL_CreateWindow(
        "Jeu de la Vie",
        (screen.w - LARGEUR_FENETRE) / 2, (screen.h - HAUTEUR_FENETRE) / 2,
        LARGEUR_FENETRE, HAUTEUR_FENETRE,
        0);

    if (window == NULL)
        if (end_sdl(0, "ERROR WINDOW CREATION", window, renderer) == -1)
            return EXIT_FAILURE;

    /************** creation renderer ****************/
    renderer = SDL_CreateRenderer(
        window, -1,
        0);
    if (renderer == NULL)
        if (end_sdl(0, "ERROR RENDERER CREATION", window, renderer) == -1)
            return EXIT_FAILURE;

    if (TTF_Init() < 0)
        if (end_sdl(0, "Couldn't initialize SDL TTF", window, renderer) == -1)
            return EXIT_FAILURE;

    /******* fin initialisation de la sdl *************/
    TTF_Font *font = NULL;                       // la variable 'police de caractère'
    font = TTF_OpenFont(PATH_FONT, TAILLE_FONT); // La police à charger, la taille désirée
    if (font == NULL)
        if (end_sdl(0, "Can't load font", window, renderer) == -1)
            return EXIT_FAILURE;

    TTF_SetFontStyle(font, TTF_STYLE_ITALIC ); // en italique, gras

    SDL_Color color = {250, 250, 250, 255}; // la couleur du texte

    SDL_Surface *text_surface = NULL;                                    // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, "Hello World !", color); // création du texte dans la surface
    if (text_surface == NULL)
        if (end_sdl(0, "Can't create text surface", window, renderer) == -1)
            return EXIT_FAILURE;

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
        end_sdl(0, "Can't create texture from surface", window, renderer);

    SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

    SDL_Rect pos = {0, 0, 0, 0};                                // rectangle où le texte va être positionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte

    SDL_GetWindowSize(window, &pos.x, &pos.y);
    pos.x = (pos.x - pos.w) / 2;
    pos.y = (pos.y - pos.h) / 2;
    SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture);                   // On n'a plus besoin de la texture avec le texte

    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_DestroyTexture(text_texture);
    TTF_Quit();
    end_sdl(1, "fermeture ok", window, renderer);
    return 0;
}