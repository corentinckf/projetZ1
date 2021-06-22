#include "labyrinthe.h"

int main()
{
    //main_kruskal();

    //generation graph couple
    graph_couple_t *graph = NULL;
    graph = init_graph_couple_alea();
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