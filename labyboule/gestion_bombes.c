#include "gestion_bombes.h"

void creer_bombe(SDL_Window *window, SDL_Renderer *renderer,
                 int pos_cour, int rayon_action, int temps, int pose_bombe,
                 bombe_t **pbombe)
{
    *pbombe = (bombe_t *)malloc(sizeof(bombe_t));
    if (*pbombe)
    {
        (*pbombe)->pos_cour = pos_cour;
        (*pbombe)->rayon_action = rayon_action;
        (*pbombe)->temps = temps;
        (*pbombe)->temps_pose_bombe = pose_bombe;
        charger_texture_bombe(window, renderer, *pbombe, PATH_IMG_BOMBE);
    }
}

void ajouter_bombe(SDL_Window *window, SDL_Renderer *renderer,
                   bombe_t *liste_bombes[NB_BOMBES], int *nb_bombes,
                   entite_t *perso)
{
    if (*nb_bombes < NB_BOMBES)
    {
        int i = 0;
        while (i < NB_BOMBES - 1 && liste_bombes[i] != NULL)
            i++;

        if (i == NB_BOMBES)
            printf("erreur sur les indices des bombes\n");

        if (check_deja_bombe(liste_bombes, perso->pos_cour) == SDL_TRUE)
        {
            creer_bombe(window, renderer, perso->pos_cour, 0, -1,
                        SDL_GetTicks(), &liste_bombes[i]);
            *nb_bombes += 1;
            //printf("nb bombe %d\n", *nb_bombes);
        }
    }
    else
        printf("nb de bombe max deja posee\n");

    /*
    for (int k = 0; k < NB_BOMBES; ++k)
    {
        printf("k = %d --> %p\n", k, liste_bombes[k]);
    }
    printf("nb bombe %d\n", *nb_bombes);
*/
}

SDL_bool check_deja_bombe(bombe_t *liste_bombes[NB_BOMBES], int pos)
{
    SDL_bool res = SDL_TRUE;
    int i = 0;
    while (res == SDL_TRUE && i < NB_BOMBES)
    {
        if (liste_bombes[i] != NULL && pos == liste_bombes[i]->pos_cour)
            res = SDL_FALSE;
        ++i;
    }
    return res;
}

void charger_texture_bombe(SDL_Window *window, SDL_Renderer *renderer, bombe_t *bombe, char *chemin)
{
    SDL_Texture *my_texture = NULL;
    my_texture = IMG_LoadTexture(renderer, chemin);
    if (my_texture == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    bombe->texture = my_texture;
}

void affichage_liste_bombes(SDL_Window *window, SDL_Renderer *renderer,
                            bombe_t *liste_bombes[NB_BOMBES])
{
    for (int i = 0; i < NB_BOMBES; ++i)
    {
        if (liste_bombes[i] != NULL)
            affichage_bombe(window, renderer, liste_bombes[i]);
    }
}
void affichage_bombe(SDL_Window *window, SDL_Renderer *renderer, bombe_t *bombe)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre

    SDL_Texture *my_texture = NULL;
    my_texture = bombe->texture;
    SDL_QueryTexture(my_texture, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    float zoom = ZOOM_BOMBE;
    destination.w =  zoom; // La destination est un zoom de la source
    destination.h =  zoom; // La destination est un zoom de la source
    destination.x = (bombe->pos_cour % NB_COLONNE_LABY) * LARGEUR_CASE+2;
    destination.y = (bombe->pos_cour / NB_COLONNE_LABY) * HAUTEUR_CASE +1;

    SDL_RenderCopy(renderer, my_texture, &source, &destination);
}

void liberer_bombe(bombe_t **p_bombe)
{
    SDL_DestroyTexture((*p_bombe)->texture);
    free(*p_bombe);
    *p_bombe = NULL;
}

int explosion(bombe_t *bombe, entite_t *perso, entite_t *tab_boule[NB_BOULES], int map[NB_LIGNE_LABY][NB_COLONNE_LABY])
{
    int rayon_action = bombe->rayon_action;
    int erreur = 1;

    int position = bombe->pos_cour;
    int i = position / NB_COLONNE_LABY;
    int j = position % NB_COLONNE_LABY;

    for (int k = 0; k < rayon_action; k++)
    {
        int sauv = bombe->pos_cour;
        unsigned mur = (unsigned)map[i][j];
        if (mur & !mur_est)
        {
            erreur *= collision_bombe(perso, tab_boule, i, j + 1);
            bombe->pos_cour = bombe->pos_cour + 1;
            explosion(bombe, perso, tab_boule, map);
        }

        if (mur & !(unsigned)mur_ouest)
        {
            bombe->pos_cour = sauv;
            erreur *= collision_bombe(perso, tab_boule, i, j - 1);
            bombe->pos_cour = bombe->pos_cour - 1;
            explosion(bombe, perso, tab_boule, map);
        }

        if (mur & !(unsigned)mur_nord)
        {
            bombe->pos_cour = sauv;
            erreur *= collision_bombe(perso, tab_boule, i - 1, j);
            bombe->pos_cour = bombe->pos_cour - NB_COLONNE_LABY;
            explosion(bombe, perso, tab_boule, map);
        }
        if (mur & !(unsigned)mur_sud)
        {
            bombe->pos_cour = sauv;
            erreur *= collision_bombe(perso, tab_boule, i + 1, j);
            bombe->pos_cour = bombe->pos_cour + NB_COLONNE_LABY;
            explosion(bombe, perso, tab_boule, map);
        }
        bombe->pos_cour = sauv;
    }
    liberer_bombe(&bombe);
    return erreur;
}

int collision_bombe(entite_t *perso, entite_t *tab_boule[NB_BOULES], int i, int j)
{
    int erreur = 0;
    int position_perso = perso->pos_cour;
    int ligne_perso = position_perso / NB_COLONNE_LABY;
    int colonne_perso = position_perso % NB_COLONNE_LABY;

    if (i == ligne_perso && j == colonne_perso)
    {
        //le perso saute !
        erreur = -1;
    }

    int k = 0;
    while (k < NB_BOULES && tab_boule[k] != NULL)
    {
        entite_t *boule = tab_boule[k];
        int position_boule = boule->pos_cour;
        int ligne_boule = position_boule / NB_COLONNE_LABY;
        int colonne_boule = position_boule % NB_COLONNE_LABY;

        if (i == ligne_boule && j == colonne_boule)
        {
            //supprimer la boule
            printf("boule supprimee\n");
            liberer_entite(&boule);
            erreur = 2;
        }
        k++;
    }
    return erreur; //0 : pas d'erreur ; -1 : tuer le perso; 2 : boule touchee par la bombe
}