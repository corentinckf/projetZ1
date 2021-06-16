#include "util_sdl.h"

#define LARGEUR_FENETRE 500
#define HAUTEUR_FENETRE 300
#define MATCOL 50
#define MATLIG 30
#define NOM_FENETRE "Fenêtre"

/*règle Maze*/
int survie[9] = {0,0,0,0,0,1,0,0,0};
int naissance[9] = {0,0,0,0,0,1,1,0,0};

int cube_l = HAUTEUR_FENETRE / MATLIG;
int cube_h = LARGEUR_FENETRE / MATCOL;

int keskeJeDeviens(int grille[MATLIG][MATCOL], int * i, int  * j)
{
    int res = -1;
    int nb_neigh = num_voisins(grille,*i,*j);
    if(grille[*i][*j] == 1){
        res = survie[nb_neigh];
    }else{
        res = naissance[nb_neigh];
    }
    return res;
}

int num_voisins(int grille[MATLIG][MATCOL], int x, int y)
{
    int i, j;
    int res = 0;
    for (i = -1; i < 2; i++)
        for (j = -1; j < 2; j++)
        {
            res+= grille[(y + j + MATLIG) % MATLIG][(x + j   + MATCOL) % MATCOL];
        }

    res -= grille[y][x];

    return res;
}

void draw(SDL_Renderer* renderer, int tamer[MATLIG][MATCOL])
{
       SDL_Rect rectangle;
        int i,j;
       for(i = 0; i < MATLIG;++i)
       {
        for(j = 0; j < MATCOL;++j)
            {
                if (tamer[i][j]==0)
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
    int step = 100;
    int grille[MATLIG][MATCOL];
    int neigh[MATLIG][MATCOL];
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
        for(int j = 0; j < MATCOL;++j)
            grille[i][j] = rand() % 2;

    for(int i = 0; i < MATLIG;++i)
        for(int j = 0; j < MATCOL;++j)
            neigh[i][j] = grille[i][j];

    for(int a = 0; a < step;++a)
    {
        draw(renderer,neigh);
        SDL_RenderPresent(renderer);
        SDL_Delay(250);
        SDL_SetRenderDrawColor(renderer,0, 0, 0,255);
        SDL_RenderClear(renderer);
        
        //On check les cellules qui vont rester/pas
        for(int i = 0; i < MATLIG;++i)
        {
            for(int j = 0; j < MATCOL;++j)
            {
                neigh[i][j] = keskeJeDeviens(grille,&i,&j);
            }
        }
    }
    end_sdl(1,"Normal ending", window, renderer, &code_retour_sdl);

    if(code_retour_sdl == -1) exit(EXIT_FAILURE);

    return 0;
}