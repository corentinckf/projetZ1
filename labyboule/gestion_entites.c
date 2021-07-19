#include "gestion_entites.h"

void creer_entite(SDL_Window *window, SDL_Renderer *renderer, int pos_prec, int pos_cour, float vitesse, int vertical, int horizontal, entite_t **pentite, char *chemin)
{
    *pentite = (entite_t *)malloc(sizeof(entite_t));
    if (*pentite)
    {
        (*pentite)->pos_prec = pos_prec;
        (*pentite)->pos_cour = pos_cour;
        (*pentite)->vitesse = vitesse;
        (*pentite)->compteur_deplacement = 0.;
        (*pentite)->vertical = vertical;
        (*pentite)->horizontal = horizontal;
        charger_texture(window, renderer, *pentite, chemin);
    }
}

void charger_texture(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, char *chemin)
{
    SDL_Texture *my_texture = NULL;
    my_texture = IMG_LoadTexture(renderer, chemin);
    if (my_texture == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    entite->texture = my_texture;
}

void liberer_entite(entite_t **p_entite)
{
    SDL_DestroyTexture((*p_entite)->texture);
    free(*p_entite);
    *p_entite = NULL;
}

void affichage_entite(SDL_Window *window, SDL_Renderer *renderer,
                      entite_t *entite, int delta, float anim)
{
    float taille = 0.01;
    int idle = 0;

    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions.w,
                      &window_dimensions.h);
    SDL_QueryTexture(entite->texture, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source.w, &source.h);

    int nb_images = 4;
    int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h / 4;         // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

    //float zoom = LARGEUR_CASE/offset_x;                   // zoom, car ces images sont un peu petites

    state.x = 0;
    state.w = offset_x;
    state.h = offset_y;
    if (entite->horizontal == 0 && entite->vertical == 0)
        idle = 1;
    else
        idle = 0;

    if (entite->vertical == 1)
        state.y = 2 * offset_y;
    else if (entite->vertical == -1)
        state.y = 3 * offset_y;

    if (entite->horizontal == 1)
        state.y = 0 * offset_y;
    else if (entite->horizontal == -1)
        state.y = 1 * offset_y;

    state.x = ((int)anim % 4) * offset_x;

    //destination.y = 0.1 * window_dimensions.h; // La course se fait en milieu d'écran (en vertical)

    if (!idle)
    {
        state.x += offset_x;
        state.x %= source.w;
    }
    else
    {
        state.y = 0;
        state.x = 0;
    }

    destination = rectangle_sprite(entite, delta, 30);

    /* * LARGEUR_CASE + (*deltaTimeNB_COLONNE_LABY * *input_h * TRANSI);*/
    //destination.y += entite->vitesse;
    // printf("x : %d y : %d\n", destination.x, destination.y);

    SDL_RenderCopy(renderer, entite->texture, &state, &destination);
}

//retourne 0 si pas de collision
int collision(int delta, entite_t *perso,
              entite_t *liste_boules[NB_BOULES], int *nb_boules,
              bombe_t *liste_bombes[NB_BOMBES], int *nb_bombes,
              int map[NB_LIGNE_LABY][NB_COLONNE_LABY])
{
    int res = 0;

    SDL_Rect sprite_perso;
    SDL_Rect sprite_boule;
    SDL_Rect sprite_bombe;
    SDL_Rect intersection;

    sprite_perso = rectangle_sprite(perso, delta, LARGEUR_CASE);

    for (int k = 0; k < NB_BOULES; ++k)
    {
        if (liste_boules[k] != NULL)
        {
            sprite_boule = rectangle_sprite(liste_boules[k], delta, LARGEUR_CASE);
            if (SDL_IntersectRect(&sprite_perso, &sprite_boule, &intersection) == SDL_TRUE && intersection.h >= 0.6 * sprite_boule.h && intersection.w >= 0.6 * sprite_boule.w)
                res = 1;
        }
    }

    if (*nb_bombes > 0)
    {
        int i = 0;
        while (!res && i < NB_BOMBES)
        {
            if (liste_bombes[i] != NULL)
            {
                int u = liste_bombes[i]->pos_cour / NB_COLONNE_LABY;
                int v = liste_bombes[i]->pos_cour % NB_COLONNE_LABY;
                sprite_bombe.y = u * HAUTEUR_CASE - 7;
                sprite_bombe.x = v * LARGEUR_CASE;
                sprite_bombe.w = ZOOM_BOMBE;
                sprite_bombe.h = ZOOM_BOMBE;

                if (SDL_IntersectRect(&sprite_perso, &sprite_bombe, &intersection) == SDL_TRUE && intersection.h >= 0.6 * sprite_bombe.h && intersection.w >= 0.6 * sprite_bombe.w)
                {
                    //res = -1;
                }
                int k = 0;
                while (k < NB_BOULES)
                {
                    if (liste_bombes[i] != NULL && liste_boules[k] != NULL)
                    {
                        sprite_boule = rectangle_sprite(liste_boules[k], delta, LARGEUR_CASE);
                        if (SDL_IntersectRect(&sprite_bombe, &sprite_boule, &intersection) == SDL_TRUE && intersection.h >= 0.8 * sprite_boule.h && intersection.w >= 0.8 * sprite_boule.w)
                        {
                            liberer_entite(&liste_boules[k]);
                            liberer_bombe(&liste_bombes[i]);

                            printf("liste boule k = %p\n", liste_boules[k]);
                            printf("liste bombe k = %p\n", liste_bombes[i]);
                            *nb_bombes -= 1;
                            *nb_boules -= 1;
                            printf("bouls %d, bombe %d\n", *nb_boules, *nb_bombes);
                            printf("contact boule bombe\n");
                        }
                    }
                    ++k;
                }
            }
            ++i;
        }
    }

    return res;
}

SDL_Rect rectangle_sprite(entite_t *entite, int delta_tps, int zoom)
{
    //float val = 0.15 * entite->compteur_deplacement ;
    //float val = 0.075 * entite->vitesse;
    /*
    int delta_tps;
    if (delta > PERIODE)
        delta_tps = delta - PERIODE;
    else
        delta_tps = delta;
*/
    SDL_Rect rect;

    int i = entite->pos_prec / NB_COLONNE_LABY;
    int j = entite->pos_prec % NB_COLONNE_LABY;

    float nb_periode = 1. / entite->vitesse;


    float ajustement = (entite->compteur_deplacement + ((float)delta_tps / (nb_periode * (float)PERIODE))) * LARGEUR_CASE;

    //rect.y = i * HAUTEUR_CASE - 7 + (delta_tps * val)  * entite->horizontal;

    rect.y = i * HAUTEUR_CASE - 7 + ajustement * entite->horizontal;
    rect.x = j * LARGEUR_CASE + ajustement * entite->vertical;

    rect.w = zoom;
    rect.h = zoom;

    return rect;
}
