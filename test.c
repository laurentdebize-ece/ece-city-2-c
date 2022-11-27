#include "test.h"





ECE_City temps( ECE_City * eceCity){
    if (eceCity->t.speedTime > 0) {
        eceCity->upgrade.Upgrade = -1;
        eceCity->t.frames++;

        if( eceCity->incendie.num ==0){
            eceCity->incendie.num = rand()%12;
        }
        //TEMPS REEL
        if(eceCity->t.frames==60/eceCity->t.speedTime) {
            eceCity->t.secondereel++;
            if(eceCity->incendie.feu == 1){
                eceCity->incendie.var++;
                if(eceCity->incendie.var == 30){
                    eceCity->incendie.feu = 0;
                    eceCity->incendie.var=0;
                }
            }
            eceCity->upgrade.upgradeEnCours++;
            eceCity->upgrade.Upgrade = eceCity->upgrade.upgradeEnCours;
            eceCity->t.secondefictif++;
            eceCity->t.frames = 0;
            if(eceCity->t.secondereel==60){
                eceCity->t.minutereel++;
                eceCity->t.secondereel = 0;
                if(eceCity->t.minutereel==60){
                    eceCity->t.heurereel++;
                    eceCity->t.minutereel = 0;
                }
            }

            if(eceCity->t.secondefictif==15){
                eceCity->t.mois++;
                eceCity->upgrade.upgradeEnCours = 0;
                eceCity->t.secondefictif = 0;
                if(eceCity->t.mois == 12){
                    eceCity->t.annee ++;
                    eceCity->incendie.varSeconde = 1;
                    eceCity->t.mois =0;
                }
            }
        }
    }
    return *eceCity;
}
