#include <stdio.h>
#include <stdlib.h>
#include "tasbin.h"

#define TAILLE 20   //taille maximale du tas

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
        return (i-1)/2;
    }
    else
    {
        return 0;
    }
}

void init(tete_t **tete)
{
    *tete = (tete_t *) malloc(sizeof(tete_t));
    (*tete)->fin = -1;
    (*tete)->tas = (int *) malloc(TAILLE * sizeof(int));
}

int estPlein(tete_t *tete)
{
    return tete->fin == TAILLE;
}

int estVide(tete_t *tete)
{
    return tete->fin == 0;
}

//verifier que ca marche si tas vide
void ajouter(tete_t *tete, int valeur)
{
    int *cour = tete->tas;
    int i;

    if (! estPlein(tete))
    {
        tete->fin++;
        i = tete->fin;
        cour += i;
        *cour = valeur;
        percolate_up(tete,i);
    }
}

void retirer_racine(tete_t *tete, int *res)
{
    int *cour = tete->tas;
    int i = 0;
    int *suiv = tete->tas;
    suiv += tete->fin;      //suivant pointe sur le dernier element de l'arbre

    //echanger racine et dernier element
    *res = *cour;
    *cour = *suiv;
    tete->fin--;
    percolate_down(tete,i);
}

//renvoie l'indice du fils max de i
int fils_min(tete_t *tete, int i)
{
    int prem = fils1(i);
    int deux = fils2(i);
    int min = prem;
    int *cour1 = tete->tas;
    int *cour2 = tete->tas;
    cour1 += prem;
    cour2 += deux;

    if (prem <= tete->fin && deux <= tete->fin)
    {
        if (*cour1 > *cour2)
        {
            min = deux;
        }
    }
    return min;    
}

//l'entier augmenter vaut 1 si l'utilisateur veut augmenter la priorite et -1 sinon
void modifier(tete_t *tete, int place, int augmenter)
{
    int *cour = tete->tas;
    cour += place;

    if (place < tete->fin)
    {
        *cour = *cour + augmenter;
        if (augmenter)
        {
            percolate_down(tete,place);
        }
        else
        {
            percolate_up(tete,place);
        }
    }
}

void construire(int tab[7], tete_t *tete)
{
    int i=0;
    int *cour = tete->tas;

    //on ajoute tous les elements sans se soucier de l'ordre impose par le tas
    for (i=0;i<7;i++)
    {
        *cour = tab[i];
        tete->fin++;
        cour++;
    }

    int j = tete->fin;

    j = pere(j);

    while (j>=0)
    {
        percolate_down(tete,j);
        j--;
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

    while (i < tete->fin + 1)
    {
        fprintf(stdout,"%d\t", *cour);
        cour++;
        i++;
    }
    fprintf(stdout,"\n");
}

void percolate_down(tete_t *tete, int place)
{
    int *cour = tete->tas;
    int *suiv = tete->tas;
    int i = place;
    int sauv;
    cour += i;
    i = fils_min(tete,i);
    suiv += i;

    while (*suiv < *cour && i <= tete->fin)
    {
        //echanger suiv et cour
        sauv = *suiv;
        *suiv = *cour;
        *cour = sauv;
        cour = suiv;
        i = fils_min(tete,i);
        suiv = tete->tas;
        suiv += i;
    }
}

void percolate_up(tete_t *tete, int place)
{
    int *cour = tete->tas, *prec = tete->tas;
    int i = place,sauv;
    cour += i;
    i = pere(i);
    prec += i;
    
    while (*prec > *cour && i>=0)
    {
        sauv = *cour;
        *cour = *prec;
        *prec = sauv;
        cour = prec;
        i = pere(i);
        prec = tete->tas;
        prec += i;
    }
}


void tri(tete_t *tete, int tab[7], int **liste)
{
    int i = 0;
    int *cour;

    construire(tab,tete);
    while (tete->fin >= 0)
    {
        cour = tete->tas;
        *(*liste + i) = *cour;
        i++;
        cour += tete->fin;
        *(tete->tas) = *cour;
        tete->fin--;
        percolate_down(tete,0);
    }
}

void afficher_tab(int **liste)
{
    for (int i=0;i<7;i++)
    {
        fprintf(stdout,"%d\t", *(*liste+i));
    }
}

int main()
{
    tete_t *tete = NULL;
    int resultat;       //sauvegarde la racine
    int tab[7] = {5,8,2,1,6,19,7};
    int *liste = NULL;
    liste = (int *) malloc(7*sizeof(int));

    if (liste)
    {
        init (&tete);

        /*
        construire(tab,tete);
        afficher_tas(tete);
        ajouter(tete,12);
        afficher_tas(tete);
        retirer_racine(tete,&resultat);
        fprintf(stdout,"valeur de la racine : %d\n",resultat);
        afficher_tas(tete);
        modifier(tete,2,1);
        afficher_tas(tete);
        */
        fprintf(stdout,"liste triee en ordre croissant :\t");
        tri(tete,tab,&liste);
        afficher_tab(&liste);
        fprintf(stdout,"\n");
    }
}