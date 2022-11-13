#include "affichage.h"
#include "initialisation.h"

void affichage_temps(TIME t){
    // AFFICHAGE TEMPS REEL DE JEU
    if(t.minutereel < 10 ){
        if(t.secondereel < 10){
            DrawText(TextFormat(" Temps de jeu : 0%d : 0%d : 0%d \n", t.heurereel, t.minutereel,t.secondereel), 20 , 40 , 20 , BLACK);
        }
        else {
            DrawText(TextFormat(" Temps de jeu : 0%d : 0%d : %d \n", t.heurereel, t.minutereel,t.secondereel), 20 , 40, 20 , BLACK);
        }
    }
    else{
        if(t.secondereel < 10){
            DrawText(TextFormat(" Temps de jeu : 0%d : %d : 0%d \n", t.heurereel, t.minutereel,t.secondereel), 20 , 40, 20, BLACK);
        }
        else {
            DrawText(TextFormat(" Temps de jeu : 0%d : %d : %d \n", t.heurereel, t.minutereel,t.secondereel), 20 , 40 , 20 , BLACK);
        }
    }
//AFFICHAGE TEMPS FICTIF
    if(t.annee < 10 ){
        if(t.mois < 10){
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", t.annee,t.mois), 20 , 60 , 20 , BLACK);
        }
        else {
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", t.annee,t.mois), 20, 60 , 20, BLACK);
        }
    }
    else{
        if(t.mois < 10){
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", t.annee,t.mois), 20, 60 , 20 , BLACK);
        }
        else {
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", t.annee,t.mois), 20, 60, 20 , BLACK);
        }
    }

}

void affichagePlateau (ECE_City eceCity){
    for (int i = 0; i < NB_LIGNE; ++i) {
        DrawLine(eceCity.tabCase[i][0].pos.x, eceCity.tabCase[i][0].pos.y, eceCity.tabCase[i][0].pos.x + TAILLE_CASE_X*NB_COLONNE, eceCity.tabCase[i][0].pos.y + TAILLE_CASE_Y*NB_COLONNE,BLACK);
    }
    DrawLine(eceCity.tabCase[34][0].pos.x+TAILLE_CASE_X, eceCity.tabCase[34][0].pos.y-TAILLE_CASE_Y, eceCity.tabCase[34][0].pos.x+TAILLE_CASE_X+ TAILLE_CASE_X*NB_COLONNE, eceCity.tabCase[34][0].pos.y-TAILLE_CASE_Y+ TAILLE_CASE_Y*NB_COLONNE,BLACK);

    for (int i = 0; i < NB_COLONNE; ++i) {
        DrawLine(eceCity.tabCase[0][i].pos.x, eceCity.tabCase[0][i].pos.y, eceCity.tabCase[0][i].pos.x + TAILLE_CASE_X*NB_LIGNE, eceCity.tabCase[0][i].pos.y - TAILLE_CASE_Y*NB_LIGNE,BLACK);
    }
    DrawLine(eceCity.tabCase[0][44].pos.x+TAILLE_CASE_X, eceCity.tabCase[0][44].pos.y+TAILLE_CASE_Y, eceCity.tabCase[0][44].pos.x+TAILLE_CASE_X + TAILLE_CASE_X*NB_LIGNE, eceCity.tabCase[0][44].pos.y+TAILLE_CASE_Y - TAILLE_CASE_Y*NB_LIGNE,BLACK);
}

void affichageCase (ECE_City * eceCity, int Ligne, int Colonne, Color color) {
    if (Ligne != -1 && Colonne != -1) {
        DrawTriangle((Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+2*TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y}, (Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y-TAILLE_CASE_Y}, (Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y+TAILLE_CASE_Y}, color);
        DrawTriangle((Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y-TAILLE_CASE_Y}, eceCity->tabCase[Ligne][Colonne].pos, (Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y+TAILLE_CASE_Y}, color);
    }
}

void affichageEtatCase (ECE_City * eceCity) {
    for (int i = 0; i < NB_LIGNE; ++i) {
        for (int j = 0; j < NB_COLONNE; ++j) {
            if (eceCity->tabCase[i][j].Etat == ROUTE) {
                affichageCase(eceCity, i, j, BLACK);
            }
            if (eceCity->tabCase[i][j].Etat == CABANE) {
                affichageCase(eceCity, i, j, BROWN);
            }
            if (eceCity->tabCase[i][j].Etat == MAISON) {
                affichageCase(eceCity, i, j, DARKGREEN);
            }
            if (eceCity->tabCase[i][j].Etat == IMMEUBLE) {
                affichageCase(eceCity, i, j, GRAY);
            }
            if (eceCity->tabCase[i][j].Etat == GRATTE_CIEL) {
                affichageCase(eceCity, i, j, LIGHTGRAY);
            }
            if (eceCity->tabCase[i][j].Etat == CENTRALE_ELECTRIQUE) {
                affichageCase(eceCity, i, j, YELLOW);
            }
            if (eceCity->tabCase[i][j].Etat == CHATEAU_EAU) {
                affichageCase(eceCity, i, j, DARKBLUE);
            }
            if (eceCity->tabCase[i][j].Etat == CASERNE_POMPIER) {
                affichageCase(eceCity, i, j, RED);
            }
        }
    }
}

void affichageCaseSelectionne (ECE_City * eceCity) {
    falseCaseSelec(eceCity);
    if (eceCity->souris.posLigne != -1 && eceCity->souris.posColonne != -1) {
        if (eceCity->EtatPlacement != VIDE && eceCity->EtatPlacement != ROUTE && eceCity->souris.posLigne+eceCity->batiment[eceCity->EtatPlacement-1].longueur <= NB_LIGNE && eceCity->souris.posColonne+eceCity->batiment[eceCity->EtatPlacement-1].largeur <= NB_COLONNE) {
            for (int i = 0; i < NB_LIGNE; ++i) {
                for (int j = 0; j < NB_COLONNE; ++j) {
                    if (i >= eceCity->souris.posLigne && i < eceCity->souris.posLigne+eceCity->batiment[eceCity->EtatPlacement-1].longueur){
                        if (j >= eceCity->souris.posColonne && j < eceCity->souris.posColonne+eceCity->batiment[eceCity->EtatPlacement-1].largeur){
                            affichageCase(eceCity, i, j, BLUE);
                            eceCity->tabCase[i][j].selec = true;
                        }
                    }
                }
            }
        }
        else if (eceCity->EtatPlacement == VIDE || eceCity->EtatPlacement == ROUTE){
            affichageCase(eceCity, eceCity->souris.posLigne, eceCity->souris.posColonne, BLUE);
            eceCity->tabCase[eceCity->souris.posLigne][eceCity->souris.posColonne].selec = true;
        }
    }
}


void affichageComplet (ECE_City * eceCity) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    affichageCaseSelectionne(eceCity);
    affichageEtatCase(eceCity);
    affichagePlateau(*eceCity);

    DrawText(TextFormat("[%d][%d]", eceCity->souris.posLigne, eceCity->souris.posColonne), 12  , 100, 20 , BLACK);
    DrawText(TextFormat("%d", eceCity->EtatPlacement), 12  , 120, 20 , BLACK);


    affichage_temps(temps(&eceCity->t));

    EndDrawing();
}