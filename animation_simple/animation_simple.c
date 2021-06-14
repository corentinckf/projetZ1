#include "animation_simple.h"

int main(int argc, char **argv)
{

    int i;
    int x_perso = 0;
    int y_perso = 2 * HAUTEUR_FENETRE / 3;

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
        "Animation Simple",
        (screen.w - LARGEUR_FENETRE) / 2, (screen.h - HAUTEUR_FENETRE) / 2,
        LARGEUR_FENETRE, HAUTEUR_FENETRE,
        SDL_WINDOW_RESIZABLE);

    if (fenetre == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", fenetre, renderer);

    /************** creation renderer ****************/
    renderer = SDL_CreateRenderer(
        fenetre, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", fenetre, renderer);

    for (i = 0; i < LARGEUR_FENETRE / 4; ++i)
    {
        /**************On dessine dans le renderer *************/
        draw(renderer, x_perso, y_perso); // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);      // affichage
        SDL_RenderClear(renderer);
        x_perso += 5;
        SDL_Delay(50);
        /******************************************************/
    }

    SDL_Delay(2000);

    end_sdl(0, "Fin normal", fenetre, renderer);
    return EXIT_SUCCESS;
}

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{ // renderer à fermer
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

void draw(SDL_Renderer *renderer, int x_pos, int y_pos)
{
    affichage_perso(renderer, x_pos, y_pos);
}

void affichage_perso(SDL_Renderer *renderer, int x_pos, int y_pos)
{

    SDL_Rect jambe;
    SDL_Rect bras;
    SDL_Rect tshirt;
    SDL_Rect tete;

    /****** jambe *********/
    jambe.x = x_pos;
    jambe.y = y_pos;
    jambe.w = LARGEUR_FENETRE / 40;
    jambe.h = HAUTEUR_FENETRE / 20;
    SDL_SetRenderDrawColor(renderer,
                           255, 0, 0, // mode Red, Green, Blue (tous dans 0..255)
                           255);      // 0 = transparent ; 255 = opaque
    SDL_RenderFillRect(renderer, &jambe);

    /****** bras *********/
    bras.w = LARGEUR_FENETRE / 20;
    bras.h = HAUTEUR_FENETRE / 20;
    bras.x = (x_pos + jambe.w / 2) - bras.w / 2;
    bras.y = y_pos - bras.h;
    SDL_SetRenderDrawColor(renderer,
                           255, 255, 255, // mode Red, Green, Blue (tous dans 0..255)
                           255);          // 0 = transparent ; 255 = opaque
    SDL_RenderFillRect(renderer, &bras);

    /****** tshirt *********/
    tshirt.w = LARGEUR_FENETRE / 40;
    tshirt.h = bras.h;
    tshirt.x = x_pos;
    tshirt.y = y_pos - tshirt.h;
    SDL_SetRenderDrawColor(renderer,
                           0, 0, 255, // mode Red, Green, Blue (tous dans 0..255)
                           255);      // 0 = transparent ; 255 = opaque
    SDL_RenderFillRect(renderer, &tshirt);

    /****** tete *********/
    tete.w = jambe.w;
    tete.h = jambe.w;
    tete.x = x_pos;
    tete.y = y_pos - tshirt.h - tete.h;
    SDL_SetRenderDrawColor(renderer,
                           255, 255, 255, // mode Red, Green, Blue (tous dans 0..255)
                           255);          // 0 = transparent ; 255 = opaque
    SDL_RenderFillRect(renderer, &tete);

    SDL_SetRenderDrawColor(renderer,
                           0, 0, 0, // mode Red, Green, Blue (tous dans 0..255)
                           255);    // 0 = transparent ; 255 = opaque
}
