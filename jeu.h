#ifndef ECE_CITY_2_C_JEU_H
#define ECE_CITY_2_C_JEU_H

#include "ECE_CITY.h"
#include "affichage.h"
#include "test.h"
#include "initialisation.h"


int detectionImageRoute (ECE_City * eceCity, int ligne, int colonne);
void detection_case_souris_0 (ECE_City * eceCity);
void detection_case_souris_1 (ECE_City * eceCity);
Vector2 getPosMouse (ECE_City * eceCity);
void detectEtat (ECE_City * eceCity, int key, int plac);
void detectEtage (ECE_City * eceCity);
void detectionEtatPlacement (ECE_City * eceCity);
bool detectionRouteBatiment (ECE_City * eceCity);
void poserBatiment(ECE_City * eceCity);
void upgradeBatiment (ECE_City * eceCity);
void fontionJeu (ECE_City * eceCity);
void menu(ECE_City * eceCity);
void fonction_principale(ECE_City * eceCity);
void Eau(ECE_City * eceCity, Sommet * ajoutGraphe, int ligne, int colonne);

#endif //ECE_CITY_2_C_JEU_H
