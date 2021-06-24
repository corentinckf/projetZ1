#include <stdio.h>
#include <stdlib.h>
#include "tasbin.h"

#define TAILLE 20

int fils1(int i)
{
    return (2*i)+1;
}

int fils2(int i)
{
    return (2*i)+2;
}

int pere(int i)
{
    if (i>0)
    {
        return ((i-1)/2);
    }
    else
    {
        return 0;
    }
}

void init(tete_t **tete)
{
    *tete = (tete_t *) malloc(sizeof(tete_t));
    (*tete)->nb_elements = 0;
    (*tete)->tas = (int *) malloc(TAILLE * sizeof(int));
}

int estPlein(tete_t *tete)
{
    return tete->nb_elements == TAILLE;
}

int estVide(tete_t *tete)
{
    return tete->nb_elements == 0;
}

//verifier que ca marche si tas vide
int ajouter(tete_t *tete, int valeur)
{
    int erreur = 1;
    int sauv = 0;
    int *cour = tete->tas;
    int *prec;

    if (! estPlein(tete))
    {
        erreur = 0;
        tete->nb_elements++;
        cour += tete->nb_elements;
        *cour = valeur;
        prec = tete->tas;
        prec += pere(*cour);

        while (*prec > *cour)
        {
            sauv = *cour;
            *cour = *prec;
            *prec = sauv;
            cour = prec;
            prec = tete->tas;
            prec += pere(*cour);
        }
    }
    return erreur;
}

int retirer_racine(tete_t *tete, int *res)
{
    int *cour = tete->tas;
    int erreur=1;

    if (! estVide(tete))
    {
        erreur = 0;
        *res = *cour;
        *cour = 0;      //tas min donc on insere la plus petite valeur sur la racine
    }
    return erreur;
}

//l'entier augmenter vaut 1 si l'utilisateur veut augmenter la priorite et -1 sinon
void modifier(tete_t *tete, int place, int augmenter)
{
    int *cour = tete->tas;
    cour += place;
    int *prec;
    int erreur = 1;
    int sauv;

    if (place < tete->nb_elements)
    {
        erreur = 0;
        *cour = *cour + augmenter;
        prec = tete->tas;
        prec += pere(*cour);

        while (*prec > *cour)
        {
            sauv = *cour;
            *cour = *prec;
            *prec = sauv;
            cour = prec;
            prec = tete->tas;
            prec += pere(*cour);
        }
    }
}

void construire(int tab[7], tete_t *tete)
{
    int i=0;

    for (i=0;i<7;i++)
    {
        ajouter(tete,tab[i]);
        i++;
    }
}

void liberer_tas(tete_t **tete)
{
    free((*tete)->tas);
    free(*tete);
    *tete = NULL;
}

void afficher_tas(tete_t *tete)
{
    int *cour = tete->tas;
    int i = 0;

    fprintf(stdout,"contenu du tas : \n");

    while (i < tete->nb_elements + 1)
    {
        fprintf(stdout,"%d\t", *cour);
        cour++;
        i++;
    }
    fprintf(stdout,"\n");
}

int main()
{
    tete_t *tete = NULL;
    int resultat;
    int tab[7] = {0,1,2,3,4,5};

    init (&tete);
    afficher_tas(tete);
    construire(tab,tete);
    afficher_tas(tete);
    /*
    ajouter(tete,7);
    afficher_tas(tete);
    retirer_racine(tete,&resultat);
    afficher_tas(tete);
    */
}