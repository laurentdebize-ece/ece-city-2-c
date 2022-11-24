#include "test.h"


ECE_City temps(TIME *t, ECE_City * eceCity){
    if (eceCity->t.speedTime > 0) {
        eceCity->upgrade.Upgrade = -1;
        t->frames++;
        //TEMPMS REEL
        if(t->frames==60/eceCity->t.speedTime) {
            t->secondereel++;
            eceCity->upgrade.upgradeEnCours++;
            eceCity->upgrade.Upgrade = eceCity->upgrade.upgradeEnCours;
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
                eceCity->upgrade.upgradeEnCours = 0;
                t->secondefictif = 0;
                if(t->mois == 12){
                    t->annee ++;
                    t->mois =0;
                }
            }
        }
    }
    return *eceCity;
}
