#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//taille de la grille
#define LIGNES 30
#define COLONNES 50

//le tableau survie est rempli de 0 et 1 : si survie[k]=1, alors la cellule survit et 0 sinon
int survie[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0};
int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 0, 0};

//on construit les tableaux survie et naissance aleatoirement
/*int k;
for (k=0;k<9;k++)
{
    survie[k]=rand()%2;
    naissance[k]=rand()%2;
}*/

//on construit les tableaux survie et naissance selon la regle donnee par ScienceEtonnante
/*
int k;
for (k=0;k<9;k++)
{
    survie[k]=0;
    naissance[k]=0;
}
survie[2] = 1;
survie[3] = 1;
naissance[3] = 1;
*/

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message a afficher
             SDL_Window *window, // fenêtre a fermer
             SDL_Renderer *renderer)
{ // renderer a fermer
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

    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}

//retourne 1 si la cellule survit et 0 si elle meurt
int devenir(int mat[LIGNES][COLONNES], int *i, int *j)
{
    int s = 0;
    int ligne, colonne;
    int resultat = -1; //la valeur -1 indique une erreur

    for (ligne = (*i) - 1; ligne < (*i) + 2; ligne++)
    {
        for (colonne = (*j) - 1; colonne < (*j) + 2; colonne++)
        {
            s += mat[(ligne + LIGNES) % LIGNES][(colonne + COLONNES) % COLONNES];
        }
    }
    s -= mat[*i][*j];
    //s est la somme des 8 cases entourant la cellule (i,j), s est donc le nombre de voisins de la cellule

    //fprintf(stdout,"nombre de voisins : %d\n", s);

    if (mat[*i][*j] == 1) //cellule en vie
    {
        resultat = survie[s];
    }
    else //cellule morte
    {
        resultat = naissance[s];
    }
    return resultat;
}

//evolution de l'etat N a l'etat N+1
void evolution(int mat[LIGNES][COLONNES], int matsuiv[LIGNES][COLONNES])
{
    int resultat;
    int i, j;

    for (i=0;i<LIGNES;i++)
    {
        for (j=0;j<COLONNES;j++)
        {
            resultat = devenir(mat, &i, &j);
            if (resultat < 0)
            {
                fprintf(stderr, "probleme d'evolution");
            }
            else
            {
                matsuiv[i][j] = resultat;
            }
        }
    }
}

void draw(SDL_Renderer *renderer, int mat[LIGNES][COLONNES], float *h, float *l)
{
    SDL_Rect rectangle;
    int i, j;

    for (i = 0; i < LIGNES; i++)
    {
        for (j = 0; j < COLONNES; j++)
        {
            if (mat[i][j] == 0) //cellule morte : en blanc
            {
                SDL_SetRenderDrawColor(renderer,
                                       255, 255, 255, // mode Red, Green, Blue (tous dans 0..255)
                                       255);          // 0 = transparent ; 255 = opaque
            }
            else //cellule en vie : en noir
            {
                SDL_SetRenderDrawColor(renderer,
                                       0, 0, 0, // mode Red, Green, Blue (tous dans 0..255)
                                       255);    // 0 = transparent ; 255 = opaque
            }
            rectangle.x = j * (*l);
            rectangle.y = i * (*h);
            rectangle.w = *l;
            rectangle.h = *h;
            SDL_RenderFillRect(renderer, &rectangle);
        }
    }
}

void init(int mat[LIGNES][COLONNES])
{
    int i, j;

    for (i = 0; i < LIGNES; i++)
    {
        for (j = 0; j < COLONNES; j++)
        {
            mat[i][j] = 0;
        }
    }
}


int main()
{
    int etat_n[LIGNES][COLONNES];
    int etat_suiv[LIGNES][COLONNES];
    int i, j;
    int x, y; //position de la souris
    int ligne=0,colonne=0;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool
        program_on = SDL_TRUE, // Booleen pour dire que le programme doit continuer
        paused = SDL_TRUE;     // Booleen pour dire que le programme est en pause
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Jeu de la vie",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1000,
                              600,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    float hauteur_pixel = 600 / LIGNES;
    float largeur_pixel = 1000 / COLONNES;

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    init(etat_n);
    draw(renderer, etat_n, &hauteur_pixel, &largeur_pixel);
    SDL_RenderPresent(renderer);
    while (paused && program_on)
    {
        //fprintf(stdout,"on est rentre dans la boucle\n");
        SDL_Delay(10);
        if (SDL_PollEvent(&event)){
        switch (event.type) // En fonction de la valeur du type de cet evenement
        {
        case SDL_QUIT:              // Un evenement simple, on a clique sur la x de la fenêtre
            program_on = SDL_FALSE; // Il est temps d'arrêter le programme
            fprintf(stdout,"quitter\n");
            break;
        case SDL_KEYDOWN: // Le type de event est : une touche appuyee ;comme la valeur du type est SDL_Keydown, dans la pratie 'union' de l'event, plusieurs champs deviennent pertinents
            switch (event.key.keysym.sym)
            {
            case SDLK_KP_ENTER:
                paused = SDL_FALSE;
                break;
            case SDLK_RETURN:
                paused = SDL_FALSE;
                break;
            default:
                break;
            }
        case SDL_MOUSEBUTTONDOWN:                                         // Click souris
            if (SDL_GetMouseState(&x, &y) && SDL_BUTTON(SDL_BUTTON_LEFT)) // Si c'est un click gauche
            {
                ligne = y / hauteur_pixel;
                colonne = x / largeur_pixel;
                //printf("ligne : %d \t colonne : %d\n", ligne, colonne);
                etat_n[ligne][colonne] = 1; //faire naitre la cellule lors d'un click gauche
                draw(renderer, etat_n, &hauteur_pixel, &largeur_pixel);
                SDL_RenderPresent(renderer);
            }
            else if (SDL_GetMouseState(&x, &y) && SDL_BUTTON(SDL_BUTTON_RIGHT)) // Si c'est un click droit
            {
                ligne = y / hauteur_pixel;
                colonne = x / largeur_pixel;
                etat_n[ligne][colonne] = 0; //faire mourir la cellule lors d'un click droit
                draw(renderer, etat_n, &hauteur_pixel, &largeur_pixel);
                SDL_RenderPresent(renderer);
            }
            break;
        default:
            break;
        }
        }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    while (program_on)
    {
        while (program_on && SDL_PollEvent(&event)) // Tant que la file des evenements stockes n'est pas vide et qu'on n'a pas termine le programme Defiler l'element en tête de file dans 'event'
        {
            switch (event.type) // En fonction de la valeur du type de cet evenement
            {
            case SDL_QUIT:              // Un evenement simple, on a clique sur la x de la // fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN:                 // Le type de event est : une touche appuyee ;comme la valeur du type est SDL_Keydown, dans la pratie 'union' de l'event, plusieurs champs deviennent pertinents
                switch (event.key.keysym.sym) // la touche appuyee est ...
                {
                case SDLK_ESCAPE:   // 'ESCAPE'
                    program_on = 0; // 'escape' ou 'q', d'autres façons de quitter le programme
                    break;
                case SDLK_q:        // 'q'
                    program_on = 0; // 'escape' ou 'q', d'autres façons de quitter le programme
                    break;
                case SDLK_SPACE:      // 'SPC'
                    paused = !paused; // basculement pause/unpause
                    break;
                default: // Une touche appuyee qu'on ne traite pas
                    break;
                }
                break;
            }
        }
        while (paused && program_on && SDL_PollEvent(&event))
        {
            SDL_Delay(100);
            switch (event.type) // En fonction de la valeur du type de cet evenement
            {
            case SDL_QUIT:              // Un evenement simple, on a clique sur la x de la // fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN: // Le type de event est : une touche appuyee ;comme la valeur du type est SDL_Keydown, dans la partie 'union' de l'event, plusieurs champs deviennent pertinents
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    paused = !paused;
                    break;
                default:
                    break;
                }
            }
        }
        if (!paused)
        {
            draw(renderer, etat_n, &hauteur_pixel, &largeur_pixel);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            evolution(etat_n, etat_suiv);

            //recopie de la matrice etat n+1 dans la matrice etat n
            for (i = 0; i < LIGNES; i++)
            {
                for (j = 0; j < COLONNES; j++)
                {
                    etat_n[i][j] = etat_suiv[i][j];
                }
            }
        }
    }
    return 0;
}