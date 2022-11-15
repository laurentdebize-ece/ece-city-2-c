#ifndef ECE_CITY_2_C_JEU_H
#define ECE_CITY_2_C_JEU_H

#include "ECE_CITY.h"
#include "affichage.h"
#include "test.h"


void detection_case_souris (ECE_City * eceCity);
Vector2 getPosMouse (ECE_City * eceCity);
void detectEtat (ECE_City * eceCity, int key, int plac);
void detectionEtatPlacement (ECE_City * eceCity);
bool detectionRouteBatiment (ECE_City * eceCity);
void poserBatiment(ECE_City * eceCity);
void fonction_principale(ECE_City * eceCity);

#endif //ECE_CITY_2_C_JEU_H
