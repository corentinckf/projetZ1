#ifndef __DIJSKTRA_H__
#define __DIJSKTRA_H__


#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"
#include "labyrinth.h"
#include "connexe.h"


#define N_SOMMET 10
#define C_LABY 4
#define L_LABY 4

#define INFINI -1
#define AUCUN -2

//void Dijkstra(graphe_t *, )
int alloc_tableaux(int,int**,int**);
void initialiser_tableaux(int,int*,int*);


#endif