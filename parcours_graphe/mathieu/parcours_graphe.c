#include "parcours_graphe.h"

int main_parcours_graphe()
{

    return 0;
}

void dijkstra_init(int r, int distance[N], int parent[N])
{
    for (int i = 0; i < N; ++i)
    {
        distance[i] = -1; //+infini +oo
        parent[i] = -1;
    }
    parent[r] = 0;
    distance[r] = 0;
}

void relachement(int u, int v, int p_u_v, int distance[N], int parent[N], tas_binaire_t *tas)
{
    if (distance[v] == -1 || distance[v] > distance[u] + p_u_v)
    {
        distance[v] = distance[u] + p_u_v;
        parent[v] = u;

        couple_t val_couple;
        val_couple.d = distance[v];
        val_couple.n = v;
        if (tas->indice_tas[v] == -1)
        {
            ajouter_elt(tas, val_couple);
        }
        else if (tas->indice_tas[v] != -2)
            diminuer_cle(tas, val_couple);
    }
}

void dijkstra(graph_l_arete_t *graph, int r, int distance[N], int parent[N])
{
    dijkstra_init(r, distance, parent);
    tas_binaire_t *file;
    couple_t *pt_tas = (couple_t *)malloc(sizeof(couple_t));
    pt_tas->d = 0;
    pt_tas->n = r;
    graph_l_arete_t *graph_copie;
    graph_copie = copie_graph(graph);

    file = creer_tas_b(*pt_tas);

    int u;
    int v;
    int p_u_v;

    while (file->nb_elt != 0)
    {
        pt_tas = retirer_elt(file);
        for (int k = 0; k < graph_copie->nb_arete; ++k)
        {

            u = graph_copie->liste_arete[k].a;
            v = graph_copie->liste_arete[k].b;
            p_u_v = graph_copie->liste_arete[k].poids;

            if (pt_tas->n == u)
            {
                relachement(u, v, p_u_v, distance, parent, file);
                //graph_copie->nb_arete--;
            }
            else if (pt_tas->n == v)
            {
                relachement(v, u, p_u_v, distance, parent, file);
                //graph_copie->nb_arete--;
            }
        }
    }
    //liberer_graph_arete(graph_copie);
}

graph_l_arete_t *copie_graph(graph_l_arete_t *graph)
{
    graph_l_arete_t *copie;
    copie = (graph_l_arete_t *)malloc(sizeof(graph));
    if (copie)
    {
        copie->liste_arete = (arete_t *)malloc(sizeof(arete_t) * graph->nb_arete);
        if (copie->liste_arete)
        {
            copie->nb_noeud = graph->nb_noeud;
            copie->nb_arete = graph->nb_arete;
            for (int k = 0; k < graph->nb_arete; ++k)
                copie->liste_arete[k] = graph->liste_arete[k];
        }
    }
    return copie;
}

void dessiner_dijkstra(SDL_Window *window, SDL_Renderer *renderer, int map[NB_LIGNE_LABY][NB_COLONNE_LABY],
                       int chemin_list[N], int taille_chemin)
{
    SDL_Rect rectangle;
    int i_k, j_k;
    int k = 0;
    int i = 0;
    rectangle.w = LARGEUR_CASE - 2;
    rectangle.h = HAUTEUR_CASE - 2;

    while (i < taille_chemin)
    {
        k = chemin_list[taille_chemin - i];
        i++;
        dessiner(window, renderer, map);
        i_k = k / NB_COLONNE_LABY;
        j_k = k % NB_COLONNE_LABY;
        //printf("k=%d, i=%d,  j=%d\n", k, i_k, j_k);
        SDL_SetRenderDrawColor(renderer, 250, 0, 0, 255);
        rectangle.x = j_k * LARGEUR_CASE + 1;
        rectangle.y = i_k * HAUTEUR_CASE + 1;

        //printf("x=%d, y=%d\n", rectangle.x, rectangle.y);

        SDL_RenderFillRect(renderer, &rectangle);

        SDL_RenderPresent(renderer);
        SDL_Delay(500);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
}

int chemin(graph_l_arete_t *graph, int sourc, int dest, int chemin_list[N])
{
    int distance[N];
    int parent[N];

    int taille_chemin = 0;
    int k = dest;
    dijkstra(graph, sourc, distance, parent);
    affficher_tab(parent, N);
    while (k != sourc)
    {
        chemin_list[taille_chemin] = k;
        //printf("k=%d  chemin_l[]=%d\n",k, chemin_list[taille_chemin]);
        k = parent[k];
        taille_chemin++;
    }

    return taille_chemin - 1;
}