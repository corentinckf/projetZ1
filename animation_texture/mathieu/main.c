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
    SDL_Texture *sun;

    background = IMG_LoadTexture(renderer, IMG_BACKGROUND);
    if (background == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    trou_noir = IMG_LoadTexture(renderer, IMG_TROU_NOIR);
    if (trou_noir == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    sprite = IMG_LoadTexture(renderer, IMG_SPRITE);
    if (sprite == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    sun = IMG_LoadTexture(renderer, IMG_SUN);
    if (sun == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

/*    
    SDL_Texture *shadow;
    shadow = IMG_LoadTexture(renderer, IMG_SHADOW);
    if (sun == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
*/
    //animation
    animation(window, renderer, background, trou_noir, sprite);
    /*
    play_texture_full_window(background, window, renderer);
    play_texture_xy(trou_noir, window, renderer);
    SDL_RenderPresent(renderer); // affichage
    SDL_Delay(1000);
    play_texture_anime(sun, window, renderer);
    play_texture_sprite_courir(sprite, window, renderer);
    play_texture_sprite_avec_bg(background, shadow, window, renderer);
*/
    SDL_Delay(500);
    SDL_RenderClear(renderer);

    IMG_Quit();
    end_sdl(1, "Fermeture SDL normale", window, renderer);
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

    float zoom = 0.5;

    destination.h = source.h * zoom;
    destination.w = source.w * zoom;

    destination.x = (window_dimensions.w - 0.7 * destination.w) / 2;
    destination.y = (window_dimensions.h - 1.6 * destination.h) / 2;
    SDL_RenderCopy(renderer, my_texture, &source, &destination);
}

void play_texture_anime(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    /* On décide de déplacer dans la fenêtre         cette image */
    float zoom = 0.25; // Facteur de zoom entre l'image source et l'image affichée

    int nb_it = 200;                 // Nombre d'images de l'animation
    destination.w = source.w * zoom; // On applique le zoom sur la largeur
    destination.h = source.h * zoom; // On applique le zoom sur la hauteur
    destination.x =
        (window_dimensions.w - destination.w) / 2; // On centre en largeur
    float h = window_dimensions.h - destination.h; // hauteur du déplacement à effectuer

    for (int i = 0; i < nb_it; ++i)
    {
        destination.y =
            h * (1 - exp(-5.0 * i / nb_it) / 2 *
                         (1 + cos(10.0 * i / nb_it * 2 *
                                  M_PI))); // hauteur en fonction du numéro d'image

        SDL_RenderClear(renderer); // Effacer l'image précédente

        SDL_SetTextureAlphaMod(my_texture, (1.0 - 1.0 * i / nb_it) * 255); // L'opacité va passer de 255 à 0 au fil de l'animation
        SDL_RenderCopy(renderer, my_texture, &source, &destination);       // Préparation de l'affichage
        SDL_RenderPresent(renderer);                                       // Affichage de la nouvelle image
        SDL_Delay(30);                                                     // Pause en ms
    }
    SDL_RenderClear(renderer);
}

void play_texture_sprite_courir(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions.w,
                      &window_dimensions.h);
    SDL_QueryTexture(my_texture, // Récupération des dimensions de l'image
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

    destination.y = // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination.h) / 2;

    int speed = 9;
    for (int x = 0; x < window_dimensions.w - destination.w; x += speed)
    {
        destination.x = x;   // Position en x pour l'affichage du sprite
        state.x += offset_x; // On passe à la vignette suivante dans l'image
        state.x %= source.w; // La vignette qui suit celle de fin de ligne est
                             // celle de début de ligne

        SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                       &state,
                       &destination);
        SDL_RenderPresent(renderer); // Affichage
        SDL_Delay(80);               // Pause en ms
    }
    SDL_RenderClear(renderer); // Effacer la fenêtre avant de rendre la main
}

void play_texture_sprite_avec_bg(SDL_Texture *bg_texture, SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions.w,
                      &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, // Récupération des dimensions de l'image
                     &source.w, &source.h);

    int nb_images = 40;                      //  Il y a 8 vignette dans la ligne qui nous intéresse
    int nb_images_animation = 1 * nb_images; //
    float zoom = 2;                          // zoom, car ces images sont un peu petites
    int offset_x = source.w / 4,             // La largeur d'une vignette de l'image
        offset_y = source.h / 5;             // La hauteur d'une vignette de l'image
    SDL_Rect state[40];                      // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    /* construction des différents rectangles autour de chacune des vignettes de la planche */
    int i = 0;
    for (int y = 0; y < source.h; y += offset_y)
    {
        for (int x = 0; x < source.w; x += offset_x)
        {
            state[i].x = x;
            state[i].y = y;
            state[i].w = offset_x;
            state[i].h = offset_y;
            ++i;
        }
    }
    state[14] = state[13]; // state[14 à 16] la même image, le monstre ne bouge pas
    state[15] = state[16];
    for (; i < nb_images; ++i)
    { // reprise du début de l'animation en sens inverse
        state[i] = state[39 - i];
    }

    destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
    destination.x = window_dimensions.w * 0.75; // Position en x pour l'affichage du sprite
    destination.y = window_dimensions.h * 0.7;  // Position en y pour l'affichage du sprite

    i = 0;
    for (int cpt = 0; cpt < nb_images_animation; ++cpt)
    {
        play_texture_full_window(bg_texture, // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                                 window, renderer);
        SDL_RenderCopy(renderer, // Préparation de l'affichage
                       my_texture, &state[i], &destination);
        i = (i + 1) % nb_images;     // Passage à l'image suivante, le modulo car l'animation est cyclique
        SDL_RenderPresent(renderer); // Affichage
        SDL_Delay(100);              // Pause en ms
    }
    SDL_RenderClear(renderer); // Effacer la fenêtre avant de rendre la main
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

    destination.x = (1.15 * window_dimensions.w - destination.w) / 2;
    destination.y = (0.8 * window_dimensions.h - destination.h) / 2;
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

    destination.y = 0.9 * window_dimensions.h; // La course se fait en milieu d'écran (en vertical)

    for (int t = 0; t < 110; t++)
    {
        play_texture_full_window(bg_texture, window, renderer);
        play_texture_xy_taille(trou_noir, window, renderer, t * taille / 2);

        if (destination.y > 0.7 * window_dimensions.h)
        {
            destination.x = 0.1 * window_dimensions.w + 6.5 * t; // Position en x pour l'affichage du sprite
            destination.y -= t / 10;
            state.x += offset_x; // On passe à la vignette suivante dans l'image
            state.x %= source.w; // La vignette qui suit celle de fin de ligne est
            SDL_RenderCopy(renderer, sprite, &state, &destination);
        }
        else if (destination.y > 0.35 * window_dimensions.h)
        {
            destination.y -= t * t / 100;
            state.x = 1;
            state.y = 2 * offset_y;
            SDL_RenderCopy(renderer, sprite, &state, &destination);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(60);
    }
}