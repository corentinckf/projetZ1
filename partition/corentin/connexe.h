#ifndef __CONNEXE_H__
#define __CONNEXE_H__


#include <stdio.h>
#include <stdlib.h>
#include "lch.h"

#define MAT_SIZE 10

int ** init_adj_mat(int, int);
void afficher_matrice(int **, int, int);
void visualiser_matrice(int **, int, int);

#endif