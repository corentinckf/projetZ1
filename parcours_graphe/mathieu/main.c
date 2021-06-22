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

    /*
    //generation graph couple
    graph_couple_t *graph = NULL;
    graph = init_graph_couple_en_grille();
    graphviz_affiche_graph_couple(graph);

    melange_fisher_yates_arete(graph);

    float p = 0.05;

    graph_couple_t *quasi_arbre = NULL;
    quasi_arbre = calcul_quasi_foret_couvrant(graph, p);
    graphviz_affiche_graph_couple(quasi_arbre);

    int map[NB_LIGNE_LABY][NB_COLONNE_LABY];
    construire_map(map, quasi_arbre);

    liberer_graph_couple(graph);
    liberer_graph_couple(quasi_arbre);

    //main_labyrinthe(map);
    //dessiner(window, renderer, map);

    play_texture_mur(window, renderer, map);
    SDL_RenderPresent(renderer);
*/

    main_parcours_graphe();

    SDL_Delay(5000);

    end_sdl(1, "fin normal", window, renderer);
    return 0;
}