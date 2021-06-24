#include "gestion_entites.h"

void creer_entite(SDL_Window *window, SDL_Renderer *renderer, int pos_prec, int pos_cour, int vitesse, int vertical, int horizontal, entite_t **pentite, char *chemin)
{
    *pentite = (entite_t *)malloc(sizeof(entite_t));
    if (*pentite)
    {
        (*pentite)->pos_prec = pos_prec;
        (*pentite)->pos_cour = pos_cour;
        (*pentite)->vitesse = vitesse;
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

void liberer(entite_t *entite)
{
    free(entite);
    entite = NULL;
}

void affichage_entite(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, int *delta)
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
    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    int nb_images = 4;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 1.95;                      // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h / 4;         // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

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

    state.x = (*delta / 4) * offset_x;

    destination.w = offset_x * zoom; // Largeur du sprite à l'écran
    destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

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
    int i = entite->pos_prec / NB_COLONNE_LABY;
    int j = entite->pos_prec % NB_COLONNE_LABY;

    destination.y = i * HAUTEUR_CASE - 4 +(*delta * 0.04) *entite->horizontal;
    destination.x = j * LARGEUR_CASE + (*delta * 0.04) *entite->vertical;

    /* * LARGEUR_CASE + (*deltaTimeNB_COLONNE_LABY * *input_h * TRANSI);*/
    //destination.y += entite->vitesse;
    // printf("x : %d y : %d\n", destination.x, destination.y);

    SDL_RenderCopy(renderer, entite->texture, &state, &destination);
}

//retourne 0 si pas de collision
int collision(entite_t *perso, entite_t *liste_boule[NB_BOULES])
{
    int res = 0;
    for (int k = 0; k < NB_BOULES; ++k)
    {
        res = res || (perso->pos_cour == liste_boule[k]->pos_cour);
    }
    return res;
}