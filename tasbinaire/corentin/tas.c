#include "tas.h"

tas_t * initTas(int max){
    tas_t * tas = NULL;
    tas->nb_courant = 0;
    tas->nb_max = max;
    tas->content = NULL;
    return tas;
}

element_t parent(tas_t * tas, int el_indice)
{
    return tas->content[(el_indice-1)/2];
}
element_t leftChild(tas_t * tas, int el_indice)
{
    return tas->content[(2*el_indice)+1];
}
element_t rightChild(tas_t * tas, int el_indice)
{
    return tas->content[(2*el_indice)+2];
}
void add(tas_t tas, element_t el);
void delete(tas_t tas);
void aug(tas_t tas, element_t el);
void dim(tas_t tas, element_t el);
int construct(tas_t tas,element_t * el_array);