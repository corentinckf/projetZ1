#include "const.h"

int main()
{

    //srand(time(NULL));
    srand(48);
    Uint8 const *keystates;

    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int currentTime = SDL_GetTicks();
    int lastTime = currentTime;
    int delta_tps = 0;

    int vertical = 0;
    int horizontal = 0;
    int coll = 0;
    float anim_perso = 0.;
    float anim_boule = 0.;
    //int periode = 0;

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
        LARGEUR_FENETRE+LARGEUR_CASE*5, HAUTEUR_FENETRE,
        0);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    /************** creation renderer ****************/
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /************** initialisation ttf ****************/
    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);
    /**** fin initialisation  *****/

    /****** chargement de la font *******/
    TTF_Font *font = NULL;                       // la variable 'police de caractère'
    font = TTF_OpenFont(PATH_FONT, TAILLE_FONT); // La police à charger, la taille désirée    if (font == NULL)
    if (font == NULL)
        end_sdl(0, "Can't load font", window, renderer);

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
    float vitesse_perso = 1;
    creer_entite(window, renderer, PERSO_POS, PERSO_POS, vitesse_perso, 0, 0, &perso, PATH_IMG_PERSO);

    //////////////////////********creation boules*********/////////////////////////////
    entite_t *liste_boules[NB_BOULES];
    int nb_boules = 0;
    float vitesse_boule = 0.5;
    for (int i = 0; i < NB_BOULES; ++i)
    {
        liste_boules[i] = NULL;
    }

    creer_entite(window, renderer, 0, 1, vitesse_boule, 0, 0, &liste_boules[0], PATH_IMG_BOULE);

    creer_entite(window, renderer, 0, NB_COLONNE_LABY - 1, vitesse_boule, 0, 0, &liste_boules[1], PATH_IMG_BOULE);

    creer_entite(window, renderer, 0, (NB_LIGNE_LABY - 1) * (NB_COLONNE_LABY - 1), vitesse_boule, 0, 0, &liste_boules[2], PATH_IMG_BOULE);

    creer_entite(window, renderer, 0, NB_LIGNE_LABY * NB_COLONNE_LABY - 1, vitesse_boule, 0, 0, &liste_boules[3], PATH_IMG_BOULE);

    nb_boules = NB_BOULES;
    //////////////////////*****************************/////////////////////////////

    //////////////////////********creation boules*********/////////////////////////////

    int nb_bombes = 0;
    bombe_t *liste_bombes[NB_BOMBES];
    for (int i = 0; i < NB_BOMBES; ++i)
    {
        liste_bombes[i] = NULL;
    }
    //////////////////////********creation boules*********/////////////////////////////

    SDL_bool
        program_on = SDL_TRUE, // Booléen pour dire que le programme doit continuer
        paused = SDL_FALSE;    // Booléen pour dire que le programme est en pause
    //ecran_debut(window, renderer, font);
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
                {                // la touche appuyée est ...
                case SDLK_SPACE: // 'SPC'
                    ajouter_bombe(window, renderer,
                                  liste_bombes, &nb_bombes, perso);
                    break;
                case SDLK_p: // 'p'
                    paused = !paused;
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:        // 'q'
                    program_on = 0; // 'escape' ou 'q', d'autres façons de quitter le programme
                    break;
                /*
                case SDLK_LEFT:
                    horizontal = -1;
                    break;
                case SDLK_RIGHT:
                    horizontal = 1;
                    break;
                case SDLK_UP:
                    vertical = -1;
                    break;
                case SDLK_DOWN:
                    vertical = 1;
                    break;
       */
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

        if (!horizontal)
            horizontal = keystates[SDL_SCANCODE_LEFT] * (-1) + keystates[SDL_SCANCODE_RIGHT];

        if (!vertical)
            vertical = keystates[SDL_SCANCODE_UP] * (-1) + keystates[SDL_SCANCODE_DOWN];

        if (!paused)
        { // Si on n'est pas en pause

            currentTime = SDL_GetTicks();
            delta_tps += currentTime - lastTime;
            lastTime = currentTime;
            //calcul perso
            if (delta_tps > PERIODE)
            {
                //for (int u = 0; u < perso->vitesse; ++u)
                deplacement_perso(map, perso, &vertical, &horizontal);
                //printf("v %d h %d\n", vertical, horizontal);

                //calcul boule
                deplacement_toutes_boules(map, liste_boules, perso->pos_cour);

                delta_tps = 0;
            }
            //affichage fond
            play_texture_mur(window, renderer, texture_mur, map);
            //affichage entite perso
            affichage_entite(window, renderer, perso, delta_tps, anim_perso);
            //affichage_entite
            for (int k = 0; k < NB_BOULES; ++k)
            {
                if (liste_boules[k] != NULL)
                    affichage_entite(window, renderer, liste_boules[k], delta_tps, anim_boule);
            }

            //printf("nb de bombes : %d\n",nb_bombes);
            affichage_liste_bombes(window, renderer, liste_bombes);

            //affichage entite boule
            anim_perso += 1;
            anim_boule += 0.3;
            coll = collision(delta_tps, perso, liste_boules, &nb_boules,
                             liste_bombes, &nb_bombes, map);
            if (coll == 1 || coll == -1)
            {
                program_on = SDL_FALSE;
            }
            else
            {
                coll = 0;
            }

            SDL_RenderPresent(renderer);

            //SDL_Delay(1000);
            SDL_RenderClear(renderer);
        }
        SDL_Delay(80); // Petite pause
    }

    SDL_Delay(500); // Petite pause

    liberer_entite(&perso);
    liberer_liste_boules(liste_boules);
    SDL_DestroyTexture(texture_mur);
    ecran_fin(window, renderer, font, coll);

    end_sdl(1, "fin normal", window, renderer);
    return 0;
}
