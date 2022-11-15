#include "jeu.h"
#include "initialisation.h"

#include "ECE_CITY.h"
#define FPS 60

int main ()
{
    ECE_City eceCity = {0};
    initECECity(&eceCity);
    //fonction3D(&eceCity);
    fonction_principale(&eceCity);
    return 0;
}
