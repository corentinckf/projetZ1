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