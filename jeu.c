#include "jeu.h"
#include "graphe.h"

void detection_case_souris (ECE_City * eceCity) {
    eceCity->souris.posLigne = -1;
    eceCity->souris.posColonne = -1;
    eceCity->souris.repLigne = eceCity->souris.pos.y - eceCity->coefTab*eceCity->souris.pos.x;
    eceCity->souris.repColonne = eceCity->souris.pos.y + eceCity->coefTab*eceCity->souris.pos.x;
    for (int i = 0; i < NB_LIGNE; ++i) {
        if (eceCity->tabCase[i][0].repLigne > eceCity->souris.repLigne){
            if (i!=NB_LIGNE-1 && eceCity->tabCase[i+1][0].repLigne < eceCity->souris.repLigne) {
                eceCity->souris.posLigne = i;
                i=NB_LIGNE;
            }
            else if (i == NB_LIGNE-1 && eceCity->tabCase[i][0].repLigne > eceCity->souris.repLigne) {
                if (eceCity->souris.repLigne > eceCity->tabCase[i][0].pos.y-TAILLE_CASE_Y - eceCity->coefTab*(eceCity->tabCase[i][0].pos.x+TAILLE_CASE_X)) {
                    eceCity->souris.posLigne = i;
                }
            }
        }
    }
    for (int i = 0; i < NB_COLONNE; ++i) {
        if (eceCity->tabCase[0][i].repColonne < eceCity->souris.repColonne){
            if (i!=NB_COLONNE-1 && eceCity->tabCase[0][i+1].repColonne > eceCity->souris.repColonne) {
                eceCity->souris.posColonne = i;
                i=NB_COLONNE;
            }
            else if (i == NB_COLONNE-1 && eceCity->tabCase[0][i].repColonne < eceCity->souris.repColonne) {
                if (eceCity->souris.repColonne < eceCity->tabCase[0][i].pos.y+TAILLE_CASE_Y + eceCity->coefTab*(eceCity->tabCase[0][i].pos.x+TAILLE_CASE_X)) {
                    eceCity->souris.posColonne = i;
                }
            }
        }
    }
    if(eceCity->souris.posLigne == -1 || eceCity->souris.posColonne == -1) {
        eceCity->souris.posLigne = -1;
        eceCity->souris.posColonne = -1;
    }
}

Vector2 getPosMouse (ECE_City * eceCity) {
    eceCity->souris.pos = GetMousePosition();
    eceCity->souris.pos.y += 13;
    return eceCity->souris.pos;
}

void detectEtat (ECE_City * eceCity, int key, int plac) {
    if (IsKeyPressed(key)) {
        if (eceCity->EtatPlacement == plac) {
            eceCity->EtatPlacement = VIDE;
        }
        else
            eceCity->EtatPlacement = plac;
    }
}

void detectEtage (ECE_City * eceCity) {
    if (IsKeyPressed(KEY_DOWN)) {
        if (eceCity->etage == JEU)
            eceCity->etage = ELECTRICITE;
        else if (eceCity->etage == ELECTRICITE)
            eceCity->etage = EAU;
    }
    if (IsKeyPressed(KEY_UP)) {
        if (eceCity->etage == ELECTRICITE)
            eceCity->etage = JEU;
        else if (eceCity->etage == EAU)
            eceCity->etage = ELECTRICITE;
    }
}

void detectionEtatPlacement (ECE_City * eceCity) {
    GetKeyPressed();
    detectEtat(eceCity, KEY_R, ROUTE);
    detectEtat(eceCity, KEY_C, CABANE);
    detectEtat(eceCity, KEY_N, MAISON);
    detectEtat(eceCity, KEY_I, IMMEUBLE);
    detectEtat(eceCity, KEY_G, GRATTE_CIEL);
    detectEtat(eceCity, KEY_E, CENTRALE_ELECTRIQUE);
    detectEtat(eceCity, KEY_H, CHATEAU_EAU);
    detectEtat(eceCity, KEY_P, CASERNE_POMPIER);
    detectEtage(eceCity);
}

bool detectionRouteBatiment (ECE_City * eceCity) {
    bool detection = false;
    for (int i = 0; i < NB_LIGNE; ++i) {
        for (int j = 0; j < NB_COLONNE; ++j) {
            if (eceCity->tabCase[i][j].selec == true) {
                if (eceCity->tabCase[i][j].Etat != VIDE){
                    return false;
                }
                else {
                    if (eceCity->tabCase[i+1][j].Etat == ROUTE || eceCity->tabCase[i-1][j].Etat == ROUTE || eceCity->tabCase[i][j+1].Etat == ROUTE || eceCity->tabCase[i][j-1].Etat == ROUTE){
                        detection = true;
                    }
                }
            }
        }
    }
    return detection;
}

void poserBatiment(ECE_City * eceCity) {
    if (eceCity->EtatPlacement != VIDE && eceCity->EtatPlacement != ROUTE && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            detectionRouteBatiment(eceCity)) {
        ajoutRouteGraphe(eceCity);
        for (int i = 0; i < NB_LIGNE; ++i) {
            for (int j = 0; j < NB_COLONNE; ++j) {
                if (eceCity->tabCase[i][j].selec == true) {
                    eceCity->tabCase[i][j].Etat = eceCity->EtatPlacement;
                }
            }
        }
    }
    else if (eceCity->EtatPlacement == ROUTE && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        for (int i = 0; i < NB_LIGNE; ++i) {
            for (int j = 0; j < NB_COLONNE; ++j) {
                if (eceCity->tabCase[i][j].selec == true && eceCity->tabCase[i][j].Etat == VIDE) {
                    eceCity->tabCase[i][j].Etat = eceCity->EtatPlacement;
                    ajoutRouteGraphe(eceCity);
                }
            }
        }
    }
}

void fonctionJeu (ECE_City * eceCity) {
    eceCity->souris.pos = getPosMouse(eceCity);
    detection_case_souris (eceCity);
    poserBatiment(eceCity);

    detectionEtatPlacement(eceCity);

    affichageComplet (eceCity);
}

void fonction_principale(ECE_City * eceCity){

    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Raylib > Allegro");

    SetTargetFPS(FPS);
    TIME t = {0};

    while (!WindowShouldClose()) {

        float f = (float)GetScreenWidth() / (float)GetScreenHeight();

        fonctionJeu(eceCity);

        /*if (IsKeyPressed(KEY_Y)){
            Sommet * parcourGraphe = eceCity->graphe;
            for (int i = 0; i < eceCity->nbSommetGraphe; ++i) {
                for (int j = 0; j < parcourGraphe->nbAdjacent; ++j) {
                    printf ("%d ", parcourGraphe->tabAdjacent[j]);
                }
                printf ("\n");
                parcourGraphe = parcourGraphe->next;
            }
        }*/

    }
}