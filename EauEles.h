#ifndef ECE_CITY_2_C_EAUELES_H
#define ECE_CITY_2_C_EAUELES_H

#include "ECE_CITY.h"

void ajoutListe (Liste ** filAttente, int id);
void nextFilAttente (Liste ** filAttente);
void etapeBFS (ECE_City * eceCity, int id, Liste ** filAttente, int * reserveEau, int idChateau);
void affichageEau (ECE_City * eceCity, Color color);

void repartitionEau (ECE_City * eceCity);


#endif //ECE_CITY_2_C_EAUELES_H
