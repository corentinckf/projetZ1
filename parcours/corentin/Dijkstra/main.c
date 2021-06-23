#include "dijkstra.h"

int main()
{
    graphe_t * graphe = init_graphe_labyrinth(C_LABY, L_LABY);
    tas_binaire_t * tas = NULL;
    int *distance = NULL, *parent = NULL,*visite;
    int code_retour = alloc_tableaux(N_SOMMET,&distance,&parent,&visite);
    if(code_retour)
    {

        /*DEBUT INITIALISATION TABLEAUX*/
        printf("Alloc tableaux : OK !\n");
        initialiser_tableaux(4,graphe, distance, parent, visite, &tas);
        printf("Remplissement tableaux initiaux : OK !\n");
        for(int i = 0; i < N_SOMMET;++i)
        {
            printf("%d : d %d p %d v %d\n",i,distance[i], parent[i], visite[i]);
        }
        /*FIN INITIALISATION TABLEAUX*/
        //fichier_graphiz(tas);

    }else
        printf("Erreur alloc tableaux !\n");
    return 0;
}