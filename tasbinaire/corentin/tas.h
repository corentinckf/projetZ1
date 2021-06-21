#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element_t;

typedef struct tas{
    int nb_courant;
    int * contenu;
} tas_t;

/*Prototypes*/

int parent(tas_t*, int);
int leftChild(tas_t*, int);
int rightChild(tas_t*, int);

void echanger(int*, int*);


void init_tas(tas_t *);
void inserer_tas(tas_t *, int);
//void supprimer_tas(tas_t *);


