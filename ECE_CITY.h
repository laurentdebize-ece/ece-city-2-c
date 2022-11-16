#ifndef ECE_CITY_2_C_ECE_CITY_H
#define ECE_CITY_2_C_ECE_CITY_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define FPS 60
#define NB_LIGNE 35
#define NB_COLONNE 45
#define X_TAB 100
#define Y_TAB 475
#define TAILLE_CASE_X 20
#define TAILLE_CASE_Y 13
#define NB_BAT 8

enum{VIDE, ROUTE, CABANE, MAISON, IMMEUBLE, GRATTE_CIEL, CENTRALE_ELECTRIQUE, CHATEAU_EAU, CASERNE_POMPIER};
enum{JEU, ELECTRICITE, EAU};

typedef struct TIME{
    int frames;
    int secondereel ;
    int minutereel ;
    int heurereel ;
    int secondefictif ;
    int mois ;
    int annee ;
}TIME;


typedef struct Case{
    Vector2 pos;
    float repLigne;
    float repColonne;
    bool selec;
    int Etat;
}Case;

typedef struct souris{
    int posLigne;
    int posColonne;
    int oldPosLigne;
    int oldPosColonne;
    Vector2 pos;
    float repLigne;
    float repColonne;
}Souris;

typedef struct batiment {
    int longueur;
    int largeur;
    int nbHabitantMax;
    int nbHabitant;
    int prix;
    char* nomBatiment;
}BatimentType;
//structure qui stock les info d'un batiment en general
// !!!!! pas de chaque batiment posés !!!!!

typedef struct Sommet{
    int id;
    int ligne;
    int colonne;
    int batiment;
    int nbAdjacent;
    int * tabAdjacent;
    struct Sommet * next;
}Sommet;

typedef struct ece_city{
    float coefTab;
    Case tabCase [NB_LIGNE][NB_COLONNE];
    BatimentType batiment [NB_BAT];
    Souris souris;
    TIME t;
    int EtatPlacement;
    Sommet * graphe;
    int nbSommetGraphe;
    int idEnCours;
    int orientation;
    int etage;
}ECE_City;

#endif //ECE_CITY_2_C_ECE_CITY_H
