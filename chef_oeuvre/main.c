#include "main.h"

int main()
{
    int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE];
    SDL_DisplayMode screen;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int vitesse = 0;
    perso_t *perso = NULL;
    int c = 0;

    int cordy_bg = 0, cordy_bg2 = 0;
    SDL_Rect window_dimensions = {0};

    int etape = 0;
    int hauteur_pixel = 600 / HAUTEUR_GRILLE;
    int largeur_pixel = 1000 / LARGEUR_GRILLE;

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
        "Chef d'oeuvre",
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

    /************** initialisation ttf ****************/
    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);
    /**** fin initialisation  *****/

    /****** chargement de la font *******/
    TTF_Font *font = NULL;                       // la variable 'police de caractère'
    font = TTF_OpenFont(PATH_FONT, TAILLE_FONT); // La police à charger, la taille désirée    if (font == NULL)
    if (font == NULL)
        end_sdl(0, "Can't load font", window, renderer);

    /*load item*/
    SDL_Texture *planche = NULL;
    planche = IMG_LoadTexture(renderer, PATH_IMG_ITEM);
    if (planche == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture item", window, renderer);

    /*Loading texture*/
    SDL_Texture *bg = IMG_LoadTexture(renderer, PATH_IMG_BG);
    if (bg == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture bg1", window, renderer);

    SDL_Texture *bg2 = IMG_LoadTexture(renderer, "./img2/bg.png");
    if (bg2 == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture bg2", window, renderer);

    /***************************/
    perso = creer_perso(window, renderer);
    init_grille(grille);

    SDL_bool
        program_on = SDL_TRUE, // Booléen pour dire que le programme doit continuer
        paused = SDL_FALSE;    // Booléen pour dire que le programme est en pause
    while (program_on)
    {                    // La boucle des évènements
        SDL_Event event; // Evènement à traiter

        while (program_on && SDL_PollEvent(&event))
        { // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
            // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN: // Le type de event est : une touche appuyée
                              // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                              // l'event, plusieurs champs deviennent pertinents
                switch (event.key.keysym.sym)
                {                     // la touche appuyée est ...
                case SDLK_p:          // 'p'
                case SDLK_SPACE:      // 'SPC'
                    paused = !paused; // basculement pause/unpause
                    break;
                case SDLK_ESCAPE:   // 'ESCAPE'
                case SDLK_q:        // 'q'
                    program_on = 0; // 'escape' ou 'q', d'autres façons de quitter le programme
                    break;
                case SDLK_LEFT:
                    if (vitesse > VITESSE_MIN)
                        vitesse--;
                    break;
                case SDLK_RIGHT:
                    if (vitesse < VITESSE_MAX)
                        vitesse++;
                    break;
                default: // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }
        //draw(state, &color, renderer, window); // On redessine
        if (!paused)
        { // Si on n'est pas en pause
            cordy_bg += 6;
            if (cordy_bg >= window_dimensions.h)
                cordy_bg = 0;
            cordy_bg2 += 6;
            if (cordy_bg2 >= window_dimensions.h)
                cordy_bg2 = 0;

            affichage_bgScroll(window, renderer, bg, bg2, &cordy_bg, &cordy_bg2);
            //affichage_texte(window, renderer, font, "score", 1, LARGEUR_FENETRE / 2, 8 * HAUTEUR_FENETRE / 10);
            draw(renderer, grille, planche, &etape, &hauteur_pixel, &largeur_pixel);

            if (c > 10)
            {
                evolution(grille, &etape);
                etape = (etape + 1) % HAUTEUR_GRILLE;
                //printf("etapte=%d\n", etape);

                c = 0;
                //perso->score++;
            }
            else
            {
                c++;
            }
            deplacement_perso(perso, &vitesse);
            check_collision(perso, grille, etape % HAUTEUR_GRILLE);
            play_with_texture_perso(perso, window, renderer);
            affichage_texte(window, renderer, font, texte_score(perso->score), 1, LARGEUR_FENETRE / 2, 8 * HAUTEUR_FENETRE / 10);

            SDL_RenderPresent(renderer);
            SDL_Delay(10);
            SDL_RenderClear(renderer);
            if (perso->score >= GOAL_SCORE)
            {
                printf("Score atteint %d\n", perso->score);
                program_on = 0;
            }
        }
        SDL_Delay(20); // Petite pause
    }

    //end_sdl(1, "fin normal", window, renderer);
    return 0;
}

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{ // renderer à fermer
    char msg_formated[255];
    int l;

    if (!ok)
    {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}

char *texte_score(int a)
{
    char *nom = malloc(15 * sizeof(char));
    nom[0] = '\0';
    strcat(nom, "score : ");
    char nb[5] = "";
    sprintf(nb, "%d", a);
    strcat(nom, nb);

    return nom;
}

void init_grille(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE])
{
    int i, j;

    for (i = 0; i < HAUTEUR_GRILLE; i++)
    {
        for (j = 0; j < LARGEUR_GRILLE; j++)
        {
            grille[i][j] = 0;
        }
    }
}

void evolution(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], int *etape)
{
    int valeur, signe;
    int alea;
    int j; 

    for (j = 0; j < LARGEUR_GRILLE; j++)
    {
        alea = rand() % 70;

        switch (alea)
        {
        case 0:
            valeur = -4;
            break;
        case 1:
            valeur = -3;
            break;
        case 2:
            valeur = -2;
            break;
        case 3:
            valeur = -1;
            break;
        case 4:
            valeur = 1;
            break;
        case 5:
            valeur = 2;
            break;
        case 6:
            valeur = 3;
            break;
        case 7:
            valeur = 4;
            break;
        default:
            valeur = 0;
            break;
        }
        grille[*etape][j] = valeur;
    }

    /*
    for (j=0;j<LARGEUR_GRILLE;j++)
    {
        valeur = rand()%5;     //valeur entre 0 et 4
        signe = (2 * (rand()%2)) - 1;   //signe vaut -1 ou 1
        grille[*etape][j] = valeur * signe;
    }
    */
}
void afficher_grille(int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE])
{
    int i, j;

    printf("valeurs grille :\n");

    for (i = 0; i < HAUTEUR_GRILLE; i++)
    {
        for (j = 0; j < LARGEUR_GRILLE; j++)
        {
            printf("%d\t", grille[i][j]);
        }
        printf("\n");
    }
}

void draw(SDL_Renderer *renderer, int grille[HAUTEUR_GRILLE][LARGEUR_GRILLE], SDL_Texture *planche, int *etape, int *hauteur_pixel, int *largeur_pixel)
{
    SDL_Rect
        source = {0},
        destination = {0},
        state = {0};

    SDL_QueryTexture(planche, NULL, NULL, &source.w, &source.h);

    int offset_x = source.w / 4;
    int offset_y = source.h / 4;
    int i, j;
    int ligne = 0;

    float zoom = 0.25;
    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;

    state.w = offset_x;
    state.h = offset_y;
    //destination.y = HAUTEUR_FENETRE;

    for (i = 0; i < HAUTEUR_GRILLE; i++)
    {
        //fprintf(stdout,"premier for\n");
        ligne = (i + (*etape)) % HAUTEUR_GRILLE;
        destination.y = i*HAUTEUR_PERSO ;
        printf("y : %d\n", destination.y);

        for (j = 0; j < LARGEUR_GRILLE; j++)
        {
            //fprintf(stdout,"deuxieme for\n");
            destination.x = j * LARGEUR_PIXEL;
            switch (grille[ligne][j])
            {
            //fprintf(stdout,"valeur : %d\n", grille[ligne][j]);
            case 0:
                //ne rien afficher : on voit le background
                break;
            case -1:
                state.x = 0;
                state.y = 0;
                break;
            case 1:
                state.x = offset_x;
                state.y = 0;
                break;
            case -2:
                state.x = 2 * offset_x;
                state.y = 0;
                break;
            case 2:
                state.x = 3 * offset_x;
                state.y = 0;
                break;
            case -3:
                state.x = 0;
                state.y = offset_y;
                break;
            case 3:
                state.x = offset_x;
                state.y = offset_y;
                break;
            case -4:
                state.x = 2 * offset_x;
                state.y = offset_y;
                break;
            case 4:
                state.x = 3 * offset_x;
                state.y = offset_y;
                break;
            default:
                fprintf(stdout, "valeur dans grille incoherente\n");
                //fprintf(stdout,"valeur : %d\n", grille[ligne][j]);
                break;
            }
            if (grille[ligne][j] != 0)
                SDL_RenderCopy(renderer, planche, &state, &destination);
        }
    }
}
