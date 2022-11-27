#include "jeu.h"
#include "initialisation.h"

#include "ECE_CITY.h"
#include "ChargeSauvegarde.h"

#define FPS 30

int main ()
{
    ECE_City eceCity = {0};

    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Raylib > Allegro");
    SetTargetFPS(FPS);


    initECECity(&eceCity);
    //load (&eceCity);

    fonction_principale(&eceCity);

    return 0;
}
