#ifndef ECE_CITY_2_C_ECE_CITY_H
#define ECE_CITY_2_C_ECE_CITY_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define FPS 60
#define NB_LIGNE 35
#define NB_COLONNE 45
#define X_TAB 100
#define Y_TAB 475
#define TAILLE_CASE_X 20
#define TAILLE_CASE_Y 11
#define NB_BAT 10
#define NB_IMAGE_BAT 50
#define NB_IMAGE_ROUTE 11
#define NB_IMAGE_MENU 8
#define NB_IMAGE_ICONE 5
#define NB_IMAGE_JEU 12
#define NB_BOUTON_BOS 12


#define POS_ROUTE_X 1
#define POS_ROUTE_Y 14
#define POS_ROUTE_Y_2 15
#define POS_TERRAIN_VAGUE 50
#define POS_RUINE 56
#define POS_CABANE 78
#define POS_MAISON 83
#define POS_IMMEUBLE 140
#define POS_GRATTE_CIEL 238
#define POS_CHATEAU_EAU 121
#define POS_CHATEAU_EAU_SENS 143
#define POS_CENTRALE_ELEC 100
#define POS_CENTRALE_ELEC_SENS 122
#define POS_CASERNE 81
#define POS_CASERNE_SENS 104

enum{VIDE, ROUTE, TERRAIN_VAGUE, CABANE, MAISON, IMMEUBLE, GRATTE_CIEL, RUINE, CENTRALE_ELECTRIQUE, CHATEAU_EAU, CASERNE_POMPIER, ROUTE_NUIT,TERRAIN_VAGUE_NUIT, CABANE_NUIT, MAISON_NUIT, IMMEUBLE_NUIT, GRATTE_CIEL_NUIT,RUINE_NUIT, CENTRAL_ELECTRIQUE_NUIT, CHATEAU_EAU_NUIT, CASERNE_POMPIER_NUIT, CENTRALE_ELECTRIQUE_SENS, CHATEAU_EAU_SENS, CASERNE_POMPIER_SENS};
enum{MENU, MODEJEU, JEUMENU, CHARGER, REGLE, QUITTER};
enum{DESTRUCTION, JEU, ELECTRICITE, EAU};
enum{CAPI, COMMU};
enum{ROUTEHAUTBAS, ROUTEBASHAUT,ROUTEVIRAGEDROITE,ROUTEVIRAGEHAUT,ROUTEVIRAGEGAUCHE,ROUTEVIRAGEBAS, ROUTETRIPLEBASDROITE, ROUTETRIPLEBASGAUCHE, ROUTETRIPLE, ROUTETRIPLEHAUTDROITE, ROUTECROISEMENT};
enum{BOUTON_1, BOUTON_2, BOUTON_3, BOUTON_QUITTER, BOUTON_1_GRIS, BOUTON_2_GRIS, BOUTON_3_GRIS, BOUTON_QUITTER_GRIS,NB_BOUTON_MENU = 4};
enum{FOND_COMMU, FOND_COMMU_NUIT, FOND_CAPI, FOND_CAPI_NUIT, BOITE_OUTILS, BOS_DESTRUCTION, BOS_ROUTE, BOS_BAT, BOS_MAISON,BOS_EAU,BOS_POMPIER,BOS_ELEC,BOS_VITESSEMOINS, BOS_PAUSE, BOS_VITESSEPLUS, BOS_SAUVEGARDE, BOS_QUITTER};


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
    int feu;
}BatimentType;
//structure qui stock les info d'un batiment en general
// !!!!! pas de chaque batiment posés !!!!!


typedef struct incendie{

    int varSeconde;
    int num;
    int var;
    int feu;
    int max;
    int proba;
}Incendie;

typedef struct {
    float x1;
    float x2;
    float y1;
    float y2;
    bool perm;
    bool temp;
    int clique;
    int equivalenceClavier;
}Bouton;


typedef struct image{
    int varTabImageBat;
    Bouton bouton_commu;
    Bouton bouton_capi;
    Bouton boite_outils;
    Bouton tabBoutonBOS[NB_BOUTON_BOS];
    Texture2D image_menu ;
    Texture2D image_bonhomme;
    Texture2D image_choix;
    Texture2D image_flamme;
    Texture2D image_affichage;
    Texture2D tabBoutonMenu [NB_IMAGE_MENU];
    Texture2D tabImageBat [NB_IMAGE_BAT];
    Texture2D tabImageRoute [NB_IMAGE_ROUTE];
    Texture2D tabImageJeu[NB_IMAGE_JEU];
}IMAGE;

typedef struct liste{
    int id;
    struct liste * next;
}Liste;

typedef struct Sommet{
    int id;
    int feu;
    int ligne;
    int colonne;
    int batiment;
    int nbAdjacent;
    Liste * tabAdjacent;
    int nbUpgrade;
    bool poser;
    bool detruire;
    bool dejaEcrit;
    bool decouverteBFS;
    bool decouvertePasApasElec;
    int reserveChateauEau;
    int reserveCentral;
    int idChateauEau [NB_IMAGE_BAT];
    int idCEntral [NB_IMAGE_BAT];
    int nbChateauEau;
    int nbCentral;
    int consoEau;
    int consoElec;
    struct Sommet * next;
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
    Incendie incendie;
    int EtatPlacement;
    IMAGE image;
    Bouton bouton;
    int currentJeu;
    Sommet * graphe;
    int nbSommetGraphe;
    int orientation;
    int etage;
    int nuit;
    toUpgrade upgrade;
    bool end;
    int eceFlouz;
    int impots;
    int nbChateauEau;
    int nbCentral;
    int nbCaserne;
    int nbHabitant;
    int modeJeu;
    int key;
}ECE_City;

#endif //ECE_CITY_2_C_ECE_CITY_H
