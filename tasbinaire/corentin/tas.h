#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element_t;
typedef struct tas{
    int nb_max;
    int nb_courant;
    element_t * content;
} tas_t;

/*Prototypes*/

tas_t * initTas(int);
int parent(tas_t*, int);
int leftChild(tas_t*, int);
int rightChild(tas_t*, int);
int add(tas_t*, element_t);
/*
void delete(tas_t);
void aug(tas_t, element_t);
void dim(tas_t, element_t);
*/
tas_t * constructTas(int,element_t *);
void interchanger(element_t *x, element_t *y);

