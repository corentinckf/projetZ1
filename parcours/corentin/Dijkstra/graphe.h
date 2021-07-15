#ifndef __GRAPHE__H
#define __GRAPHE__H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int sommet;

typedef struct arrete
{
    sommet a;
    sommet b;
    int poids;
}arrete_t;

typedef struct graphe
{
    int n_sommet;
    int n_arrete;
    arrete_t * liste_arrete;
}graphe_t;

/*Prototypes*/
graphe_t * initialiser_graphe(int);
/*void ajouter_arrete(arrete_t *, graphe_t*);
void supprimer_arrete(int, graphe_t*);*/
void afficher_graphe(graphe_t *);

#endif