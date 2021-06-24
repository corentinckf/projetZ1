#include "const.h"

int main()
{

    //srand(time(NULL));
    srand(48);
    Uint8 const *keystates;

    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int vertical = 0;
    int horizontal = 0;
    int coll = 0;

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

    /********* initialisation perso **************/
    entite_t *perso = NULL;
    bombe_t *bombe = NULL;
    creer_entite(window, renderer, 10 - 1, 10, 1, 0, 0, &perso, PATH_IMG_PERSO);

    //////////////////////********creation boules*********/////////////////////////////
    entite_t *liste_boule[NB_BOULES];

    for (int i = 0; i < NB_BOULES; ++i)
    {
        liste_boule[i] = NULL;
    }
<<<<<<< HEAD
    SDL_Delay(1000);
    SDL_RenderClear(renderer);
    int map_bis_tab[NB_LIGNE_LABY][NB_COLONNE_LABY];
    map_bis(map, map_bis_tab, tab_boule, 0);
    play_texture_mur(window, renderer, texture_mur, map_bis_tab);
    
    SDL_Delay(5000);
=======
>>>>>>> fe0b162cbf62bd9e417e3788323b5f26f0027891

    creer_entite(window, renderer, 0, 0, 0, 0, 0, &liste_boule[0], PATH_IMG_BOULE);

    creer_entite(window, renderer, 0, NB_COLONNE_LABY - 1, 0, 0, 0, &liste_boule[1], PATH_IMG_BOULE);

    creer_entite(window, renderer, 0, (NB_LIGNE_LABY - 1) * (NB_COLONNE_LABY - 1), 0, 0, 0, &liste_boule[2], PATH_IMG_BOULE);

    creer_entite(window, renderer, 0, NB_COLONNE_LABY * NB_LIGNE_LABY, 0, 0, 0, &liste_boule[3], PATH_IMG_BOULE);
    //////////////////////*****************************/////////////////////////////

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
                creer_bombe(window,renderer,perso->pos_cour,3,5,&bombe,PATH_IMG_BOMBE);
                    nb_bombes++;
                    break;
                case SDLK_SPACE:      // 'SPC'
                    paused = !paused; // basculement pause/unpause
                    break;
                case SDLK_ESCAPE:   // 'ESCAPE'
                case SDLK_q:        // 'q'
                    program_on = 0; // 'escape' ou 'q', d'autres façons de quitter le programme
                    break;
                default: // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }

        /********** Regarde les touches de directions ************/
        keystates = SDL_GetKeyboardState(NULL);
        horizontal = keystates[SDL_SCANCODE_LEFT] * (-1) + keystates[SDL_SCANCODE_RIGHT];
        vertical = keystates[SDL_SCANCODE_UP] * (-1) + keystates[SDL_SCANCODE_DOWN];
        if (abs(horizontal - vertical))
        {
            vertical = 0;
            horizontal = 0;
        }

    
        if (!paused)
        { // Si on n'est pas en pause

            //calcul perso
            //deplacement_perso(map, perso, vertical, horizontal);

            //calcul boule
            //deplacement_toutes_boules(map, liste_boule, perso->pos_cour);

            //affichage fond
            play_texture_mur(window, renderer, texture_mur, map);
            //affichage entite perso
            //affichage_entite(window, renderer, perso);
            //affichage_entite
            for (int k = 0; k < NB_BOULES; ++k)
            {
                affichage_entite(window, renderer, liste_boule[k]);
            }
            //affichage entite boule

            coll = collision(perso, liste_boule);
            if (coll)
            { //program_on = 0;
            }
            SDL_RenderPresent(renderer);

            SDL_Delay(1000);
            SDL_RenderClear(renderer);
        }
        SDL_Delay(20); // Petite pause
    }

    SDL_DestroyTexture(texture_mur);
    end_sdl(1, "fin normal", window, renderer);
    return 0;
}
