#ifndef __PARTITION_H__
#define __PARTITION_H__


#include <stdio.h>
#include <stdlib.h>
#include "lch.h"

#define PART_SIZE 11

/*Prototypes*/
void afficher_partition(int **, int, int);
void afficher_hauteurs(int *, int);
int ** creer(int, int **);
    /*crée à partir d'un ensemble E
    la partition où chaque élément est seul dans sa classe*/
int recuperer_classe(int**, int);
    /*prend en entrée un élément x∈E et renvoie un identifiant unique de la classe à laquelle appartient x
    */
void fusion(int **, int, int);
    /*prend deux éléments x,y de E en entrée et fusionne les classes de x et de y
    dans la partition*/
void fusion_arbo(int **,int *, int, int);
int * lister_classe(int **, int, int);
    /*prend en entrée une étiquette de classe, et renvoie les éléments de cette classe,*/
void lister_partition(int **, int);
    /*renvoie la liste des classes*/

void visualiser_graph(int **, int);


#endif