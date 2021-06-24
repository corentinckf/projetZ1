#ifndef __LABYRINTH_H__
#define __LABYRINTH_H__

#include <stdio.h>
#include <stdlib.h>

#include "partition.h"
#include "connexe.h"
#include "graphe.h"
#include "kruskal.h"

graphe_t * init_graphe_labyrinth(int, int);
void fisher_yates_shuffle(graphe_t *);
void change(sommet * a, sommet * b);

#endif
