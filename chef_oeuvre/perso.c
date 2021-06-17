#include "perso.h"
#include "main.h"

int main_perso(SDL_Window *window, SDL_Renderer *renderer)
{

    int i;
    perso_t *perso = creer_perso(window, renderer);
    // supp_perso(perso);
    play_texture_xy(perso->sprite[0], window, renderer);

    int vitesse = -4;

    /*
    for (i = 0; i < 10; ++i)
    {
        play_with_texture_2(perso, window, renderer);
    }
*/
    return 0;
}

perso_t *creer_perso(SDL_Window *window, SDL_Renderer *renderer)
{
    int i;
    perso_t *perso = NULL;
    perso = malloc(sizeof(perso_t));
    if (perso == NULL)
        exit(EXIT_FAILURE);
    //perso->sprite = malloc(sizeof(SDL_Renderer *) * NB_IMG_PERSO);

    perso->info.w = LARGEUR_PERSO;
    perso->info.h = HAUTEUR_PERSO;
    perso->direction = 0;
    perso->direction = calcul_dir_anim_perso(0);
    perso->score = 0;

    char *path_perso = malloc(sizeof(char) * 1000);
    //perso->sprite = IMG_LoadTexture(renderer, "/home/local.isima.fr/mavilledie4/shared/projetZ1/chef_oeuvre/img2/redfighter0001.png");

    //play_texture_xy(perso->sprite, window, renderer);

    for (i = 0; i < NB_IMG_PERSO; i++)
    {
        path_perso = path_perso_determine(i + 1);
        printf("%s\n", path_perso);
        perso->sprite[i] = IMG_LoadTexture(renderer, path_perso);
        if (perso->sprite[i] == NULL)
            end_sdl(0, "Echec du chargement de l'image dans la texture du perso", window, renderer);
        //play_texture_xy(perso->sprite[i], window, renderer);
    }
    return perso;
}

void supp_perso(perso_t *perso)
{
    for (int i = 0; i < NB_IMG_PERSO; i++)
    {
        SDL_DestroyTexture(perso->sprite[i]);
    }
    free(perso->sprite);
    free(perso);
    perso = NULL;
}

int calcul_dir_anim_perso(int a)
{
    return (a + (NB_IMG_PERSO / 2));
}

void deplacement_perso(perso_t *perso, int *vitesse)
{
    int signe = *vitesse / *vitesse;
    if (*vitesse != 0)
    {
        for (int i = 0; i < abs(*vitesse); ++i)
        {
            if (perso->info.x - 1 >= 0 && perso->info.x + 1 < LARGEUR_GRILLE)
                perso->info.x += signe;
        }
        *vitesse = (-1) * signe;
    }
}

int check_collision(perso_t *perso, int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE])
{
    int item_point = grille[perso->info.y][perso->info.x];
    perso->score += item_point;
    return item_point;
}

void play_with_texture_2(perso_t *perso,
                         SDL_Window *window,
                         SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(perso->sprite[calcul_dir_anim_perso(perso->direction)], NULL, NULL, &source.w, &source.h);

    float zoom = 1.5;         // Facteur de zoom à appliquer
    destination.w = source.w; // La destination est un zoom de la source
    destination.h = source.h; // La destination est un zoom de la source
    destination.x = (window_dimensions.w - destination.w) / 2;
    destination.y = (window_dimensions.h - destination.h) / 2;

    SDL_RenderCopy(renderer, perso->sprite[calcul_dir_anim_perso(perso->direction)], // Préparation de l'affichage
                   &source,
                   &destination);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    SDL_RenderClear(renderer); // Effacer la fenêtre
}

char *path_perso_determine(int n)
{
    char *nom = malloc(NB_MAX_CHAR_PATH * sizeof(char));
    nom[0] = '\0';
    strcat(nom, PATH_IMG_PERSO);
    char nb[1] = "";
    sprintf(nb, "%d", n);
    strcat(nom, nb);
    strcat(nom, PATH_IMG_PERSO_EXT);
    //printf("%s\n", nom);
    return nom;
}

void play_texture_xy(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    float zoom = 0.5;

    destination.h = source.h * zoom;
    destination.w = source.w * zoom;

    destination.x = (window_dimensions.w - 0.7 * destination.w) / 2;
    destination.y = (window_dimensions.h - 1.6 * destination.h) / 2;
    SDL_RenderCopy(renderer, my_texture, &source, &destination);
    SDL_RenderPresent(renderer);
    SDL_Delay(1500);
}