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
#define TAILLE_CASE_Y 11
#define NB_BAT 9
#define NB_IMAGE_BAT 50
#define NB_IMAGE_ROUTE 11
#define NB_IMAGE_MENU 8

#define POS_ROUTE_X 1
#define POS_ROUTE_Y 14
#define POS_ROUTE_Y_2 15
#define POS_TERRAIN_VAGUE 50
#define POS_CABANE 78
#define POS_MAISON 83
#define POS_IMMEUBLE 140
#define POS_GRATTE_CIEL 238

enum{VIDE, ROUTE, TERRAIN_VAGUE, CABANE, MAISON, IMMEUBLE, GRATTE_CIEL, CENTRALE_ELECTRIQUE, CHATEAU_EAU, CASERNE_POMPIER,TERRAIN_VAGUE_NUIT, CABANE_NUIT, MAISON_NUIT, IMMEUBLE_NUIT, GRATTE_CIEL_NUIT};
enum{MENU, MODEJEU, JEUMENU, CHARGER, REGLE, QUITTER};
enum{DESTRUCTION, JEU, ELECTRICITE, EAU};
enum{CAPI, COMMU};
enum{ROUTEHAUTBAS, ROUTEBASHAUT,ROUTEVIRAGEDROITE,ROUTEVIRAGEHAUT,ROUTEVIRAGEGAUCHE,ROUTEVIRAGEBAS, ROUTETRIPLEBASDROITE, ROUTETRIPLEBASGAUCHE, ROUTETRIPLE, ROUTETRIPLEHAUTDROITE, ROUTECROISEMENT};
enum{BOUTON_1, BOUTON_2, BOUTON_3, BOUTON_QUITTER, BOUTON_1_GRIS, BOUTON_2_GRIS, BOUTON_3_GRIS, BOUTON_QUITTER_GRIS,NB_BOUTON_MENU = 4};

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
    int prix;
    char* nomBatiment;
}BatimentType;
//structure qui stock les info d'un batiment en general
// !!!!! pas de chaque batiment posés !!!!!
typedef struct {
    float x1;
    float x2;
    float y1;
    float y2;
}Bouton;


typedef struct image{
    int varTabImageBat;
    Bouton bouton_commu;
    Bouton bouton_capi;
    Texture2D image_menu ;
    Texture2D image_bonhomme;
    Texture2D image_fond ;
    Texture2D image_choix;
    Texture2D image_fond_nuit;
    Texture2D tabBoutonMenu [NB_IMAGE_MENU];
    Texture2D tabImageBat [NB_IMAGE_BAT];
    Texture2D tabImageRoute [NB_IMAGE_ROUTE];

}IMAGE;

typedef struct liste{
    int id;
    struct liste * next;
}Liste;

typedef struct Sommet{
    int id;
    int ligne;
    int colonne;
    int batiment;
    int nbAdjacent;
    int * tabAdjacent;
    int nbUpgrade;
    bool poser;
    int consoEau;
    bool decouverteBFS;
    int idChateauEau [NB_BAT];
    int nbChateauEau;
    int reserveChateauEau;
    struct Sommet * next;
    bool dejaEcrit;
}Sommet;

typedef struct {
    int Upgrade;
    int upgradeEnCours;
    int idEnCours;
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
    int orientation;
    int etage;
    int nuit;
    toUpgrade upgrade;
    bool end;
    int eceFlouz;
    int CapiCommu;
    int impots;
    int nbChateauEau;
    int nbHabitant;
    int modeJeu;
}ECE_City;

#endif //ECE_CITY_2_C_ECE_CITY_H
