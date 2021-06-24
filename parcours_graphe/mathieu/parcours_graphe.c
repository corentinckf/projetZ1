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
            relachement(pt_tas->n, pt_tas->n + 1, 1, distance, parent, file);

        if (pt_tas->n - 1 > 0 && !(mur & (unsigned)mur_ouest))
            relachement(pt_tas->n, pt_tas->n - 1, 1, distance, parent, file);

        if (pt_tas->n - NB_COLONNE_LABY > 0 && !(mur & (unsigned)mur_nord))
            relachement(pt_tas->n, pt_tas->n - NB_COLONNE_LABY, 1, distance, parent, file);

        if (pt_tas->n + NB_COLONNE_LABY < N && !(mur & (unsigned)mur_sud))
            relachement(pt_tas->n, pt_tas->n + NB_COLONNE_LABY, 1, distance, parent, file);

        /* cherche les voisins en parcourant toute la liste des aretes
        for (int a = 0; k < graph_copie->nb_arete; ++k)
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

void dessiner_chemin(SDL_Window *window, SDL_Renderer *renderer, int map[NB_LIGNE_LABY][NB_COLONNE_LABY],
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
        SDL_Delay(200);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
}

int chemin_dijkstra(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int sourc, int dest, int chemin_list[N])
{
    int distance[N];
    int parent[N];

    int taille_chemin = 0;
    int k = dest;
    dijkstra(map, sourc, distance, parent);
    //affficher_tab(parent, N);
    while (k != sourc)
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

void promenade_labyrinthe_dijkstra(SDL_Window *window, SDL_Renderer *renderer)
{
    float p = 0.01;
    //generation graph arete
    graph_l_arete_t *graph = NULL;
    graph = init_graph_arete_en_grille();
    graphviz_affiche_graph_arete(graph);
    melange_fisher_yates_arete(graph);
    //Generation quasi arbre
    graph_l_arete_t *quasi_arbre = NULL;
    quasi_arbre = calcul_quasi_foret_couvrant(graph, p);
    graphviz_affiche_graph_arete(quasi_arbre);
    liberer_graph_arete(graph);

    int map[NB_LIGNE_LABY][NB_COLONNE_LABY];
    construire_map(map, quasi_arbre);
    /*
    int parent[N];
    int distance[N];

    dijkstra(map, 0, distance, parent);
    printf("parent : "); affficher_tab(parent,N);
    printf("distance : "); affficher_tab(distance,N);
*/
    int sourc = 0;
    int dest = 0;

    int chemin_list[N];
    int taille_chemin;
    int compt = 0;
    int alea;
    while (compt < 10)
    {
        sourc = dest;
        alea = rand() % quasi_arbre->nb_noeud;
        printf("alea=%d\n", alea);
        dest = alea;
        taille_chemin = chemin_dijkstra(map, sourc, dest, chemin_list);

        dessiner_chemin(window, renderer, map, chemin_list, taille_chemin);
        ++compt;
    }
    SDL_Delay(750);
    SDL_RenderPresent(renderer);
    liberer_graph_arete(quasi_arbre);
}

int d_euclidienne(int a, int b)
{
    int i_a = a / NB_COLONNE_LABY;
    int j_a = a % NB_COLONNE_LABY;
    int i_b = b / NB_COLONNE_LABY;
    int j_b = b % NB_COLONNE_LABY;
    int d = (i_a - i_b) * (i_a - i_b) + (j_a - j_b) * (j_a - j_b);
    d = (int)sqrt((double)d);
    return d;
}

int d_tchebychev(int a, int b)
{
    int i_a = a / NB_COLONNE_LABY;
    int j_a = a % NB_COLONNE_LABY;
    int i_b = b / NB_COLONNE_LABY;
    int j_b = b % NB_COLONNE_LABY;
    return MAX(abs(i_a - i_b), abs(j_a - j_b));
}

int d_manattan(int a, int b)
{
    int i_a = a / NB_COLONNE_LABY;
    int j_a = a % NB_COLONNE_LABY;
    int i_b = b / NB_COLONNE_LABY;
    int j_b = b % NB_COLONNE_LABY;
    int d = abs(i_a - i_b) + abs(j_a - j_b);
    return d;
}

void A_etoile(int (*fct_distance)(const int, const int), int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int r, int distance[N], int parent[N])
{
    dijkstra_init(r, distance, parent);
    tas_binaire_t *file;
    couple_t *pt_tas = (couple_t *)malloc(sizeof(couple_t));
    pt_tas->d = 0;
    pt_tas->n = r;
    file = creer_tas_b(*pt_tas);

    int i_pt_tas, j_pt_tas;
    int d_u_v;
    unsigned mur;

    while (file->nb_elt != 0)
    {
        pt_tas = retirer_elt(file);
        i_pt_tas = pt_tas->n / NB_COLONNE_LABY;
        j_pt_tas = pt_tas->n % NB_COLONNE_LABY;

        mur = (unsigned)map[i_pt_tas][j_pt_tas];

        if ((pt_tas->n + 1) % NB_COLONNE_LABY != 0 && !(mur & (unsigned)mur_est))
        {
            d_u_v = fct_distance(pt_tas->n, pt_tas->n + 1);
            relachement(pt_tas->n, pt_tas->n + 1, d_u_v, distance, parent, file);
        }
        if (pt_tas->n - 1 > 0 && !(mur & (unsigned)mur_ouest))
        {
            d_u_v = fct_distance(pt_tas->n, pt_tas->n - 1);
            relachement(pt_tas->n, pt_tas->n - 1, d_u_v, distance, parent, file);
        }
        if (pt_tas->n - NB_COLONNE_LABY > 0 && !(mur & (unsigned)mur_nord))
        {
            d_u_v = fct_distance(pt_tas->n, pt_tas->n - NB_COLONNE_LABY);
            relachement(pt_tas->n, pt_tas->n - NB_COLONNE_LABY, d_u_v, distance, parent, file);
        }
        if (pt_tas->n + NB_COLONNE_LABY < N && !(mur & (unsigned)mur_sud))
        {
            d_u_v = fct_distance(pt_tas->n, pt_tas->n + NB_COLONNE_LABY);
            relachement(pt_tas->n, pt_tas->n + NB_COLONNE_LABY, d_u_v, distance, parent, file);
        }
    }
}

void promenade_labyrinthe_a_etoile(SDL_Window *window, SDL_Renderer *renderer)
{
    float p = 0.01;
    //generation graph arete
    graph_l_arete_t *graph = NULL;
    graph = init_graph_arete_en_grille();
    graphviz_affiche_graph_arete(graph);
    melange_fisher_yates_arete(graph);
    //Generation quasi arbre
    graph_l_arete_t *quasi_arbre = NULL;
    quasi_arbre = calcul_quasi_foret_couvrant(graph, p);
    graphviz_affiche_graph_arete(quasi_arbre);
    liberer_graph_arete(graph);

    int map[NB_LIGNE_LABY][NB_COLONNE_LABY];
    construire_map(map, quasi_arbre);

    int sourc = 0;
    int dest = 0;

    int chemin_list[N];
    int taille_chemin;
    int compt = 0;
    int alea;
    while (compt < 10)
    {
        sourc = dest;
        alea = rand() % quasi_arbre->nb_noeud;
        printf("alea=%d\n", alea);
        dest = alea;
        taille_chemin = chemin_a_etoile(d_euclidienne, map, sourc, dest, chemin_list);

        dessiner_chemin(window, renderer, map, chemin_list, taille_chemin);
        ++compt;
    }
    SDL_Delay(1000);
    SDL_RenderPresent(renderer);
    liberer_graph_arete(quasi_arbre);
}

int chemin_a_etoile(int (*fct_distance)(const int, const int), int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int sourc, int dest, int chemin_list[N])
{
    int distance[N];
    int parent[N];

    int taille_chemin = 0;
    int k = dest;
    A_etoile(fct_distance, map, sourc, distance, parent);
    while (k != sourc)
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

void init_DFS(int couleur[N], int parent[N])
{
    for (int u = 0; u < N; ++u)
    {
        couleur[u] = 0; //Blanc
        parent[u] = -1;
    }
}

void DFS_rec(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int u,
             int couleur[N], int parent[N],
             int debut[N], int fin[N], int *temps)
{

    couleur[u] = 2; //gris
    *temps = *temps + 1;
    debut[u] = *temps;

    int i_u = u / NB_COLONNE_LABY;
    int j_u = u % NB_COLONNE_LABY;

    unsigned mur = (unsigned)map[i_u][j_u];

    if ((u + 1) % NB_COLONNE_LABY != 0 && !(mur & (unsigned)mur_est))
        if (couleur[u + 1] == 0) //blanc
        {
            {
                parent[u + 1] = u;
                DFS_rec(map, u + 1, couleur, parent, debut, fin, temps);
            }
        }
    if (u - 1 > 0 && !(mur & (unsigned)mur_ouest))
    {
        if (couleur[u - 1] == 0) //blanc
        {
            parent[u - 1] = u;
            DFS_rec(map, u - 1, couleur, parent, debut, fin, temps);
        }
    }
    if (u - NB_COLONNE_LABY > 0 && !(mur & (unsigned)mur_nord))
    {
        if (couleur[u - NB_COLONNE_LABY] == 0) //blanc
        {
            parent[u - NB_COLONNE_LABY] = u;
            DFS_rec(map, u - NB_COLONNE_LABY, couleur, parent, debut, fin, temps);
        }
    }
    if (u + NB_COLONNE_LABY < N && !(mur & (unsigned)mur_sud))
    {
        if (couleur[u + NB_COLONNE_LABY] == 0) //blanc
        {
            parent[u + NB_COLONNE_LABY] = u;
            DFS_rec(map, u + NB_COLONNE_LABY, couleur, parent, debut, fin, temps);
        }
    }
    couleur[u] = 1; //Noir
    *temps = *temps + 1;
    fin[u] = *temps;
}

void DFS_run(int map[NB_LIGNE_LABY][NB_COLONNE_LABY], int r,
             int couleur[N], int parent[N],
             int debut[N], int fin[N])
{
    int temps = 0;

    init_DFS(couleur, parent);
    DFS_rec(map, r, couleur, parent, debut, fin, &temps);
}

void promenade_parcours_en_profondeur(SDL_Window *window, SDL_Renderer *renderer)
{

    float p = 0.01;
    //generation graph arete
    graph_l_arete_t *graph = NULL;
    graph = init_graph_arete_en_grille();
    //graphviz_affiche_graph_arete(graph);
    melange_fisher_yates_arete(graph);
    //Generation quasi arbre
    graph_l_arete_t *quasi_arbre = NULL;
    quasi_arbre = calcul_quasi_foret_couvrant(graph, p);
    //graphviz_affiche_graph_arete(quasi_arbre);
    liberer_graph_arete(graph);

    int map[NB_LIGNE_LABY][NB_COLONNE_LABY];
    construire_map(map, quasi_arbre);

    int couleur[N];
    int parent[N];
    int debut[N];
    int fin[N];

    int r = 0;

    DFS_run(map, r, couleur, parent, debut, fin);
    /*
    printf("couleur : ");
    affficher_tab(couleur, N);
    printf("parent : ");
    affficher_tab(parent, N);
    printf("debut : ");
    affficher_tab(debut, N);
    printf("fin : ");
    affficher_tab(fin, N);
    */

    SDL_Rect rectangle;
    SDL_Rect rectangle_bis;

    int i_k, j_k;
    rectangle.w = LARGEUR_CASE - 2;
    rectangle.h = HAUTEUR_CASE - 2;
    rectangle_bis.w = LARGEUR_CASE - 2;
    rectangle_bis.h = HAUTEUR_CASE - 2;

    int ordre[2 * N];
    int d = 1;
    int f;
    for (int i = 0; i < N; ++i)
        ordre[i] = -1;
    for (int i = 0; i < N; ++i)
        ordre[debut[i]] = i;

    int compt = 0;
    while (compt < 2 * N)
    {
        if (ordre[compt] != -1)
        {

            rectangle_bis.x = rectangle.x;
            rectangle_bis.y = rectangle.y;
            i_k = ordre[compt] / NB_COLONNE_LABY;
            j_k = ordre[compt] % NB_COLONNE_LABY;
            rectangle.x = j_k * LARGEUR_CASE + 1;
            rectangle.y = i_k * HAUTEUR_CASE + 1;

            dessiner(window, renderer, map);
            SDL_SetRenderDrawColor(renderer, 0, 0, 250, 255);
            SDL_RenderFillRect(renderer, &rectangle_bis);

            SDL_SetRenderDrawColor(renderer, 0, 0, 250, 255);
            SDL_RenderFillRect(renderer, &rectangle);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            // SDL_RenderClear(renderer);
        }
        ++compt;
    }
    liberer_graph_arete(quasi_arbre);
}

void compare_a_etoile()
{
    float p = 0.01;
    //generation graph arete
    graph_l_arete_t *graph = NULL;
    graph = init_graph_arete_en_grille();
    //graphviz_affiche_graph_arete(graph);
    melange_fisher_yates_arete(graph);
    //Generation quasi arbre
    graph_l_arete_t *quasi_arbre = NULL;
    quasi_arbre = calcul_quasi_foret_couvrant(graph, p);
    // graphviz_affiche_graph_arete(quasi_arbre);
    liberer_graph_arete(graph);

    int map[NB_LIGNE_LABY][NB_COLONNE_LABY];
    construire_map(map, quasi_arbre);

    int distance[N];
    int parent[N];

    clock_t start_t, end_t, total_t;
    double temps_d_euclidienne;
    double temps_d_tchebychev;
    double temps_d_manattan;

    float m_e = 0.;
    float m_t = 0.;
    float m_m = 0.;

    for (int k = 0; k < 10; k++)
    {
        start_t = clock();
        printf("Debut de A_etoide avec la distance euclidienne, start_t = %ld\n", start_t);
        A_etoile(d_euclidienne, map, 0, distance, parent);
        end_t = clock();
        printf("Fin de A_etoide avec la distance euclidienne,   end_t = %ld\n", end_t);
        temps_d_euclidienne = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("A_etoide avec la distance euclidienne :         Total time taken by CPU: %f\n", temps_d_euclidienne);

        start_t = clock();
        printf("Debut de A_etoide avec la distance tchebychev,  start_t = %ld\n", start_t);
        A_etoile(d_tchebychev, map, 0, distance, parent);
        end_t = clock();
        printf("Fin de A_etoide avec la distance tchebychev,    end_t = %ld\n", end_t);
        temps_d_tchebychev = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("A_etoide avec la distance tchebychev :          Total time taken by CPU: %f\n", temps_d_tchebychev);

        start_t = clock();
        printf("Debut de A_etoide avec la distance manattan,    start_t = %ld\n", start_t);
        A_etoile(d_manattan, map, 0, distance, parent);
        end_t = clock();
        printf("Fin de A_etoide avec la distance manattan, end_t = %ld\n", end_t);
        temps_d_manattan = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("A_etoide avec la distance manattan :            Total time taken by CPU: %f\n", temps_d_manattan);

        m_e = m_e + temps_d_euclidienne;
        m_t = m_t + temps_d_tchebychev;
        m_m = m_m + temps_d_manattan;
    }

    m_e /= 10;
    m_t /= 10;
    m_m /= 10;
    printf("\n\n");
    printf("A_etoide avec la distance euclidienne : Total time taken by CPU: %f\n", m_e);
    printf("A_etoide avec la distance tchebychev :  Total time taken by CPU: %f\n", m_t);
    printf("A_etoide avec la distance manattan :    Total time taken by CPU: %f\n", m_m);
}
