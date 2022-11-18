#ifndef ECE_CITY_2_C_AFFICHAGE_H
#define ECE_CITY_2_C_AFFICHAGE_H

#include "ECE_CITY.h"
#include "test.h"

unsigned char surPassage(int mouse_x, int mouse_y, int x, int y, int largeur,int hauteur);
void affichage_menu(ECE_City eceCity);
void affichage_temps(ECE_City eceCity);
void affichagePlateau (ECE_City eceCity);
void affichageCase (ECE_City * eceCity, int Ligne, int Colonne, Color color);
void affichageEtatCase (ECE_City * eceCity);
void affichageCaseSelectionne (ECE_City * eceCity);

void affichageComplet (ECE_City * eceCity);

#endif //ECE_CITY_2_C_AFFICHAGE_H
