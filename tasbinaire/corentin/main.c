#include "tas.h"

#define NB_MAX 10

element_t tasInit[] = {100,19,36,17,3,25,1,2,7};
element_t toAdd = 50;

int main()
{
    tas_t * tas1 = constructTas(NB_MAX, tasInit);
    //add(tas1,toAdd);
    return 0;
}