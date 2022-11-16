#include "affichage.h"
#include "initialisation.h"

void affichage_menu(ECE_City eceCity){
  BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(eceCity.image.image_menu, 0,0, WHITE);
    DrawTexture(eceCity.image.image_barre1,0,0, WHITE);
    DrawTexture(eceCity.image.image_barre2,0,0, WHITE);
    DrawTexture(eceCity.image.image_barre3,0,0, WHITE);

    //DrawRectangle(687,920,504, 88, GRAY)
    DrawTexture(eceCity.image.image_quitter,0,0, WHITE);



    if ((eceCity.image.image_barre1.x1 <= eceCity.souris.pos.x )&&(eceCity.souris.pos.x <= eceCity.image.image_barre1.x2 )&& ( eceCity.image.image_barre1.y1  <= eceCity.souris.pos.y)&&( eceCity.souris.pos.y <= eceCity.image.image_barre1.y2  )){
        DrawTexture(eceCity.image.image_barregrise1,0,0, WHITE);
    }
    if ((eceCity.image.image_barre2.x1 <= eceCity.souris.pos.x )&&(eceCity.souris.pos.x <= eceCity.image.image_barre2.x2 )&& ( eceCity.image.image_barre2.y1  <= eceCity.souris.pos.y)&&( eceCity.souris.pos.y <= eceCity.image.image_barre2.y2  )){
        DrawTexture(eceCity.image.image_barregrise2,0,0, WHITE);
    }
    if ((eceCity.image.image_barre3.x1 <= eceCity.souris.pos.x )&&(eceCity.souris.pos.x <= eceCity.image.image_barre3.x2 )&& ( eceCity.image.image_barre3.y1  <= eceCity.souris.pos.y)&&( eceCity.souris.pos.y <= eceCity.image.image_barre3.y2  )){
        DrawTexture(eceCity.image.image_barregrise3,0,0, WHITE);
    }
    if ((eceCity.image.image_quitter.x1 <= eceCity.souris.pos.x )&&(eceCity.souris.pos.x <= eceCity.image.image_quitter.x2 )&& ( eceCity.image.image_quitter.y1  <= eceCity.souris.pos.y)&&( eceCity.souris.pos.y <= eceCity.image.image_quitter.y2  )){
        DrawTexture(eceCity.image.image_quittergris,0,0, WHITE);
    }
  EndDrawing();
}


void affichage_temps(ECE_City eceCity){
    // AFFICHAGE TEMPS REEL DE JEU
    if(eceCity.t.minutereel < 10 ){
        if(eceCity.t.secondereel < 10){
            DrawText(TextFormat(" Temps de jeu : 0%d : 0%d : 0%d \n", eceCity.t.heurereel, eceCity.t.minutereel,eceCity.t.secondereel), 20 , 40 , 20 , BLACK);
        }
        else {
            DrawText(TextFormat(" Temps de jeu : 0%d : 0%d : %d \n", eceCity.t.heurereel, eceCity.t.minutereel,eceCity.t.secondereel), 20 , 40, 20 , BLACK);
        }
    }
    else{
        if(eceCity.t.secondereel < 10){
            DrawText(TextFormat(" Temps de jeu : 0%d : %d : 0%d \n", eceCity.t.heurereel, eceCity.t.minutereel,eceCity.t.secondereel), 20 , 40, 20, BLACK);
        }
        else {
            DrawText(TextFormat(" Temps de jeu : 0%d : %d : %d \n", eceCity.t.heurereel, eceCity.t.minutereel,eceCity.t.secondereel), 20 , 40 , 20 , BLACK);
        }
    }
//AFFICHAGE TEMPS FICTIF
    if(eceCity.t.annee < 10 ){
        if(eceCity.t.mois < 10){
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", eceCity.t.annee,eceCity.t.mois), 20 , 60 , 20 , BLACK);
        }
        else {
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", eceCity.t.annee,eceCity.t.mois), 20, 60 , 20, BLACK);
        }
    }
    else{
        if(eceCity.t.mois < 10){
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", eceCity.t.annee,eceCity.t.mois), 20, 60 , 20 , BLACK);
        }
        else {
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", eceCity.t.annee,eceCity.t.mois), 20, 60, 20 , BLACK);
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

void affichageElecEau (ECE_City * eceCity, Color color) {
    for (int i = 0; i < NB_LIGNE; ++i) {
        for (int j = 0; j < NB_COLONNE; ++j) {
            if (eceCity->tabCase[i][j].Etat == ROUTE) {
                affichageCase(eceCity, i, j, color);
            }
        }
    }
}

void affichageComplet (ECE_City * eceCity) {


    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (eceCity->etage == JEU) {
        affichageCaseSelectionne(eceCity);
        affichageEtatCase(eceCity);
    }
    if (eceCity->etage == ELECTRICITE) {
        affichageElecEau(eceCity, YELLOW);
    }
    if (eceCity->etage == EAU) {
        affichageElecEau(eceCity, DARKBLUE);
    }
    affichagePlateau(*eceCity);

    DrawText(TextFormat("[%d][%d]", eceCity->souris.posLigne, eceCity->souris.posColonne), 12  , 100, 20 , BLACK);
    DrawText(TextFormat("%s", eceCity->batiment[eceCity->EtatPlacement-1].nomBatiment), 12  , 120, 20 , BLACK);
    DrawText("Cabane --> C", 12, 140, 20, BLACK);
    DrawText("Maison --> N", 12, 160, 20, BLACK);
    DrawText("Immeuble --> I", 12, 180, 20, BLACK);
    DrawText("Gratte-ciel --> G", 12, 200, 20, BLACK);
    DrawText("Centrale elec --> E", 12, 220, 20, BLACK);
    DrawText("Chateau d eau --> H", 12, 240, 20, BLACK);
    DrawText("Caserne pompier --> P", 12, 260, 20, BLACK);
    DrawText("Route --> R", 12, 300, 20, BLACK);


    affichage_temps(temps(eceCity));

    EndDrawing();
}