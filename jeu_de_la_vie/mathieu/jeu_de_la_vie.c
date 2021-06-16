#include "jeu_de_la_vie.h"

int main()
{
    int super_grille[2][HAUTEUR_GRILLE][LARGEUR_GRILLE];

    int grille_etat_n = 0;
    //int init_grille_main = 1;
    int vitesse = VITESSE_BASE;
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
        "Jeu de la Vie",
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
    /******* fin initialisation de la sdl *************/

    //initialisation des grilles a 0
    init_map(super_grille[0]);
    init_map(super_grille[1]);
    //placement_config_depart_alea_alea(super_grille[0]);

    int x_mouse, y_mouse;

    SDL_bool
        program_on = SDL_TRUE, // Booléen pour dire que le programme doit continuer
        paused = 1;            // Booléen pour dire que le programme est en pause

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
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_q:                // 'q'
                    program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                    break;
                case SDLK_p:          // 'p'
                    paused = !paused; // basculement pause/unpause
                    break;
                case SDLK_SPACE:      // 'SPC'
                    paused = !paused; // basculement pause/unpause
                    break;
                case SDLK_KP_PLUS: // '+'
                    if (vitesse - 10 > 0)
                    {
                        vitesse -= 10; // augment la vitesse de jeu
                        //printf("+++\n");
                    }
                    break;
                case SDLK_KP_MINUS: // '-'
                    vitesse += 10;  // diminue la vitesse de jeu
                    break;
                default:
                    break;
                }
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (paused && SDL_GetMouseState(&x_mouse, &y_mouse) & SDL_BUTTON(SDL_BUTTON_LEFT))
                { // Si c'est un click gauche
                    placement_cellule_souris(super_grille[0], x_mouse, y_mouse);
                }
                break;
            default:
                break;
            }
        }
        //draw(state, &color, renderer, window); // On redessine
        draw(renderer, super_grille[grille_etat_n], couleurs);
        SDL_RenderPresent(renderer);
        //printf("pause %d\n", paused);

        if (!paused)
        { // Si on n'est pas en pause
            etape(super_grille, grille_etat_n);
            draw(renderer, super_grille[grille_etat_n], couleurs);
            grille_etat_n = (grille_etat_n + 1) % 2;
            SDL_RenderPresent(renderer);
        }
        SDL_Delay(5 + vitesse); // Petite pause
    }

    SDL_Delay(1500);
    end_sdl(0, "Fin normal", fenetre, renderer);
    return EXIT_SUCCESS;
}

void etape(int super_grille[2][HAUTEUR_GRILLE][LARGEUR_GRILLE], int grille_etat_n)
{
    int i, j;
    int etat_n;
    int etat_n_plus_1;
    int nb_voisins;
    for (i = 0; i < HAUTEUR_GRILLE; i++)
    {
        for (j = 0; j < LARGEUR_GRILLE; j++)
        {
            etat_n = super_grille[grille_etat_n][i][j];

            nb_voisins = cb_nb_voisins(super_grille[grille_etat_n], j, i);

            if (etat_n) //cellule vivante
                etat_n_plus_1 = survie[nb_voisins];
            else //cellule morte
                etat_n_plus_1 = naissance[nb_voisins];

            super_grille[(grille_etat_n + 1) % 2][i][j] = etat_n_plus_1;
        }
    }
}

int cb_nb_voisins(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], int x, int y)
{
    int i, j;
    int u, v;
    int nb_voisins = 0;
    for (i = -1; i < 2; i++)
        for (j = -1; j < 2; j++)
        {
            u = (y + i + HAUTEUR_GRILLE) % HAUTEUR_GRILLE;
            v = (x + j + LARGEUR_GRILLE) % LARGEUR_GRILLE;
            nb_voisins += grille[u][v];
        }

    nb_voisins -= grille[y][x];

    return nb_voisins;
}

void draw(SDL_Renderer *renderer, int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], int couleurs[NB_COULEURS][3])
{
    int i, j, c;
    SDL_Rect rect;
    for (i = 0; i < HAUTEUR_GRILLE; i++)
    {
        for (j = 0; j < LARGEUR_GRILLE; j++)
        {
            c = grille[i][j];
            SDL_SetRenderDrawColor(renderer, couleurs[c][0], couleurs[c][1], couleurs[c][2], 255);
            rect.x = j * TAILLE_PIXEL;
            rect.y = i * TAILLE_PIXEL;
            rect.w = 1 * TAILLE_PIXEL;
            rect.h = 1 * TAILLE_PIXEL;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void placement_config_depart_alea(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE])
{
    srand(time(NULL));
    int i, j;
    for (i = 0; i < HAUTEUR_GRILLE; i++)
        for (j = 0; j < LARGEUR_GRILLE; j++)
            grille[i][j] = rand() % 2;
}

void init_map(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE])
{
    int i, j;
    for (i = 0; i < HAUTEUR_GRILLE; i++)
        for (j = 0; j < LARGEUR_GRILLE; j++)
            grille[i][j] = 0;
}
void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{ // fin anormale : ok = 0 ; normale ok = 1// message à afficher// fenêtre à fermer // renderer a fermer

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

void placement_cellule_souris(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], int x_m, int y_m)
{
    int i = y_m / TAILLE_PIXEL;
    int j = x_m / TAILLE_PIXEL;
    if (i >= 0 && i < HAUTEUR_GRILLE)
    {
        if (j >= 0 && j < LARGEUR_FENETRE)
            grille[i][j] = !grille[i][j];
        printf("y_mouse %d, i %d\n", y_m, i);
        printf("x_mouse %d, j %d\n", x_m, j);
    }
    else
        printf("erreur dans les indices retourne par la souris\n");
}
