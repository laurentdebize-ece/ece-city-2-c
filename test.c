#include "test.h"


TIME temps(TIME *t){

    t->frames++;
    //TEMPMS REEL
    if(t->frames==60) {
        t->secondereel++;
        t->secondefictif++;
        t->frames = 0;
        if(t->secondereel==60){
            t->minutereel++;
            t->secondereel = 0;
            if(t->minutereel==60){
                t->heurereel++;
                t->minutereel = 0;
            }
        }
        if(t->secondefictif==15){
            t->mois++;
            t->secondefictif = 0;
            if(t->mois == 12){
                t->annee ++;
                t->mois =0;
            }
        }

    }
    return *t;
}
