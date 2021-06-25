#include "const.h"

void affichage_texte(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, char *texte, int taille, int x, int y)
{
    TTF_SetFontStyle(font, NULL); // en italique, gras

    SDL_Color color = {250, 250, 250, 255}; // la couleur du texte

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
    pos.x = x - pos.w / 2;
    pos.y = y + pos.h / 2;
    SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture);                   // On n'a plus besoin de la texture avec le texte
}

void ecran_fin(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, int coll)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);

    affichage_texte(window, renderer, font, "Game Over !", 1, LARGEUR_FENETRE / 2, HAUTEUR_FENETRE / 4);
    //printf("coll %d ", coll);
    if (coll == 1)
    {
        affichage_texte(window, renderer, font, "Une boule vous a rattrape.", 1, LARGEUR_FENETRE / 2, 1 * HAUTEUR_FENETRE / 2);
    }else if(coll==-1)
    {
        affichage_texte(window, renderer, font, "Une bombe a explose vers vous.", 1, LARGEUR_FENETRE / 2, 1 * HAUTEUR_FENETRE / 2);
    }
    

    SDL_RenderPresent(renderer);
    SDL_Delay(2500);
}