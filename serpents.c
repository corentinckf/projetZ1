#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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

void draw(SDL_Renderer* renderer, int *x, int *nb)                                   // Je pense que vous allez faire moins laid :)
{
       SDL_Rect rectangle;
       int y=600/2-100*(*nb%2);
       
       if (*nb %2 == 0)
       {
              SDL_SetRenderDrawColor(renderer,                                
              0, 0, 100,                               // mode Red, Green, Blue (tous dans 0..255)
              255);                                   // 0 = transparent ; 255 = opaque
       }
       else
       {
              SDL_SetRenderDrawColor(renderer,                                
                                   200, 0, 0,                               // mode Red, Green, Blue (tous dans 0..255)
                                   255);                                   // 0 = transparent ; 255 = opaque
       }
       
       rectangle.x=*x;
       rectangle.y=y;
       rectangle.w=100;
       rectangle.h=100;
       SDL_RenderFillRect(renderer,&rectangle);

       SDL_RenderDrawLine(renderer,
                            *x, y,                                       // x,y du point de la première extrémité
                            *x+100, y+100);                              // x,y seconde extrémité


       /* tracer un cercle n'est en fait pas trivial, voilà le résultat sans algo intelligent ... */
       /*  for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
       {      
       SDL_SetRenderDrawColor(renderer,
                            (cos(angle * 2) + 1) * 255 / 2,       // quantité de Rouge      
                            (cos(angle * 5) + 1) * 255 / 2,       //          de vert 
                            (cos(angle) + 1) * 255 / 2,           //          de bleu
                            255);                                 // opaque
       SDL_RenderDrawPoint(renderer, 
                            200 + 100 * cos(angle),                  // coordonnée en x
                            200 + 150 * sin(angle));                 //            en y   
       }*/
}

int main()
{
       SDL_Window* window = NULL;
       SDL_Renderer* renderer = NULL;
       int i;
       int x=0;
       int nb;
       window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 600,
                            600,
                            SDL_WINDOW_OPENGL);
       if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

       renderer = SDL_CreateRenderer(
              window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
       if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

       SDL_SetRenderDrawColor(renderer,                                
              0, 0, 0,                               // mode Red, Green, Blue (tous dans 0..255)
              255);                                   // 0 = transparent ; 255 = opaque
       
       for (i=0;i<6;i++)
       {
              draw(renderer,&x,&nb);
              SDL_RenderPresent(renderer);
              SDL_Delay(1000);
              SDL_SetRenderDrawColor(renderer,                                
                                          0, 0, 0,                               // mode Red, Green, Blue (tous dans 0..255)
                                          255);                                  // 0 = transparent ; 255 = opaque
              SDL_RenderClear(renderer);
              x+=100;
              nb++;
       } 
       end_sdl(1, "Normal ending", window, renderer);
       return EXIT_SUCCESS;
}