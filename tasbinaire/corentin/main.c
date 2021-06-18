#include "tas.h"

#define NB_MAX 15




int main()
{
    
    element_t toAdd = 50;
    element_t tasInit[] = {100,19,36,17,3,25,1,2,7};
    tas_t * tas1 = initTas(NB_MAX);

    memcpy(tas1->content, tasInit, sizeof(element_t) * NB_MAX);

    add(tas1,toAdd);
    return 0;
}