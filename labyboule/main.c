#include "const.h"

int main()
{

    //srand(time(NULL));
    srand(48);

    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int vitesse = 0;

    SDL_Rect window_dimensions = {0};

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
        "LabyBoule",
        (screen.w - LARGEUR_FENETRE) / 2, (screen.h - HAUTEUR_FENETRE) / 2,
        LARGEUR_FENETRE, HAUTEUR_FENETRE,
        0);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    /************** creation renderer ****************/
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /********* chargement texture map ***********/
    SDL_Texture *texture_mur;
    texture_mur = IMG_LoadTexture(renderer, PATH_IMG_MUR);
    if (texture_mur == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    /*********** initialisation map **************/
    int map[NB_LIGNE_LABY][NB_COLONNE_LABY];
    init_map(map);
    play_texture_mur(window, renderer, texture_mur, map);

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
                    if (vitesse > VITESSE_MIN)
                        vitesse--;
                    break;
                case SDLK_RIGHT:
                    if (vitesse < VITESSE_MAX)
                        vitesse++;
                    break;
                default: // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }

        if (!paused)
        { // Si on n'est pas en pause

            //calcul perso
            //calcul boule

            //affichage entite perso
            //affichage entite boule
            play_texture_mur(window, renderer, texture_mur, map);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            SDL_RenderClear(renderer);
        }
        SDL_Delay(20); // Petite pause
    }

    SDL_DestroyTexture(texture_mur);
    end_sdl(1, "fin normal", window, renderer);
    return 0;
}