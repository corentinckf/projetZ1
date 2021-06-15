#include "util_sdl.h"

#define LARGEUR_FENETRE 400
#define HAUTEUR_FENETRE 300
#define NOM_FENETRE "Fenêtre"

int main(int argc, char **argv)
{
    SDL_Window * window = initWindow(LARGEUR_FENETRE,
                                     HAUTEUR_FENETRE,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     NOM_FENETRE);
    if(!test_fenetre(window)) exit(EXIT_FAILURE);

    SDL_Delay(10000);
    SDL_Quit();
    return 0;
}