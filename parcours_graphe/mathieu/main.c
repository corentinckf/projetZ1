#include "const.h"

int main()
{
    srand(GRAINE);


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

    //generation graph arete
    graph_l_arete_t *graph = NULL;
    graph = init_graph_arete_en_grille();
    graphviz_affiche_graph_arete(graph);

    melange_fisher_yates_arete(graph);

    float p = 0.05 ;

    graph_l_arete_t *quasi_arbre = NULL;
    quasi_arbre = calcul_quasi_foret_couvrant(graph, p);
    graphviz_affiche_graph_arete(quasi_arbre);

    int map[NB_LIGNE_LABY][NB_COLONNE_LABY];
    construire_map(map, quasi_arbre);

    //main_labyrinthe(map);
    //dessiner(window, renderer, map);
    int sourc = 0;
    int dest = 22;
    int distance[N];
    int parent[N];

    dijkstra(quasi_arbre, sourc, distance, parent);


    printf("parent : ");
    affficher_tab(parent, N);
    printf("distance : ");
    affficher_tab(distance, N);
    printf("\n");




    //dessiner(window, renderer, map);
    //play_texture_mur(window, renderer, map);
    dessiner_dijkstra(window, renderer,map, distance, parent, sourc, dest);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);

    liberer_graph_arete(graph);
    liberer_graph_arete(quasi_arbre);

    end_sdl(1, "fin normal", window, renderer);
    return 0;
}