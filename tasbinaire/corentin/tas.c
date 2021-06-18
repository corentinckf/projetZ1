#include "tas.h"

tas_t * initTas(int max){
    tas_t * tas = (tas_t *) malloc(sizeof(tas_t));
    if(tas)
    {
        tas->nb_courant = 0;
        tas->nb_max = max;
        tas->content = NULL;
    }
    
    return tas;
}

int parent(tas_t * tas, int el_indice)
{
    return (el_indice-1)/2;
}
int left(tas_t * tas, int el_indice)
{
    return (2*el_indice)+1;
}
int right(tas_t * tas, int el_indice)
{
    return (2*el_indice)+2;
}

int add(tas_t * tas, element_t el)
{
    int code_retour = 1;
    if(tas->nb_courant == tas->nb_max)
        code_retour = 0;
    else
    {
        /*On place l'élement à la fin de la liste dans un premmier temps*/
        ++(tas->nb_courant);
        int indice_dernier = tas->nb_courant - 1;
        tas->content[indice_dernier] = el;

        /*Ensuite on repositionne l'élément*/
        while (indice_dernier != 0 && tas->content[parent(tas,indice_dernier)] < tas->content[indice_dernier])
        {
            element_t temp = tas->content[parent(tas,indice_dernier)];
            tas->content[indice_dernier] = temp;
            tas->content[parent(tas,indice_dernier)] = el;
            indice_dernier = parent(tas,indice_dernier);
        }
        
    }
    
    return code_retour;
}
//void delete(tas_t tas);
//void aug(tas_t tas, element_t el);
//void dim(tas_t tas, element_t el);
tas_t * constructTas(int nbMax,element_t * el_array){
    tas_t * tas = initTas(nbMax);
    int length = sizeof( element_t ) * nbMax;
    tas->content = (element_t *) malloc(length);
    memcpy(tas->content, el_array, length);
    return tas;
}
