#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "labyrinthe_arborescent.h"

void fisher_yates_shuffle(int *aretes, int taille)
{
    int i = taille - 2;
    int j,sauv;
    while (i >= 2)
    {
        j = (rand()%i) % 2;
        //echanger aretes i et j
        sauv = aretes[i];
        aretes[i] = aretes[j];
        aretes[j] = sauv;
        sauv = aretes[i+1];
        aretes[i+1] = aretes[j+1];
        aretes[j+1] = sauv;
        i -= 2;
    }
}

void creation_grille(int *aretes, int taille, int nb_elements)
{
    for (int i=0; i < LIGNES ; i++)
    {
        for (int j=0 ; j < COLONNES; j++)
        {
            int sommet_cour = i*LIGNES + j;
            int sommet_suiv = sommet_cour + 1;
            int sommet_dessus = sommet_cour - COLONNES;
            if (i-1 < 0 && j+1 < COLONNES)    //premiere ligne sans derniere colonne
            {
                ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_suiv);
            }
            else if (j+1 == COLONNES)    //derniere colonne
            {
                ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_dessus);
            }
            else if (i-1 >= 0 && j+1 < COLONNES)
            {
                ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_suiv);
                ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_dessus);
            }            
        }
    }
}

int main()
{
    /*
    if (SDL_Init(SDL_INIT_VIDEO) != 0) printf("erreur d'intialisation de la SDL\n");

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    //Creation de la fenêtre
    window = SDL_CreateWindow("Premier dessin",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                                screen.h * 0.66,
                                SDL_WINDOW_OPENGL);
    if (window == NULL) printf("erreur de creation de la fenetre\n");

    //Creation du renderer
    renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) printf("erreur de creation du renderer\n");
    */

    int classes[TAILLE];
    int hauteurs[TAILLE];
    //srand(time(NULL));
    srand(42);

    int noeuds[TAILLE];
    int *aretes = (int *)malloc(sizeof(int) * 8*TAILLE); //s'assurer que le nombre de cases est pair (couple d'entiers)
    int taille = 8 * TAILLE;
    int nb_elements = 0;

    int *nouv_aretes = (int *)malloc(sizeof(int) * 8 * TAILLE);
    int nb_aretes = 0;
    int nouv_taille = 8 * TAILLE;

    //initialisation
    for (int i = 0; i < TAILLE; i++)
    {
        noeuds[i] = i;
    }

    FILE *fichier = NULL;
    fichier = fopen("labyrinthe.dot","w");
    FILE *lab_arbre = NULL;
    lab_arbre = fopen("lab_arbre.dot", "w");

    if (fichier)
    {
        for (int i=0; i < LIGNES ; i++)
        {
            for (int j=0 ; j < COLONNES; j++)
            {
                int sommet_cour = i*COLONNES + j;
                int sommet_suiv = sommet_cour + 1;
                int sommet_dessus = sommet_cour - COLONNES;
                if (i == 0 && j+1 < COLONNES)    //premiere ligne sans derniere colonne
                {
                    ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_suiv);
                }
                else if (i != 0 && j+1 == COLONNES)    //derniere colonne
                {
                    ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_dessus);
                }
                else if (i > 0 && j+1 < COLONNES)
                {
                    ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_suiv);
                    ajouter(&aretes,&taille,&nb_elements,sommet_cour,sommet_dessus);
                }            
            }
        }
        //creation_grille(aretes,taille,nb_elements);
        draw_graph(noeuds,aretes,fichier,nb_elements);
        creer(classes,hauteurs);
        fisher_yates_shuffle(aretes,taille);
        arbre_couvrant(nouv_aretes,&nb_aretes,aretes,&nb_elements,classes,hauteurs,nouv_taille);
        draw_graph(noeuds,nouv_aretes,lab_arbre,nb_aretes);
        system("dot -Tjpg labyrinthe.dot -o labyrinthe.jpg");
        system("dot -Tjpg lab_arbre.dot -o lab_arbre.jpg");
        fclose(fichier);
    }

    return EXIT_SUCCESS;
}