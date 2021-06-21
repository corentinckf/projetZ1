#include "tas.h"

int parent(tas_t * tas, int el_indice)
{   
    int res = 0;
    if(el_indice) res = (el_indice-1)/2;
    return res;
}
int left(tas_t * tas, int el_indice)
{
    return (2*el_indice)+1;
}
int right(tas_t * tas, int el_indice)
{
    return (2*el_indice)+2;
}

void init_tas(tas_t * t)
{
    
}


void inserer_tas(tas_t * t, int el)
{
    
    int i = t->nb_courant - 1, pere = parent(t,i), tmp;
    /* On ajoute l'élément à la fin de la liste dans un premier temps*/
    t->contenu[i] = el;
    ++(t->nb_courant);

    /*On récuperer la position du père*/
    pere = parent(t,i);
    while(i > 0 && t->contenu[pere] < t->contenu[i])
    {
        tmp = t->contenu[pere];
        t->contenu[pere] = t->contenu[i];
        t->contenu[i] = tmp;
        i = pere;
        pere = parent(t,i);
    }
}

void supprimer_tas(tas_t * t)
{

}

