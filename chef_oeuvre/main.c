#include "main.h"

int main()
{
    int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE];
    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int vitesse = 0;
    perso_t *perso = NULL;

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
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /************** creation renderer ****************/
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /************** initialisation ttf ****************/
    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);
    /**** fin initialisation  *****/

    /****** chargement de la font *******/
    TTF_Font *font = NULL;                                                                                   // la variable 'police de caractère'
    font = TTF_OpenFont(PATH_FONT, TAILLE_FONT); // La police à charger, la taille désirée    if (font == NULL)
    if (font == NULL)
        end_sdl(0, "Can't load font", window, renderer);

  
    /***************************/
    perso = creer_perso(window, renderer);
    init_map(grille);

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
        //draw(state, &color, renderer, window); // On redessine
        if (!paused)
        { // Si on n'est pas en pause

            affichage_texte(window, renderer, font, texte_score(perso->score), 1, LARGEUR_FENETRE / 2, 0);
            deplacement_perso(perso, &vitesse);
            check_collision(perso, grille);
            play_with_texture_perso(perso, window, renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
            SDL_RenderClear(renderer);
            if (perso->score >= GOAL_SCORE)
            {
                printf("Score atteint %d\n", perso->score);
                program_on = 0;
            }
        }
        SDL_Delay(50); // Petite pause
    }

    //end_sdl(1, "fin normal", window, renderer);
    return 0;
}

void init_map(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE])
{
    int i, j;
    for (i = 0; i < HAUTEUR_GRILLE; i++)
        for (j = 0; j < LARGEUR_GRILLE; j++)
            grille[i][j] = 0;
}

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{ // renderer à fermer
    char msg_formated[255];
    int l;

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

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}

char *texte_score(int a)
{

    char *nom = malloc(12 * sizeof(char));
    nom[0] = '\0';
    strcat(nom, "score : ");
    char nb[1] = "";
    sprintf(nb, "%d", a);
    strcat(nom, nb);

    return nom;
}
