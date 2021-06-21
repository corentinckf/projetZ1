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

void echanger(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void init_tas(tas_t * t, int * liste, int taille)
{
    int i;
    t->contenu = (int *) malloc(taille * sizeof(int));
    if(t->contenu)
    {
        for(i = 0; liste[i] != '\0')
        {
            t->contenu[i] = liste[i];
            ++t->nb_courant;
        }
    }
    
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
        echanger(&t->contenu[i], &t->contenu[pere]);
        i = pere;
        pere = parent(t,i);
    }
}

//void supprimer_tas(tas_t * t){}

