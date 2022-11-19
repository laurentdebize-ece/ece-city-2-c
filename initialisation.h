#ifndef ECE_CITY_2_C_INITIALISATION_H
#define ECE_CITY_2_C_INITIALISATION_H

#include "ECE_CITY.h"


void initECECity (ECE_City * eceCity);

void initBatiment (ECE_City * eceCity, char* fichier);
void initEtatCase (ECE_City * eceCity);
void initCase0 (ECE_City * ece_city);
void initCase1 (ECE_City * ece_city);
void initGraphe (ECE_City * eceCity);
void initSouris (ECE_City * eceCity);
void falseCaseSelec (ECE_City * eceCity);
void initBouton(ECE_City * eceCity);
void loadImages(ECE_City *eceCity);
void unloadImages(ECE_City *eceCity);

#endif //ECE_CITY_2_C_INITIALISATION_H
