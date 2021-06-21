#include <stdio.h>
#include <stdlib.h>

/*Prototypes*/

int ** creer(int*, int);
    /*crée à partir d'un ensemble E
    la partition où chaque élément est seul dans sa classe*/
int recuperer_classe(int**, int);
    /*prend en entrée un élément x∈E et renvoie un identifiant unique de la classe à laquelle appartient x
    */
/*void fusion();*/
    /*prend deux éléments x,y de E en entrée et fusionne les classes de x et de y
    dans la partition*/
/*void lister_classe();*/
    /*prend en entrée une étiquette de classe, et renvoie les éléments de cette classe,*/
/*void lister_partition();*/
    /*renvoie la liste des classes*/
