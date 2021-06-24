#include "perso.h"

int main(int argc, char *argv[])
{
    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int input_h = atoi(argv[1]), input_v = atoi(argv[2]), debut = atoi(argv[3]), fin = atoi(argv[4]);

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    window = SDL_CreateWindow("Test animation personnage",
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
    SDL_Texture *sprite;

    sprite = IMG_LoadTexture(renderer, PATH_IMG_PERSO);
    if (sprite == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    //animation
    affichage_entite(window, renderer, sprite, &input_h, &input_v, &debut, &fin);

    SDL_RenderClear(renderer);

    IMG_Quit();
    end_sdl(1, "Fermeture SDL normale", window, renderer);
    return 0;
}

void affichage_entite(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *sprite,
                      int *input_h, int *input_v, int *deb, int *fin)
{
    float taille = 0.01;
    int idle = 0;

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

    int nb_images = 4;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 2;                      // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h / 4;         // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

    state.x = 0;
    state.w = offset_x;
    state.h = offset_y;
    if (*input_h == 0 && *input_v == 0)
        idle = 1;
    else
        idle = 0;

    if (*input_h == 1)
        state.y = 1 * offset_y;
    else if (*input_h == -1)
        state.y = 0 * offset_y;

    if (*input_v == 1)
        state.y = 2 * offset_y;
    else if (*input_v == -1)
        state.y = 3 * offset_y;

    destination.w = offset_x * zoom; // Largeur du sprite à l'écran
    destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

    destination.y = 0.1 * window_dimensions.h; // La course se fait en milieu d'écran (en vertical)

    for (int t = 0; t < 10; t++)
    {
        if (!idle)
        {
            state.x += offset_x;
            state.x %= source.w;
        }
        else
        {
            state.y = 0;
            state.x = 0;
        }

        time_t ancienTime = time();
        time_t deltaTime = ancienTime - time();
        time_t tempTime += deltaTime;
        destination.x += deb * destination.w + (tempTime);

        SDL_RenderCopy(renderer, sprite, &state, &destination);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
}

int end_sdl(char ok,            // fin anormale : ok = 0 ; normale ok = 1
            char const *msg,    // message à afficher
            SDL_Window *window, // fenêtre à fermer
            SDL_Renderer *renderer)
{ // renderer à fermer
    char msg_formated[255];
    int l;
    int code_retour = 0;
    if (!ok)
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
        code_retour = -1; //exit(EXIT_FAILURE)  après
    }
    return code_retour;
}
