#include "ui.h"

char *texte_score(int a)
{
    char *nom = malloc(15 * sizeof(char));
    nom[0] = '\0';
    strcat(nom, "Nombre de boule : ");
    char nb[2] = "";
    sprintf(nb, "%d", a);
    strcat(nom, nb);

    return nom;
}

void affichage_texte(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, char *texte, float taille, int x, int y, int r, int g, int b, int a)
{
    TTF_SetFontStyle(font, TTF_STYLE_NORMAL); // en italique, gras

    SDL_Color color = {r, g, b, a}; // la couleur du texte

    SDL_Surface *text_surface = NULL;                          // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, texte, color); // création du texte dans la surface
    if (text_surface == NULL)
        end_sdl(0, "Can't create text surface", window, renderer);

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
        end_sdl(0, "Can't create texture from surface", window, renderer);

    SDL_FreeSurface(text_surface); // la surface ne sert plus à rien

    SDL_Rect pos = {0, 0, 0, 0};                                // rectangle où le texte va être positionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte

    pos.w = pos.w * taille;
    pos.h = pos.h * taille;

    //SDL_GetWindowSize(window, &pos.x, &pos.y);
    //pos.x = x - pos.w / 2;
    //pos.y = y + pos.h / 2;
    pos.x = x;
    pos.y = y;
    SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture);                   // On n'a plus besoin de la texture avec le texte
}

void ecran_fin(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, int coll)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);

    affichage_texte(window, renderer, font, "Game Over !", 1, LARGEUR_FENETRE / 2, HAUTEUR_FENETRE / 4, 250, 250, 250, 255);
    //printf("coll %d ", coll);
    if (coll == 1)
    {
        affichage_texte(window, renderer, font, "Une boule vous a rattrape.", 1, LARGEUR_FENETRE / 2, 1 * HAUTEUR_FENETRE / 2, 250, 250, 250, 255);
    }
    else if (coll == -1)
    {
        affichage_texte(window, renderer, font, "Une bombe a explose vers vous.", 1, LARGEUR_FENETRE / 2, 1 * HAUTEUR_FENETRE / 2, 250, 250, 250, 255);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(500);
}

void ecran_debut(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);

    affichage_texte(window, renderer, font, "LabyBoule", 1, LARGEUR_FENETRE / 2, HAUTEUR_FENETRE / 4, 250, 250, 250, 255);

    affichage_texte(window, renderer, font, "Fleches directionnelles pour se deplacer", 1, LARGEUR_FENETRE / 2, 1 * HAUTEUR_FENETRE / 2, 250, 250, 250, 255);
    affichage_texte(window, renderer, font, "P pour poser une bombe", 1, LARGEUR_FENETRE / 2, 0.75 * HAUTEUR_FENETRE / 2, 250, 250, 250, 255);

    SDL_RenderPresent(renderer);
    SDL_Delay(2500);
}

void affichage_effet(SDL_Window *window, SDL_Renderer *renderer,
                     SDL_Texture *my_texture,
                     enum effet type_effet, int position, int delta, int anim)
{

    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions.w,
                      &window_dimensions.h);

    SDL_QueryTexture(my_texture, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source.w, &source.h);

    int nb_images = NB_FRAME_EFFET;
    int offset_x = source.w / nb_images,
        offset_y = source.h / NB_EFFET;

    state.x = 0;
    state.w = offset_x;
    state.h = offset_y;

    state.y = type_effet * offset_y;

    state.x = anim * offset_x;

    int i = position / NB_COLONNE_LABY;
    int j = position % NB_COLONNE_LABY;

    destination.y = i * HAUTEUR_CASE - 7;
    destination.x = j * LARGEUR_CASE;

    int zoom = ZOOM_BOMBE * 1;

    destination.w = zoom;
    destination.h = zoom;

    SDL_RenderCopy(renderer, my_texture, &state, &destination);
}

void gestion_affichage_effet(SDL_Window *window, SDL_Renderer *renderer,
                             enum effet type_effet, int position, int delta)

{
    SDL_Texture *my_texture;
    my_texture = IMG_LoadTexture(renderer, PATH_IMG_EFFET);
    if (my_texture != NULL)
    {
        SDL_Delay(TEMPS_FRAME_EFFET);
        for (int i = 0; i < NB_FRAME_EFFET; ++i)
        {
            affichage_effet(window, renderer, my_texture, type_effet, position, delta, i);
            SDL_RenderPresent(renderer);
            SDL_Delay(TEMPS_FRAME_EFFET);
        }
        SDL_DestroyTexture(my_texture);
    }
    else
    {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());
    }
}

void affichage_ecran(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font,
                     int delta_tps, int anim, entite_t *perso,
                     entite_t *liste_boules[NB_BOULES], int *nb_boules,
                     bombe_t *liste_bombes[NB_BOMBES], int *nb_bombes,
                     SDL_Texture *texture_mur, int map[NB_LIGNE_LABY][NB_COLONNE_LABY])
{

    SDL_RenderClear(renderer);

    //affichage fond
    play_texture_mur(window, renderer, texture_mur, map);
    //printf("nb de bombes : %d\n",nb_bombes);
    affichage_liste_bombes(window, renderer, liste_bombes);
    //affichage_entite
    //affichage entite perso
    affichage_entite(window, renderer, perso, delta_tps, anim * perso->vitesse);
    //affichage entite boule
    for (int k = 0; k < NB_BOULES; ++k)
    {
        if (liste_boules[k] != NULL)
            affichage_entite(window, renderer, liste_boules[k], delta_tps, anim * liste_boules[k]->vitesse);
    }

    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);

    SDL_RenderDrawLine(renderer, LARGEUR_FENETRE, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    SDL_Rect rect;
    rect.x = 0, rect.y = 0;
    rect.w = LARGEUR_ECRAN_SCORE + LARGEUR_FENETRE, rect.h = HAUTEUR_FENETRE;
    SDL_RenderDrawRect(renderer, &rect);

    affichage_score(window, renderer, font, perso, liste_boules, liste_bombes);
    SDL_RenderPresent(renderer);

    SDL_Delay(10);
}

void affichage_score(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font,
                     entite_t *perso, entite_t *liste_boules[NB_BOULES], bombe_t*liste_bombes[NB_BOMBES])
{
    int largeur_barre_vie = LARGEUR_ECRAN_SCORE - 2.75 * LARGEUR_CASE;
    int hauteur_barre_vie = HAUTEUR_CASE - 3;

    SDL_Rect rect_vie_fond =
        {(NB_COLONNE_LABY + 2.17) * LARGEUR_CASE, 2 * HAUTEUR_CASE,
         largeur_barre_vie, hauteur_barre_vie};
    int x_score = (NB_COLONNE_LABY)*LARGEUR_CASE + 18;
    SDL_Rect rect;

    /********* Contour score *******************/
    for (int i = 0; i < 15; ++i)
    {
        SDL_SetRenderDrawColor(renderer, 105 + 10 * i, 105 + 10 * i, 105 + 10 * i, 255);
        rect.x = LARGEUR_FENETRE + 1 + i, rect.y = 1 + i;
        rect.w = LARGEUR_ECRAN_SCORE - 2 - 2 * i, rect.h = HAUTEUR_FENETRE - 2 - 2 * i;
        SDL_RenderFillRect(renderer, &rect);
    }

    /****************** Vie ******************/
    affichage_texte(window, renderer, font, "vie", 0.4, x_score, 1 * HAUTEUR_CASE + 6, 0, 0, 0, 255);

    SDL_SetRenderDrawColor(renderer, 250, 0, 0, 255);
    rect_vie_fond.w = largeur_barre_vie * perso->vie / 100;
    SDL_RenderFillRect(renderer, &rect_vie_fond);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    rect_vie_fond.w = largeur_barre_vie;
    SDL_RenderDrawRect(renderer, &rect_vie_fond);

    char valeur_vie[5];
    sprintf(valeur_vie, "%d", perso->vie);

    affichage_texte(window, renderer, font, valeur_vie, 0.3, rect_vie_fond.x + 5, 2 * HAUTEUR_CASE - 14, 0, 0, 0, 255);
    affichage_texte(window, renderer, font, "%", 0.3, rect_vie_fond.x + 35, 2 * HAUTEUR_CASE - 11, 0, 0, 0, 255);

    /***************** Boules *****************/
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    affichage_texte(window, renderer, font, "Boules", 0.3, x_score, 4 * HAUTEUR_CASE +15, 0, 0, 0, 255);
    int nb_boules_restantes = 0;
    for (int k = 0; k < NB_BOULES; ++k)
    {
        if (liste_boules[k] != NULL)
        {
            affichage_score_entite(window, renderer, boule, x_score + nb_boules_restantes % 4 * 25, 6 * HAUTEUR_CASE + 25 * (nb_boules_restantes / 4));
            ++nb_boules_restantes;
        }
    }


  /***************** Bombes *****************/
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    affichage_texte(window, renderer, font, "Bombes posées", 0.3, x_score, 8 * HAUTEUR_CASE +15, 0, 0, 0, 255);
    int nb_bombes_posees = 0;
    for (int k = 0; k < NB_BOMBES; ++k)
    {
        if (liste_bombes[k] != NULL)
        {
            affichage_score_entite(window, renderer, bombe, x_score + nb_bombes_posees % 4 * 25, 10 * HAUTEUR_CASE + 25 * (nb_bombes_posees / 4));
            ++nb_bombes_posees;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void affichage_score_entite(SDL_Window *window, SDL_Renderer *renderer,
                            enum type_objet type, int x_pos, int y_pos)
{

    SDL_Rect
        source = {0},
        window_dimensions = {0},
        destination = {0},
        state = {0};

    SDL_Texture *my_texture;
    my_texture = IMG_LoadTexture(renderer, PATH_IMG_SCORE);
    if (my_texture != NULL)
    {
        SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
        SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

        int nb_images = 4;
        int offset_x = source.w / nb_images,
            offset_y = source.h;

        float zoom = 25;

        destination.x = x_pos;
        destination.y = y_pos;
        destination.w = zoom;
        destination.h = zoom;

        state.x = (int)type*offset_x;
         state.y = 0;
        state.w = offset_x, state.h = offset_y;

        SDL_RenderCopy(renderer, my_texture, &state, &destination);
        SDL_DestroyTexture(my_texture);
    }
    else
    {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());
    }
}