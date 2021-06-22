#ifndef __KRUSKAL_H__
#define __KRUSKAL_H__

#include <stdio.h>
#include <stdlib.h>
#include "connexe.h"
#include "partition.h"
#include "graphe.h"

graphe_t *  kruskal(graphe_t *);
void afficher_liste_arrete(arrete_t *, int);

#endif
