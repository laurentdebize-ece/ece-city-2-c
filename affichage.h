#ifndef ECE_CITY_2_C_AFFICHAGE_H
#define ECE_CITY_2_C_AFFICHAGE_H

#include "ECE_CITY.h"
#include "jeu.h"
#include "test.h"

unsigned char surPassage(int mouse_x, int mouse_y, int x, int y, int largeur,int hauteur);
void affichage_mode(ECE_City * eceCity);
float posBatAffichage (ECE_City *eceCity, int Bat);
void affichage_menu(ECE_City eceCity);
void affichage_temps(ECE_City eceCity);
void affichagePlateau0 (ECE_City eceCity);
void affichageCase (ECE_City * eceCity, int Ligne, int Colonne, Color color);
void affichageEtatCase (ECE_City * eceCity);
void afficherRoute (ECE_City * eceCity, int i, int j);
void affichageEtatCaseBatiment (ECE_City * eceCity, Sommet * parcoursGraphe);
void affichageCaseSelectionne (ECE_City * eceCity);
void affichageElec (ECE_City * eceCity, Color color);
void affichageRoutePoser (ECE_City * eceCity);

void affichageComplet (ECE_City * eceCity);

#endif //ECE_CITY_2_C_AFFICHAGE_H
