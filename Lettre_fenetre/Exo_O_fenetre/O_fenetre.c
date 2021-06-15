#include "util_sdl.h"

#define LARGEUR_FENETRE 400
#define HAUTEUR_FENETRE 300


/***************************************/
/*  Z_fenetre affiche des fenetre en O */
/***************************************/
void test_fenetre(SDL_Window *fenetre)
{
    if (fenetre == NULL)
    {
        SDL_Log("Error : SDL Window creation - %s\n", SDL_GetError()); // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{

    SDL_DisplayMode screen;

    int i;
    int j;
    int nb_fenetre_largeur;
    int nb_fenetre_hauteur;
    SDL_Window **tab_p_fenetre;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    nb_fenetre_largeur = screen.w / LARGEUR_FENETRE + 1;
    nb_fenetre_hauteur = screen.h / HAUTEUR_FENETRE + 1;

    printf("nb fenetre\n\tw : %d\n\th : %d\n", nb_fenetre_largeur, nb_fenetre_hauteur);

    tab_p_fenetre = (SDL_Window **)malloc(sizeof(SDL_Window *) * 3 * nb_fenetre_largeur);

    for (i = 0; i < nb_fenetre_largeur; i++)
    {
        //Fenetre ligne du haut
        tab_p_fenetre[i] = SDL_CreateWindow(
            "Window",                         // codage en utf8, donc accents possibles
            i * LARGEUR_FENETRE, 0,           // position
            LARGEUR_FENETRE, HAUTEUR_FENETRE, // largeur, hauteur
            0);

        test_fenetre(tab_p_fenetre[i]);

        //fenetre ligne de bas
        tab_p_fenetre[nb_fenetre_largeur + i] = tab_p_fenetre[i] = SDL_CreateWindow(
            "Window",                                                         // codage en utf8, donc accents possibles
            screen.w - (i + 1) * LARGEUR_FENETRE, screen.h - HAUTEUR_FENETRE, // position
            LARGEUR_FENETRE, HAUTEUR_FENETRE,                                 // largeur, hauteur
            0);

        test_fenetre(tab_p_fenetre[nb_fenetre_largeur + i]);
 
        //Fenetre verticale gauche
        tab_p_fenetre[2 * nb_fenetre_largeur + i] = SDL_CreateWindow(
            "Window",                                                  // codage en utf8, donc accents possibles
            0 * LARGEUR_FENETRE, HAUTEUR_FENETRE * i, // position
            LARGEUR_FENETRE, HAUTEUR_FENETRE,                          // largeur, hauteur
            0);

        //Fenetre verticale droite
        tab_p_fenetre[2 * nb_fenetre_largeur + i] = SDL_CreateWindow(
            "Window",                                                  // codage en utf8, donc accents possibles
            screen.w - LARGEUR_FENETRE, HAUTEUR_FENETRE * i, // position
            LARGEUR_FENETRE, HAUTEUR_FENETRE,                          // largeur, hauteur
            0);

        test_fenetre(tab_p_fenetre[2 * nb_fenetre_largeur + i]);
   
        SDL_Delay(500);
    }

    SDL_Delay(10000);

    //Liberation de toutes les fenetres
    for (i = 0; i < 3 * nb_fenetre_largeur; i++)
    {
        SDL_DestroyWindow(tab_p_fenetre[i]);
    }

    free(tab_p_fenetre);
    SDL_Quit();
    return 0;
}