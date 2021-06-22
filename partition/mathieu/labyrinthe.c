#include "labyrinthe.h"

int main()
{
    //main_kruskal();

    //generation graph couple
    graph_couple_t *graph = NULL;
    graph = init_graph_couple_en_grille();
    graphviz_affiche_graph_couple(graph);

    melange_fisher_yates_arete(graph);

    //en calculer une forêt couvrante de poids minimal
    graph_couple_t *arbre_couvrant = NULL;
    arbre_couvrant = calcul_foret_couvrant(graph);
    graphviz_affiche_graph_couple(arbre_couvrant);

    liberer_graph_couple(graph);
    liberer_graph_couple(arbre_couvrant);

    return 0;
}

int main_labyrinthe()
{
    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Rect window_dimensions = {0};

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w, screen.h);

    /************** creation window ****************/
    window = SDL_CreateWindow(
        "Labyrinthe",
        (screen.w - LARGEUR_FENETRE) / 2, (screen.h - HAUTEUR_FENETRE) / 2,
        LARGEUR_FENETRE, HAUTEUR_FENETRE,
        0);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    /************** creation renderer ****************/
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /**
 * 
 * 
 * 
 * 
 */

    SDL_Delay(2000);

    end_sdl(1, "fin normal", window, renderer);
    return 0;
}

void permute_a_b(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void melange_fisher_yates_arete(graph_couple_t *graph)
{
    srand(48);
    //srand(time(NULL));

    int j;
    for (int i = graph->nb_arete - 1; i >= 1; --i)
    {
        j = rand() % i + 1;
        permute_a_b(&graph->liste_couple[i].a, &graph->liste_couple[j].a);
        permute_a_b(&graph->liste_couple[i].b, &graph->liste_couple[j].b);
    }
}

void construire_map(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], graph_couple_t *graph)
{
    int a, b;
    int i_a, j_a;
    int i_b, j_b;

    for (int i = 0; i < NB_LIGNE_LABY; ++i)
        for (int j = 0; j < NB_COLONNE_LABY; ++j)
            map[i][j] = 15; //full mur

    for (int k = 0; k < graph->nb_arete; ++k)
    {
        a = graph->liste_couple[k].a;
        b = graph->liste_couple[k].b;

        i_a = a / NB_COLONNE_LABY;
        j_a = a % NB_COLONNE_LABY;
        i_b = b / NB_COLONNE_LABY;
        j_b = b % NB_COLONNE_LABY;
        switch (a - b)
        {
        case -1:                //arete a--b
            map[i_a][j_a] -= 1; //a mur droite
            map[i_b][j_b] -= 4; //b mur gauche
            break;
        case 1:                 //arete b--a
            map[i_a][j_a] -= 4; //a mur gauche
            map[i_b][j_b] -= 1; //b mur droite
            break;
        case -NB_COLONNE_LABY:  //a -|- b
            map[i_a][j_a] -= 8; //a mur bas
            map[i_b][j_b] -= 2; //b mur haut
            break;
        case NB_COLONNE_LABY:   //b -|- a
            map[i_a][j_a] -= 2; //a mur haut
            map[i_b][j_b] -= 8; //b mur bas
            break;
        default:
            printf("bizarre tu devrais pas aller ici\n");
            break;
        }
    }
}

void dessiner(SDL_Window *window, SDL_Renderer *renderer, int map[NB_LIGNE_LABY][NB_COLONNE_LABY])
{
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 400;
    rectangle.h = 400;

    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer,
                       0, 0,      // x,y du point de la première extrémité
                       400, 400); // x,y seconde extrémité

    for (int i = 0; i < NB_COLONNE_LABY; ++i)
        for (int j = 0; j < NB_LIGNE_LABY; ++j)
            trace_mur(window, renderer,map, i, j);
}

void trace_mur(SDL_Window *window, SDL_Renderer *renderer, int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int i, int j)
{
}

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{ // renderer à fermer
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

    IMG_Quit();
    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}