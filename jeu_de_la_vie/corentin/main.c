#include "util_sdl.h"

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 500
#define MATCOL 100
#define MATLIG 50
#define NOM_FENETRE "Jeu de la vie corentin"

#define TAUXDEFECONDITE 5

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
                                        0, 0, 0,                               
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

int main(int argc, char **argv)
{
    int code_retour_sdl;

    int fait = 0;
    int step = 50;
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
            int randint = rand() % 10;
            if(randint < TAUXDEFECONDITE)
                g[i][j] = 1;
            else
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
        draw(renderer,*pg);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        SDL_SetRenderDrawColor(renderer,0, 0, 0,255);
        SDL_RenderClear(renderer);
        
        next(*pg,*pn);
        Grille *ptemp = pg;
        pg = pn;
        pn = ptemp;

    }
    end_sdl(1,"Normal ending", window, renderer, &code_retour_sdl);

    if(code_retour_sdl == -1) exit(EXIT_FAILURE);

    return 0;
}