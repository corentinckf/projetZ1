#include "jeu_de_la_vie.h"

int main()
{
    int super_grille[2][HAUTEUR_GRILLE][LARGEUR_GRILLE];

    int n;
    int grille_etat_n = 0;
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

    init_map(super_grille[0]);
    init_map(super_grille[1]);
    placement_config_depart(super_grille[0]);

    draw(renderer, super_grille[0], couleurs); // appel de la fonction qui crée l'image
    SDL_RenderPresent(renderer);               // affichage

    for (n = 1; n < N; n++)
    {

        SDL_Delay(VITESSE);
        etape(super_grille, grille_etat_n);
        draw(renderer, super_grille[grille_etat_n], couleurs);
        grille_etat_n = n % 2;
        SDL_RenderPresent(renderer);
    }

    SDL_Delay(2000);
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

void placement_config_depart(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE])
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