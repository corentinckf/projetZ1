#include "tas.h"

#define NB_MAX 15




int main()
{
    
    element_t toAdd = 50;
    element_t tasInit[] = {100,19,36,17,3,25,1,2,7};
    tas_t * tas1 = constructTas(NB_MAX, tasInit);

    for(int i = 0; i < 9;++i)
    {
        ++tas1->nb_courant;
        tas1->content[i] = tasInit[i];
        
    }
    add(tas1,toAdd);
    return 0;
}