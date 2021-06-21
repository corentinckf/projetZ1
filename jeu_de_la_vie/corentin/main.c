#include "util_sdl.h"

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 1000
#define MATCOL 100
#define MATLIG 100
#define TAILLE_PIXEL 10
#define TAILLE_PIXEL2 5
#define NOM_FENETRE "Jeu de la vie corentin"

#define TAUXDEFECONDITE 3

typedef int Grille[MATCOL][MATLIG];

/*règle Gems*/

int survie[9] = {0,0,0,1,1,1,0,1,0};
int naissance[9] = {0,0,0,0,1,1,1,0,1};

int cube_l = HAUTEUR_FENETRE / MATLIG;
int cube_h = LARGEUR_FENETRE / MATCOL;

int num_voisins(Grille grille, int x, int y)
{
    int res = 0;
    for(int i = -1; i < 2;++i)
        for(int j = -1;j < 2 ;++j)
            res += grille[(x + i + MATLIG) % MATLIG][(y + j + MATCOL) % MATCOL];
    return res -= grille[x][y];
}

void next(Grille grille, Grille next)
{
    for(int i = 0; i < MATLIG;++i)
    {
        for(int j = 0; j < MATCOL;++j)
        {
            int neigh = num_voisins(grille,i,j);
            int actual = grille[i][j];
            if(actual) next[i][j] = survie[neigh];
            else next[i][j] = naissance[neigh];
        }
    }
}

void draw(SDL_Renderer* renderer, Grille grille)
{
       SDL_Rect rectangle;
        int i,j;
       for(i = 0; i < MATLIG;++i)
       {
        for(j = 0; j < MATCOL;++j)
            {
                if (grille[i][j]==0)
                {
                    SDL_SetRenderDrawColor(renderer,                                
                    255, 255, 255,
                    255);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer,                                
                                        rand() % 200, rand() % 200, rand() % 200,                               
                                        255);                                 
                }
                rectangle.x= j*cube_l;
                rectangle.y= i*cube_h;
                rectangle.w= cube_l;
                rectangle.h= cube_h;
                SDL_RenderFillRect(renderer,&rectangle);
           }
       }
}   

void placement_cellule_souris(int grille[MATLIG][MATCOL], int x_m, int y_m)
{
    int i = y_m / TAILLE_PIXEL;
    int j = x_m / TAILLE_PIXEL;
    if (i >= 0 && i < MATLIG)
    {
        if (j >= 0 && j < LARGEUR_FENETRE)
            grille[i][j] = !grille[i][j];
    }
}

int main(int argc, char **argv)
{
    int code_retour_sdl;

    int fait = 0;
    int step = 100;
    Grille g;
    Grille n;
    
    SDL_Window * window = initWindow(LARGEUR_FENETRE,
                                     HAUTEUR_FENETRE,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     NOM_FENETRE);
    SDL_Renderer * renderer;
    SDL_DisplayMode screen;

    SDL_GetCurrentDisplayMode(0, &screen);
    
    if(window == NULL) end_sdl(0,
     "ERROR WINDOW CREATION",
     window,
     renderer,
     &code_retour_sdl
    );

    renderer = SDL_CreateRenderer(
           window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL)
    end_sdl(0,
     "ERROR RENDERER CREATION",
     window,
     renderer,
     &code_retour_sdl
    );

    /*Init remplissement de départ*/
    srand(time(NULL));
    for(int i = 0; i < MATLIG;++i)
    {
        for(int j = 0; j < MATCOL;++j)
        {
            /*int randint = rand() % 10;
            if(randint < TAUXDEFECONDITE)
                g[i][j] = 1;
            else*/
                g[i][j] = 0;
        }
            
    }
        

    for(int i = 0; i < MATLIG;++i)
        for(int j = 0; j < MATCOL;++j)
            n[i][j] = g[i][j];

    Grille *pg = &g;
    Grille *pn = &n;

    for(int a = 0; a < step;++a)
    {
        

    }
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
                    srand(time(NULL));
                    for(int i = 0; i < MATLIG;++i)
                    {
                        for(int j = 0; j < MATCOL;++j)
                        {
                            int randint = rand() % 10;
                            if(randint < TAUXDEFECONDITE)
                                g[i][j] = 1;
                            else
                                g[i][j] = 0;
                        }
                            
                    }
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (paused && SDL_GetMouseState(&x_mouse, &y_mouse) & SDL_BUTTON(SDL_BUTTON_LEFT))
                { // Si c'est un click gauche
                    placement_cellule_souris(g, x_mouse, y_mouse);
                }
                break;
            default:
                break;
            }
        }
        draw(renderer,*pg);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer,0, 0, 0,255);

        if (!paused)
        { // Si on n'est pas en pause
            
            SDL_RenderClear(renderer);
            
            next(*pg,*pn);
            Grille *ptemp = pg;
            pg = pn;
            pn = ptemp;
        }
        SDL_Delay(10); // Petite pause
    }
    end_sdl(1,"Normal ending", window, renderer, &code_retour_sdl);

    if(code_retour_sdl == -1) exit(EXIT_FAILURE);

    return 0;
}

