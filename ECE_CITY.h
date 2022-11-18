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
#define TAILLE_CASE_Y 12
#define NB_BAT 9
#define NB_IMAGE_BAT 5
#define NB_IMAGE_ROUTE 6

#define POS_CABANE 78
#define POS_MAISON 83
#define POS_IMMEUBLE 140
#define POS_GRATTE_CIEL 238

enum{VIDE, ROUTE, TERRAIN_VAGUE, CABANE, MAISON, IMMEUBLE, GRATTE_CIEL, CENTRALE_ELECTRIQUE, CHATEAU_EAU, CASERNE_POMPIER};
enum{MENU, JEUMENU, CHARGER, REGLE, QUITTER};
enum{JEU, ELECTRICITE, EAU};
enum{ROUTEHAUTBAS, ROUTEBASHAUT,ROUTEVIRAGEBAS,ROUTEVIRAGEHAUT,ROUTEVIRAGEDROITE,ROUTEVIRAGEGAUCHE};


typedef struct TIME{
    int frames;
    int secondereel ;
    int minutereel ;
    int heurereel ;
    int secondefictif ;
    int mois ;
    int annee ;
    int speedTime;
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


typedef struct image{
    Texture2D image_menu ;
    Texture2D image_barre1 ;
    Texture2D image_barre2 ;
    Texture2D image_barre3 ;
    Texture2D image_barregrise1;
    Texture2D image_barregrise2;
    Texture2D image_barregrise3;
    Texture2D image_quitter;
    Texture2D image_quittergris;

    Texture2D image_test;



    Texture2D tabImageBat [NB_IMAGE_BAT];
    Texture2D tabImageRoute [NB_IMAGE_ROUTE];

}IMAGE;
typedef struct Sommet{
    int id;
    int ligne;
    int colonne;
    int batiment;
    int nbAdjacent;
    int * tabAdjacent;
    int nbUpgrade;
    bool poser;
    struct Sommet * next;
}Sommet;

typedef struct {
    int Upgrade;
    int upgradeEnCours;
}toUpgrade;

typedef struct ece_city{
    float coefTab;
    Case tabCase [NB_LIGNE][NB_COLONNE];
    BatimentType batiment [NB_BAT];
    Souris souris;
    TIME t;
    int EtatPlacement;
    IMAGE image;
    int currentJeu;
    Sommet * graphe;
    int nbSommetGraphe;
    int idEnCours;
    int orientation;
    int etage;
    toUpgrade upgrade;
    bool end;
}ECE_City;

#endif //ECE_CITY_2_C_ECE_CITY_H
