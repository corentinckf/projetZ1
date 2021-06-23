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

//void dijkstra(graph_l_arete_t *graph,  int r, int distance[N], int parent[N])
void dijkstra(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int r, int distance[N], int parent[N])
{
    /*
    graph_l_arete_t *graph_copie;
    graph_copie = copie_graph(graph);
*/
    dijkstra_init(r, distance, parent);
    tas_binaire_t *file;
    couple_t *pt_tas = (couple_t *)malloc(sizeof(couple_t));
    pt_tas->d = 0;
    pt_tas->n = r;
    file = creer_tas_b(*pt_tas);

    int i_pt_tas, j_pt_tas;
    unsigned mur;

    while (file->nb_elt != 0)
    {
        pt_tas = retirer_elt(file);
        i_pt_tas = pt_tas->n / NB_COLONNE_LABY;
        j_pt_tas = pt_tas->n % NB_COLONNE_LABY;

        mur = (unsigned)map[i_pt_tas][j_pt_tas];

        if ((pt_tas->n + 1) % NB_COLONNE_LABY != 0 && !(mur & (unsigned)mur_est))
        {
            relachement(pt_tas->n, pt_tas->n + 1, 1, distance, parent, file);
            // printf("%d,%d\n", pt_tas->n, pt_tas->n + 1);
        }
        if (pt_tas->n - 1 > 0 &&  !(mur & (unsigned)mur_ouest))
        {
            relachement(pt_tas->n, pt_tas->n - 1, 1, distance, parent, file);
            // printf("%d,%d et mur %d et murOuest %d\n", pt_tas->n, pt_tas->n - 1, mur, mur_ouest);
        }
        if (pt_tas->n - NB_COLONNE_LABY > 0 && !(mur & (unsigned)mur_nord))
        {
            relachement(pt_tas->n, pt_tas->n - NB_COLONNE_LABY, 1, distance, parent, file);
            // printf("%d,%d\n", pt_tas->n, pt_tas->n - NB_COLONNE_LABY);
        }
        if (pt_tas->n + NB_COLONNE_LABY < N && !(mur & (unsigned)mur_sud))
        {
            relachement(pt_tas->n, pt_tas->n + NB_COLONNE_LABY, 1, distance, parent, file);
            // printf("%d,%d\n", pt_tas->n, pt_tas->n + NB_COLONNE_LABY);
        }

        /*
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
        */
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
    SDL_Rect rect_sourc;
    SDL_Rect rect_dest;

    int i_k, j_k;
    int k;
    int i = 0;
    rectangle.w = LARGEUR_CASE - 2;
    rectangle.h = HAUTEUR_CASE - 2;

    rect_dest.w = rectangle.w;
    rect_dest.h = rectangle.h;
    rect_sourc.w = rectangle.w;
    rect_sourc.h = rectangle.h;

    rect_dest.x = (chemin_list[0] % NB_COLONNE_LABY) * LARGEUR_CASE + 1;
    rect_dest.y = (chemin_list[0] / NB_COLONNE_LABY) * HAUTEUR_CASE + 1;

    rect_sourc.x = (chemin_list[taille_chemin - 1] % NB_COLONNE_LABY) * LARGEUR_CASE + 1;
    rect_sourc.y = (chemin_list[taille_chemin - 1] / NB_COLONNE_LABY) * HAUTEUR_CASE + 1;

    while (i < taille_chemin)
    {
        k = chemin_list[taille_chemin - 1 - i];
        i++;
        dessiner(window, renderer, map);

        i_k = k / NB_COLONNE_LABY;
        j_k = k % NB_COLONNE_LABY;
        //printf("k=%d, i=%d,  j=%d\n", k, i_k, j_k);
        rectangle.x = j_k * LARGEUR_CASE + 1;
        rectangle.y = i_k * HAUTEUR_CASE + 1;

        //printf("x=%d, y=%d\n", rectangle.x, rectangle.y);

        SDL_SetRenderDrawColor(renderer, 250, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect_sourc);
        SDL_SetRenderDrawColor(renderer, 0, 250, 0, 255);
        SDL_RenderFillRect(renderer, &rect_dest);

        SDL_SetRenderDrawColor(renderer, 0, 0, 250, 255);
        SDL_RenderFillRect(renderer, &rectangle);

        SDL_RenderPresent(renderer);
        SDL_Delay(50);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
}

int chemin(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int sourc, int dest, int chemin_list[N])
{
    int distance[N];
    int parent[N];

    int taille_chemin = 0;
    int k = dest;
    dijkstra(map, sourc, distance, parent);
    //affficher_tab(parent, N);
    while ( k != sourc)
    {
        chemin_list[taille_chemin] = k;
        k = parent[k];
        taille_chemin++;
    }
    chemin_list[taille_chemin] = sourc;
    taille_chemin++;
    // printf("Chemin de %d a %d de taille %d\n", sourc, dest, taille_chemin);
    // printf("taille_chemin=%d  chemin_l[]=\n", taille_chemin);
    // affficher_tab(chemin_list, taille_chemin);
    return taille_chemin;
}