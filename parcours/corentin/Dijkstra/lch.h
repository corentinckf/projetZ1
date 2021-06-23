#ifndef __CELLULE_H__
#define __CELLULE_H__

#include <stdio.h>
#include <stdlib.h>

//Définition de la structure cellule pour la liste chaînée
typedef struct cellule
{

    int valeur;
    struct cellule * suivant;

}cellule;

//Prototypes des fonctions sur les listes chaînées
cellule * alloc_cellule(int, cellule *);
void ajouter_cellule(cellule ** , cellule *);
void supprimer_cellule(cellule **);
void afficher_lch(cellule *, FILE *);
void liberer_lch(cellule **);

#endif
