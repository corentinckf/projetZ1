#include "dijkstra.h"

int main()
{
    graphe_t * graphe = init_graphe_labyrinth(C_LABY, L_LABY);
    int *distance = NULL, *parent = NULL;
    int code_retour = alloc_tableaux(N_SOMMET,&distance,&parent);
    if(code_retour)
    {

        /*DEBUT INITIALISATION TABLEAUX*/
        printf("Alloc tableaux : OK !\n");
        initialiser_tableaux(N_SOMMET, distance, parent);
        printf("Remplissement tableaux initiaux : OK !\n");
        /*FIN INITIALISATION TABLEAUX*/

    }else
        printf("Erreur alloc tableaux !\n");
    return 0;
}