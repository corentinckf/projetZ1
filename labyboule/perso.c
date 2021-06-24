#include "const.h"
#include "perso.h"

int main(int argc, char *argv[])
{
    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int input_h = 0 , input_v = 0, debut = 0, fin = 0, x = 0, y = 0;
    unsigned int tempPrecedent = 0, tempsActuel = 0, deltaTime = 0;
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
    
    SDL_bool
        program_on = SDL_TRUE, // Booléen pour dire que le programme doit continuer
        paused = SDL_FALSE;    // Booléen pour dire que le programme est en pause
    while (program_on)
    {                    // La boucle des évènements
        SDL_Event event; // Evènement à traiter

        while (program_on && SDL_PollEvent(&event))
        { // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
            // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN: // Le type de event est : une touche appuyée
                              // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                              // l'event, plusieurs champs deviennent pertinents
                switch (event.key.keysym.sym)
                {                     // la touche appuyée est ...
                case SDLK_p:          // 'p'
                case SDLK_SPACE:      // 'SPC'
                    paused = !paused; // basculement pause/unpause
                    break;
                case SDLK_ESCAPE:   // 'ESCAPE'
                case SDLK_q:        // 'q'
                    program_on = 0; // 'escape' ou 'q', d'autres façons de quitter le programme
                    break;
                case SDLK_LEFT:
                    input_h = -1;
                    break;
                case SDLK_RIGHT:
                    input_h = 1;
                    break;
                case SDLK_UP:
                    input_v = 1;
                    break;
                case SDLK_DOWN:
                    input_v = -1;
                    break;
                default: // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {                     // la touche appuyée est ...
                    case SDLK_LEFT:
                        input_h = 0;
                        break;
                    case SDLK_RIGHT:
                        input_h = 0;
                        break;
                    case SDLK_UP:
                        input_v = 0;
                        break;
                    case SDLK_DOWN:
                        input_v = 0;
                        break;
                    default: // Une touche appuyée qu'on ne traite pas
                        break;
                }
                break;
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }
        //draw(state, &color, renderer, window); // On redessine
        if (!paused)
        { 

            tempsActuel = SDL_GetTicks();
            if(deltaTime > BOUCLE_DELAY)
            {
                deltaTime = 0;
                debut = fin;
            }
            deltaTime += tempsActuel - tempPrecedent;
            
            affichage_entite(window, renderer, sprite, &input_h, &input_v, &x, &y, &deltaTime);
            printf("Position joueur : %d \n", debut);
            tempPrecedent = tempsActuel;
            
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            SDL_Delay(BOUCLE_DELAY);

        }
    }
    

    IMG_Quit();
    end_sdl(1, "Fermeture SDL normale", window, renderer);
    return 0;
}

void affichage_entite(SDL_Window * window, SDL_Renderer * renderer,SDL_Texture * sprite, int * input_h, int * input_v, int * x, int * y, unsigned int * deltaTime)
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
    if(*input_h==0 && *input_v==0) idle = 1;
    else idle = 0;

    
    if(*input_v == 1)state.y = 1 * offset_y;
    else if(*input_v == -1)state.y = 0 * offset_y;


    if(*input_h == 1)state.y = 2 * offset_y;
    else if(*input_h == -1)state.y = 3 * offset_y;

    

    destination.w = offset_x * zoom; // Largeur du sprite à l'écran
    destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

    destination.y = 0.1 * window_dimensions.h; // La course se fait en milieu d'écran (en vertical)


    if(!idle)
    {
        state.x += offset_x;
        state.x %= source.w;
    }else{
        state.y = 0;
        state.x = 0;
    }

    

    destination.x += *x;/* * LARGEUR_CASE + (*deltaTime * *input_h * TRANSI);*/
    destination.y += *y;
    printf("x : %d y : %d\n", destination.x, destination.y);
    
    SDL_RenderCopy(renderer, sprite, &state, &destination);

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

