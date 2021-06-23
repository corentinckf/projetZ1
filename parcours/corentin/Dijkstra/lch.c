#include "lch.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------- */
/* alloc_cellule: Alloue l'espace mémoire et initialise une cellule et  */
/*                la renvoie                                            */
/*                                                                      */
/* En entrée: valeur, periode, num_usine des entiers nécessaires à      */
/*            l'initialisation de la cellule                            */
/*            Et suivant un pointeur sur la cellule suivante            */
/*                                                                      */
/* En sortie: Un pointeur sur une cellule                               */
/* -------------------------------------------------------------------- */
cellule * alloc_cellule(int valeur,cellule * suivant)
{
    cellule * element = (cellule *) malloc(sizeof(cellule));
    if(element)
    {
        element->valeur = valeur;
        element->suivant = suivant;
    }

    return element;   
}

/* -------------------------------------------------------------------- */
/* ajouter_cellule: Ajoute une cellule à l'addresse prec de la lch      */
/*                                                                      */
/* En entrée: Un double pointeur sur la cellule précédente              */
/*            Un pointeur sur la cellule à rajouter                     */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void ajouter_cellule(cellule ** prec, cellule * block)
{
    block->suivant = *prec;
    *prec = block;
}

/* -------------------------------------------------------------------- */
/* supprimer_cellule: Supprime une cellule d'adresse donnée en paramètre*/
/*                                                                      */
/* En entrée: Un double pointeur sur la cellule précédente              */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void supprimer_cellule(cellule ** prec)
{
    cellule * temp = *prec;
    *prec=(*prec)->suivant;
    free(temp);
}

/* -------------------------------------------------------------------- */
/* afficher_cellule: Affiche un liste chaînée                           */
/*                                                                      */
/* En entrée: Un pointeur sur une cellule (la tête de la lch)           */
/*            Un pointeur sur un stream (pour spécifier là où on veut   */
/*               qu'il y ai affichage)                                  */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void afficher_lch(cellule * tete, FILE * flux)
{
    cellule * courant = tete;

    while(courant)
    {
        fprintf(flux, " |%d| ", courant->valeur);
        courant = courant->suivant;
    }

}

/* -------------------------------------------------------------------- */
/* liberer_lch: Libère l'espace mémoire de la liste chaînée             */
/*                                                                      */
/* En entrée: Un double pointeur sur une cellule (la tête de la lch)    */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void liberer_lch(cellule ** tete)
{
    while(*tete)
    {
        supprimer_cellule(tete);
    }
}
