#include <stdio.h>
#include <stdlib.h>

typedef int element_t;
typedef struct tas{
    element_t * content;
    int nb_max;
    int nb_courant;
} tas_t;

/*Prototypes*/
tas_t * initTas(int);
element_t parent(tas_t, int);
element_t leftChild(tas_t, int);
element_t rightChild(tas_t, int);
void add(tas_t, element_t);
void delete(tas_t);
void aug(tas_t, element_t);
void dim(tas_t, element_t);
int construct(tas_t,element_t *);

