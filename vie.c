#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//taille de la grille
#define LIGNES 30
#define COLONNES 50

//le tableau survie est rempli de 0 et 1 : si survie[k]=1, alors la cellule survit et 0 sinon
int survie[9] = {0,1,0,1,0,0,0,1,1};
int naissance[9] = {1,0,1,0,1,1,1,0,0};

//on construit les tableaux survie et naissance aléatoirement
/*int k;

for (k=0;k<9;k++)
{
    survie[k]=rand()%2;
    naissance[k]=rand()%2;
}*/

//on construit les tableaux survie et naissance selon la regle donnée par ScienceEtonnante
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

void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                  char const* msg,                                    // message à afficher
                  SDL_Window* window,                                 // fenêtre à fermer
                  SDL_Renderer* renderer) {                           // renderer à fermer
       char msg_formated[255];                                         
       int l;                                                          

       if (!ok) {                                                      
              strncpy(msg_formated, msg, 250);                                 
              l = strlen(msg_formated);
              strcpy(msg_formated + l, " : %s\n");                     

              SDL_Log(msg_formated, SDL_GetError());                   
       }                                                               

       if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
       if (window != NULL)   SDL_DestroyWindow(window);                                        

       SDL_Quit();                                                     

       if (!ok) {                                                      
              exit(EXIT_FAILURE);                                              
       }                                                               
}

//retourne 1 si la cellule survit et 0 si elle meurt
int devenir(int mat[LIGNES][COLONNES], int *i, int *j)
{
    int s=0;
    int ligne,colonne;
    int resultat=-1; //la valeur -1 indique une erreur

    for (ligne = ((*i)-1 + LIGNES) % LIGNES ; ligne < ((*i)+2) % LIGNES ; ligne++)
    {
        for (colonne = ((*j)-1 + COLONNES) % COLONNES ; colonne < ((*j)+2) % COLONNES ; colonne++)
        {
            s+=mat[ligne][colonne];
        }
    }
    s-=mat[*i][*j];
    //s est la somme des 8 cases entourant la cellule (i,j), s est donc le nombre de voisins de la cellule

    if (mat[*i][*j] == 1)   //cellule en vie
    {
        resultat = survie[s];
    }
    else        //cellule morte
    {
        resultat = naissance[s];
    }
    return resultat;    
}

//evolution de l'etat N à l'etat N+1 ; renvoie l'entier changement qui indique s'il y a eu un changement de l'etat n à n+1 ou pas
int evolution(int mat[LIGNES][COLONNES], int matsuiv[LIGNES][COLONNES])
{
    int changement=0,resultat;
    int ligne=0,colonne=0;
    int i,j;

    while (ligne < LIGNES && changement == 0)
    {
        while (colonne < COLONNES && changement == 0)
        {
            resultat=devenir(mat,&ligne,&colonne);
            if (resultat < 0)
            {
                fprintf(stderr,"probleme d'evolution");
            }
            else
            {
                matsuiv[ligne][colonne] = resultat;
                if (mat[ligne][colonne] != matsuiv[ligne][colonne])
                {
                    changement=1;
                }
            }
            colonne++; 
        }
        ligne++;
    }

    for (j=colonne;j<COLONNES;j++)
    {
        resultat=devenir(mat,&ligne,&j);
        if (resultat < 0)
        {
            fprintf(stderr,"probleme d'evolution");
        }
        else
        {
            matsuiv[ligne][j] = resultat;
        }
    }

    for (i=ligne+1;i<LIGNES;i++)
    {
        for (j=0;j<COLONNES;j++)
        {
            resultat=devenir(mat,&i,&j);
            if (resultat < 0)
            {
                fprintf(stderr,"probleme d'evolution");
            }
            else
            {
                matsuiv[i][j] = resultat;
            }
        }
    }
    return changement;
}

void draw(SDL_Renderer* renderer, int mat[LIGNES][COLONNES], int *h, int *l)
{
       SDL_Rect rectangle;
       int i,j;
       
       for (i=0;i<LIGNES;i++)
       {
           for (j=0;j<COLONNES;j++)
           {
                if (mat[i][j] == 0)     //cellule morte : en blanc
                {
                        SDL_SetRenderDrawColor(renderer,                                
                        255, 255, 255,                               // mode Red, Green, Blue (tous dans 0..255)
                        255);                                   // 0 = transparent ; 255 = opaque
                }
                else                    //cellule en vie : en noir
                {
                        SDL_SetRenderDrawColor(renderer,                                
                                            0, 0, 0,                               // mode Red, Green, Blue (tous dans 0..255)
                                            255);                                   // 0 = transparent ; 255 = opaque
                }
                rectangle.x=j*(*l);
                rectangle.y=i*(*h);
                rectangle.w=*l;
                rectangle.h=*h;
                SDL_RenderFillRect(renderer,&rectangle);
           }
       }
}

int main()
{
    int etat_n[LIGNES][COLONNES];
    int etat_suiv[LIGNES][COLONNES];
    int changement=1;
    int ligne=0,colonne=0;
    int i,j;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    window = SDL_CreateWindow("Jeu de la vie",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED, 600,
                        600,
                        SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    //SDL_GetWindowSize(window,&largeur_ecran,&hauteur_ecran);

    int hauteur_pixel = 600 / LIGNES;
    int largeur_pixel = 1000 / COLONNES;

    renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    SDL_SetRenderDrawColor(renderer,                                
            0, 0, 0,                               // mode Red, Green, Blue (tous dans 0..255)
            255);                                   // 0 = transparent ; 255 = opaque

    //initialisation aléatoire
    for (i=0;i<LIGNES;i++)
    {
        for (j=0;j<COLONNES;j++)
        {
            etat_n[i][j] = rand()%2;
        }
    }

    draw(renderer,etat_n, &hauteur_pixel, &largeur_pixel);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    SDL_SetRenderDrawColor(renderer,0, 0, 0,255);
    SDL_RenderClear(renderer);

    for (int cpt=0; cpt<10; cpt++)
    {
        //afficher l'etat n
        draw(renderer,etat_n, &hauteur_pixel, &largeur_pixel);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        SDL_SetRenderDrawColor(renderer,0, 0, 0,255);
        SDL_RenderClear(renderer);

        //afficher l'etat n+1
        draw(renderer,etat_suiv, &hauteur_pixel, &largeur_pixel);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        SDL_SetRenderDrawColor(renderer,0, 0, 0,255);
        SDL_RenderClear(renderer);

        //recopie de la matrice etat n+1 dans la matrice etat_n
        for (i=0;i<LIGNES;i++)
        {
            for (j=0;j<COLONNES;j++)
            {
                etat_n[i][j] = etat_suiv[i][j];
            }
        }
        changement = evolution(etat_n,etat_suiv);
    }

    return 0;
}