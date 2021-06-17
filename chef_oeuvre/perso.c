#include "perso.h"
#include "main.h"

int main_perso(SDL_Window *window, SDL_Renderer *renderer)
{

    int i;
    perso_t *perso = creer_perso(window, renderer);
    //play_texture_xy(perso->sprite[0], window, renderer);

    int vitesse = 3;
    perso->direction = vitesse;
    for (i = 0; i < 9; ++i)
    {
        play_with_texture_perso(perso, window, renderer);
        deplacement_perso(perso, &vitesse);
        //vitesse += 1;
        //printf("vitesse %d\n", vitesse);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);

        SDL_RenderClear(renderer); // Effacer la fenêtre
    }

    supp_perso(perso);

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

    perso->info.x = X_POS_PERSO_DEPART;
    perso->info.y = Y_POS_PERSO_DEPART;

    perso->info.w = LARGEUR_PERSO;
    perso->info.h = HAUTEUR_PERSO;
    perso->direction = 0;
    perso->direction = calcul_dir_anim_perso(0);
    perso->score = 0;

    char *path_perso = malloc(sizeof(char) * NB_MAX_CHAR_PATH);

    for (i = 0; i < NB_IMG_PERSO; i++)
    {
        path_perso = path_perso_determine(i + 1);
        printf("%s\n", path_perso);
        perso->sprite[i] = IMG_LoadTexture(renderer, path_perso);
        if (perso->sprite[i] == NULL)
            end_sdl(0, "Echec du chargement de l'image dans la texture du perso", window, renderer);
    }
    return perso;
}

void supp_perso(perso_t *perso)
{
    for (int i = 0; i < NB_IMG_PERSO; i++)
    {
        SDL_DestroyTexture(perso->sprite[i]);
    }
    free(perso);
    perso = NULL;
}

int calcul_dir_anim_perso(int a)
{
    //printf("a=%d et indice =%d\n", a, (a + (NB_IMG_PERSO / 2)) % NB_IMG_PERSO);
    return ((a + (NB_IMG_PERSO / 2)) + NB_IMG_PERSO) % NB_IMG_PERSO;
}

void deplacement_perso(perso_t *perso, int *vitesse)
{
    int signe = *vitesse / *vitesse;
    printf("signe %d\n", signe);
    if (*vitesse != 0)
    {
        for (int i = 0; i < abs(*vitesse); ++i)
        {
            if (perso->info.x + signe >= 0 && perso->info.x + signe < LARGEUR_GRILLE)
                perso->info.x += signe;
        }
        *vitesse += (-1) * signe;
    }
    perso->direction = *vitesse;
}

int check_collision(perso_t *perso, int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE])
{
    int item_point = grille[perso->info.y][perso->info.x];
    perso->score += item_point;
    return item_point;
}

void play_with_texture_perso(perso_t *perso,
                             SDL_Window *window,
                             SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(perso->sprite[calcul_dir_anim_perso(perso->direction)], NULL, NULL, &source.w, &source.h);

    float zoom = 0.5;                // Facteur de zoom à appliquer
    destination.w = source.w * zoom; // La destination est un zoom de la source
    destination.h = source.h * zoom; // La destination est un zoom de la source

    destination.x = perso->info.x * LARGEUR_PIXEL;
    destination.y = perso->info.y;

    SDL_RenderCopy(renderer, perso->sprite[calcul_dir_anim_perso(perso->direction)], // Préparation de l'affichage
                   &source,
                   &destination);
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