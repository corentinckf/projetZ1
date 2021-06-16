#include "util_sdl.h"

SDL_Window * initWindow(int width, int height,int x_pos, int y_pos, char * window_name)
{
    SDL_Window * window;

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
        window_name,                       // window title
        x_pos,                             // initial x position
        y_pos,                             // initial y position
        width,                               // width, in pixels
        height,                               // height, in pixels
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Error : Window initialisation - %s\n", SDL_GetError());
        window = NULL;
    }

    return window;

}

void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                  char const* msg,                                    // message à afficher
                  SDL_Window* window,                                 // fenêtre à fermer
                  SDL_Renderer* renderer,
                  int * code_retour) {                           // renderer à fermer
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
      *code_retour = -1;                                                                                           
  }                                                               
}  

int test_fenetre(SDL_Window *fenetre)
{
    int code_retour = 1;
    if (fenetre == NULL)
    {
        SDL_Log("Error : SDL Window creation - %s\n", SDL_GetError()); // échec de la création de la fenêtre
        SDL_Quit();
        code_retour = 0;
    }
    return code_retour;
}

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture
    int code_retour;

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer, &code_retour);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer, &code_retour);

    return my_texture;
  }

void draw_texture(SDL_Texture *my_texture, SDL_Window *window,
                    SDL_Renderer *renderer, float zm, float cordx, float cordy) {
    SDL_Rect 
    source = {0},                      // Rectangle définissant la zone de la texture à récupérer
    destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);  // Récupération des dimensions de l'image

    float zoom = zm;                        // Facteur de zoom à appliquer    
    destination.w = source.w * zoom;         // La destination est un zoom de la source
    destination.h = source.h * zoom;         // La destination est un zoom de la source
    destination.x = cordx;
    destination.y = cordy;
        
    SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                &source,
                &destination);            
    //SDL_RenderPresent(renderer);             
    //SDL_Delay(1000);                         

    SDL_RenderClear(renderer);               // Effacer la fenêtre
}

