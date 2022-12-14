#include "affichage.h"
#include "jeu.h"
#include "initialisation.h"

unsigned char surPassage(int mouse_x, int mouse_y, int x, int y, int largeur,int hauteur, ECE_City * eceCity){// duplication fonction à optimiser
    eceCity->souris.pos = getPosMouse(eceCity);
    if(eceCity->souris.pos.x >= x && eceCity->souris.pos.y >= y && eceCity->souris.pos.x <= x + 400 && eceCity->souris.pos.y <= y + 500){
        return 1;
    }
    return 0;
}

void affichage_mode(ECE_City * eceCity){
    BeginDrawing();
    DrawTexture(eceCity->image.image_choix,0,0,WHITE);
    DrawTexture(eceCity->image.tabBoutonMenu[BOUTON_QUITTER],0,0,WHITE);
    EndDrawing();
}
void affichage_menu(ECE_City eceCity){
  BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(eceCity.image.image_menu, 0,0, WHITE);

    for (int i = BOUTON_1; i <= BOUTON_QUITTER; ++i) {
        DrawTexture(eceCity.image.tabBoutonMenu[i],0,0, WHITE);
    }

    for (int i = BOUTON_1; i <= BOUTON_QUITTER; ++i) {
        if ((eceCity.image.tabBoutonMenu[i].x1 <= eceCity.souris.pos.x )&&(eceCity.souris.pos.x <= eceCity.image.tabBoutonMenu[i].x2 )&& ( eceCity.image.tabBoutonMenu[i].y1  <= eceCity.souris.pos.y)&&( eceCity.souris.pos.y <= eceCity.image.tabBoutonMenu[i].y2  )){
            DrawTexture(eceCity.image.tabBoutonMenu[i+NB_BOUTON_MENU],0,0, WHITE);
        }
    }
    if (eceCity.currentJeu == REGLE) {
        DrawTexture(eceCity.image.image_règles,0,0,WHITE);
    }
  EndDrawing();
}


void affichage_temps(ECE_City eceCity){
    // AFFICHAGE TEMPS REEL DE JEU
    if(eceCity.t.minutereel < 10 ){
        if(eceCity.t.secondereel < 10){
            DrawText(TextFormat(" 0%d : 0%d : 0%d \n", eceCity.t.heurereel, eceCity.t.minutereel,eceCity.t.secondereel), 120 , 75, 25 , BLACK);
        }
        else {
            DrawText(TextFormat(" 0%d : 0%d : %d \n", eceCity.t.heurereel, eceCity.t.minutereel,eceCity.t.secondereel), 120 , 75, 25 , BLACK);
        }
    }
    else{
        if(eceCity.t.secondereel < 10){
            DrawText(TextFormat(" 0%d : %d : 0%d \n", eceCity.t.heurereel, eceCity.t.minutereel,eceCity.t.secondereel), 120 , 75, 25, BLACK);
        }
        else {
            DrawText(TextFormat(" 0%d : %d : %d \n", eceCity.t.heurereel, eceCity.t.minutereel,eceCity.t.secondereel), 120 , 75, 25 , BLACK);
        }
    }
//AFFICHAGE TEMPS FICTIF
    if(eceCity.t.annee < 10 ){
        if(eceCity.t.mois < 10){
            DrawText(TextFormat("  années : 0%d mois :  0%d \n", eceCity.t.annee,eceCity.t.mois), 1630 , 55 , 25 , BLACK);
        }
        else {
            DrawText(TextFormat("  années : 0%d mois :  %d \n", eceCity.t.annee,eceCity.t.mois), 1630, 55, 25, BLACK);
        }
    }
    else{
        if(eceCity.t.mois < 10){
            DrawText(TextFormat("  années : %d mois :  0%d \n", eceCity.t.annee,eceCity.t.mois), 1630, 55 , 25 , BLACK);
        }
        else {
            DrawText(TextFormat("  années : %d mois :  %d \n", eceCity.t.annee,eceCity.t.mois), 1630, 55, 25 , BLACK);
        }
    }
}

void drawPlan0 () {
    DrawTriangle((Vector2){X_TAB + (NB_LIGNE)*TAILLE_CASE_X, Y_TAB - (NB_LIGNE)*TAILLE_CASE_Y},
                 (Vector2){X_TAB-10, Y_TAB + 10},
                 (Vector2){X_TAB + (NB_COLONNE)*TAILLE_CASE_X, Y_TAB + (NB_COLONNE)*TAILLE_CASE_Y + 20}
            , GRAY);
    DrawTriangle((Vector2){X_TAB + (NB_LIGNE)*TAILLE_CASE_X, Y_TAB - (NB_LIGNE)*TAILLE_CASE_Y},
                 (Vector2){X_TAB + (NB_COLONNE)*TAILLE_CASE_X, Y_TAB + (NB_COLONNE)*TAILLE_CASE_Y + 20},
                 (Vector2){X_TAB + NB_COLONNE * TAILLE_CASE_X + NB_LIGNE * TAILLE_CASE_X + 10, Y_TAB + (NB_COLONNE - NB_LIGNE) * TAILLE_CASE_Y + 10}
            , GRAY);


    DrawTriangle((Vector2){X_TAB + (NB_LIGNE)*TAILLE_CASE_X, Y_TAB - (NB_LIGNE)*TAILLE_CASE_Y - 10},
                 (Vector2){X_TAB-10, Y_TAB},
                 (Vector2){X_TAB + (NB_COLONNE)*TAILLE_CASE_X, Y_TAB + (NB_COLONNE)*TAILLE_CASE_Y + 10}
            , LIGHTGRAY);
    DrawTriangle((Vector2){X_TAB + (NB_LIGNE)*TAILLE_CASE_X, Y_TAB - (NB_LIGNE)*TAILLE_CASE_Y - 10},
                 (Vector2){X_TAB + (NB_COLONNE)*TAILLE_CASE_X, Y_TAB + (NB_COLONNE)*TAILLE_CASE_Y + 10},
                 (Vector2){X_TAB + NB_COLONNE * TAILLE_CASE_X + NB_LIGNE * TAILLE_CASE_X + 10, Y_TAB + (NB_COLONNE - NB_LIGNE) * TAILLE_CASE_Y}
            , LIGHTGRAY);
}

void drawPlan1 () {
    DrawTriangle((Vector2){X_TAB + (NB_COLONNE+1)*TAILLE_CASE_X, Y_TAB - (NB_LIGNE-1)*TAILLE_CASE_Y},
                 (Vector2){X_TAB + TAILLE_CASE_X-10,  (NB_COLONNE - NB_LIGNE +1) *TAILLE_CASE_Y+ Y_TAB + 10},
                 (Vector2){X_TAB + (NB_LIGNE+1)*TAILLE_CASE_X, Y_TAB + (NB_COLONNE+1)*TAILLE_CASE_Y + 20}
            , GRAY);
    DrawTriangle((Vector2){X_TAB + (NB_COLONNE+1)*TAILLE_CASE_X, Y_TAB - (NB_LIGNE-1)*TAILLE_CASE_Y},
                 (Vector2){X_TAB + (NB_LIGNE+1)*TAILLE_CASE_X, Y_TAB + (NB_COLONNE+1)*TAILLE_CASE_Y + 20},
                 (Vector2){X_TAB + (NB_COLONNE + NB_LIGNE+1) * TAILLE_CASE_X + 10, Y_TAB + TAILLE_CASE_Y + 10}
            , GRAY);


    DrawTriangle((Vector2){X_TAB + (NB_COLONNE+1)*TAILLE_CASE_X, Y_TAB - (NB_LIGNE-1)*TAILLE_CASE_Y - 10},
                 (Vector2){X_TAB + TAILLE_CASE_X-10, (NB_COLONNE - NB_LIGNE +1) *TAILLE_CASE_Y+ Y_TAB},
                 (Vector2){X_TAB + (NB_LIGNE+1)*TAILLE_CASE_X, Y_TAB + (NB_COLONNE+1)*TAILLE_CASE_Y + 10}
            , LIGHTGRAY);
    DrawTriangle((Vector2){X_TAB + (NB_COLONNE+1)*TAILLE_CASE_X, Y_TAB - (NB_LIGNE-1)*TAILLE_CASE_Y - 10},
                 (Vector2){X_TAB + (NB_LIGNE+1)*TAILLE_CASE_X, Y_TAB + (NB_COLONNE+1)*TAILLE_CASE_Y + 10},
                 (Vector2){X_TAB + (NB_COLONNE + NB_LIGNE+1) * TAILLE_CASE_X + 10, Y_TAB + TAILLE_CASE_Y}
            , LIGHTGRAY);
}

void affichagePlateau0 (ECE_City eceCity){
    drawPlan0();
    for (int i = 0; i < NB_LIGNE; ++i) {
        DrawLine(eceCity.tabCase[i][0].pos.x, eceCity.tabCase[i][0].pos.y, eceCity.tabCase[i][0].pos.x + TAILLE_CASE_X*NB_COLONNE, eceCity.tabCase[i][0].pos.y + TAILLE_CASE_Y*NB_COLONNE,BLACK);
    }
    DrawLine(eceCity.tabCase[34][0].pos.x+TAILLE_CASE_X, eceCity.tabCase[34][0].pos.y-TAILLE_CASE_Y, eceCity.tabCase[34][0].pos.x+TAILLE_CASE_X+ TAILLE_CASE_X*NB_COLONNE, eceCity.tabCase[34][0].pos.y-TAILLE_CASE_Y+ TAILLE_CASE_Y*NB_COLONNE,BLACK);

    for (int i = 0; i < NB_COLONNE; ++i) {
        DrawLine(eceCity.tabCase[0][i].pos.x, eceCity.tabCase[0][i].pos.y, eceCity.tabCase[0][i].pos.x + TAILLE_CASE_X*NB_LIGNE, eceCity.tabCase[0][i].pos.y - TAILLE_CASE_Y*NB_LIGNE,BLACK);
    }
    DrawLine(eceCity.tabCase[0][44].pos.x+TAILLE_CASE_X, eceCity.tabCase[0][44].pos.y+TAILLE_CASE_Y, eceCity.tabCase[0][44].pos.x+TAILLE_CASE_X + TAILLE_CASE_X*NB_LIGNE, eceCity.tabCase[0][44].pos.y+TAILLE_CASE_Y - TAILLE_CASE_Y*NB_LIGNE,BLACK);
}

void affichagePlateau1 (ECE_City eceCity){
    drawPlan1();
    for (int i = 0; i < NB_LIGNE; ++i) {
        DrawLine(eceCity.tabCase[i][0].pos.x, eceCity.tabCase[i][0].pos.y, eceCity.tabCase[i][0].pos.x + TAILLE_CASE_X*NB_COLONNE, eceCity.tabCase[i][0].pos.y - TAILLE_CASE_Y*NB_COLONNE,BLACK);
    }
    DrawLine(eceCity.tabCase[0][0].pos.x+TAILLE_CASE_X, eceCity.tabCase[0][0].pos.y+TAILLE_CASE_Y, eceCity.tabCase[0][0].pos.x + TAILLE_CASE_X*(NB_COLONNE+1), eceCity.tabCase[0][0].pos.y - TAILLE_CASE_Y*(NB_COLONNE-1),BLACK);

    for (int i = 0; i < NB_COLONNE; ++i) {
        DrawLine(eceCity.tabCase[0][i].pos.x+TAILLE_CASE_X, eceCity.tabCase[0][i].pos.y+TAILLE_CASE_Y, eceCity.tabCase[0][i].pos.x - TAILLE_CASE_X*(NB_LIGNE-1), eceCity.tabCase[0][i].pos.y - TAILLE_CASE_Y*(NB_LIGNE-1),BLACK);
    }
    DrawLine(eceCity.tabCase[0][44].pos.x+TAILLE_CASE_X*2, eceCity.tabCase[0][44].pos.y, eceCity.tabCase[0][44].pos.x+TAILLE_CASE_X*2 - TAILLE_CASE_X*NB_LIGNE, eceCity.tabCase[0][44].pos.y- TAILLE_CASE_Y*NB_LIGNE,BLACK);
}

void affichageCase (ECE_City * eceCity, int Ligne, int Colonne, Color color) {
    if (Ligne != -1 && Colonne != -1) {
        DrawTriangle((Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+2*TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y}, (Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y-TAILLE_CASE_Y}, (Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y+TAILLE_CASE_Y}, color);
        DrawTriangle((Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y-TAILLE_CASE_Y}, eceCity->tabCase[Ligne][Colonne].pos, (Vector2) {eceCity->tabCase[Ligne][Colonne].pos.x+TAILLE_CASE_X, eceCity->tabCase[Ligne][Colonne].pos.y+TAILLE_CASE_Y}, color);
    }
}

float posBatAffichage (ECE_City *eceCity, int Bat) {
    if (Bat == TERRAIN_VAGUE+eceCity->image.varTabImageBat)
        return POS_TERRAIN_VAGUE;
    if (Bat == RUINE+eceCity->image.varTabImageBat)
        return POS_RUINE;
    if (Bat == CABANE+eceCity->image.varTabImageBat)
        return POS_CABANE;
    if (Bat == MAISON+eceCity->image.varTabImageBat)
        return POS_MAISON;
    if (Bat == IMMEUBLE+eceCity->image.varTabImageBat)
        return POS_IMMEUBLE;
    if (Bat == GRATTE_CIEL+eceCity->image.varTabImageBat)
        return POS_GRATTE_CIEL;
    if (Bat == CHATEAU_EAU+eceCity->image.varTabImageBat)
        return POS_CHATEAU_EAU;
    if (Bat == CHATEAU_EAU_SENS)
        return POS_CHATEAU_EAU_SENS;
    if (Bat == CENTRALE_ELECTRIQUE+eceCity->image.varTabImageBat)
        return POS_CENTRALE_ELEC;
    if (Bat == CENTRALE_ELECTRIQUE_SENS)
        return POS_CENTRALE_ELEC_SENS;
    if (Bat == CASERNE_POMPIER+eceCity->image.varTabImageBat)
        return POS_CASERNE;
    if (Bat == CASERNE_POMPIER_SENS)
        return POS_CASERNE_SENS;
    return 0;
}

void affichageEtatCase (ECE_City * eceCity) {
    Sommet * parcoursGraphe = eceCity->graphe;
    while (parcoursGraphe != NULL) {
        parcoursGraphe->poser = false;

        parcoursGraphe = parcoursGraphe->next;
    }
    affichageEtatCaseBatiment(eceCity, parcoursGraphe);
}

void afficherRoute (ECE_City * eceCity, int i, int j) {
    if (eceCity->tabCase[i][j].Etat == ROUTE) {
        int route12 = detectionImageRoute(eceCity, i, j);
        DrawTexture(eceCity->image.tabImageRoute[route12], (int)eceCity->tabCase[i][j].pos.x + POS_ROUTE_X,
                    (int)eceCity->tabCase[i][j].pos.y - positionRoute(route12), WHITE);
    }
}

void affichageEtatCaseBatiment (ECE_City * eceCity, Sommet * parcoursGraphe) {
    if (eceCity->orientation == 0) {
        for (int i = NB_LIGNE-1; i > 0; --i) {
            for (int j = 0; j < NB_COLONNE; ++j) {
                afficherRoute(eceCity, i, j);
                if (eceCity->tabCase[i][j].Etat >= TERRAIN_VAGUE && eceCity->tabCase[i][j].Etat <= CASERNE_POMPIER) {
                    parcoursGraphe = eceCity->graphe;
                    while (parcoursGraphe != NULL) {
                        if (parcoursGraphe->batiment == eceCity->tabCase[i][j].Etat) {
                            if (i == parcoursGraphe->ligne && j == parcoursGraphe->colonne + eceCity->batiment[parcoursGraphe->batiment-1].largeur -1) {
                                if (!parcoursGraphe->poser) {
                                    DrawTexture(eceCity->image.tabImageBat[parcoursGraphe->batiment-2+eceCity->image.varTabImageBat],
                                                eceCity->tabCase[parcoursGraphe->ligne][parcoursGraphe->colonne].pos.x,
                                                eceCity->tabCase[parcoursGraphe->ligne][parcoursGraphe->colonne].pos.y - posBatAffichage(eceCity,parcoursGraphe->batiment+eceCity->image.varTabImageBat), WHITE);
                                    parcoursGraphe->poser = true;
                                }
                            }
                        }
                        parcoursGraphe = parcoursGraphe->next;
                    }
                }
            }
        }
    }
    if (eceCity->orientation == 1) {
        for (int i = NB_LIGNE-1; i > 0; --i) {
            for (int j = NB_COLONNE-1; j > 0; --j) {
                afficherRoute(eceCity, i, j);
                if (eceCity->tabCase[i][j].Etat >= TERRAIN_VAGUE && eceCity->tabCase[i][j].Etat <= CASERNE_POMPIER) {
                    parcoursGraphe = eceCity->graphe;
                    while (parcoursGraphe != NULL) {
                        if (parcoursGraphe->batiment == eceCity->tabCase[i][j].Etat) {
                            if (i == parcoursGraphe->ligne && j == parcoursGraphe->colonne) {
                                if (!parcoursGraphe->poser) {
                                    DrawTexture(eceCity->image.tabImageBat[parcoursGraphe->batiment-2 + eceCity->image.varTabImageBat + (parcoursGraphe->batiment>GRATTE_CIEL?NB_IMAGE_JEU:0)],
                                                eceCity->tabCase[parcoursGraphe->ligne+eceCity->batiment[parcoursGraphe->batiment-1].longueur-1][parcoursGraphe->colonne].pos.x,
                                                eceCity->tabCase[parcoursGraphe->ligne+eceCity->batiment[parcoursGraphe->batiment-1].longueur-1][parcoursGraphe->colonne].pos.y - posBatAffichage(eceCity, parcoursGraphe->batiment + (parcoursGraphe->batiment>GRATTE_CIEL?NB_IMAGE_JEU:0)), WHITE);
                                    parcoursGraphe->poser = true;
                                }
                            }
                        }
                        parcoursGraphe = parcoursGraphe->next;
                    }
                }
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

void affichageCaseDestruction (ECE_City * eceCity) {
    Sommet  * parcoursGraphe = eceCity->graphe;
    while (parcoursGraphe != NULL){
        if (parcoursGraphe->detruire == true) {
            for (int i = 0; i < NB_LIGNE; ++i) {
                for (int j = 0; j < NB_COLONNE; ++j) {
                    if (parcoursGraphe->ligne <= i &&
                        parcoursGraphe->ligne + eceCity->batiment[parcoursGraphe->batiment-1].longueur > i &&
                        parcoursGraphe->colonne <= j &&
                        parcoursGraphe->colonne + eceCity->batiment[parcoursGraphe->batiment-1].largeur > j) {
                        affichageCase(eceCity, i, j, RED);
                    }
                }
            }
        }

        parcoursGraphe = parcoursGraphe->next;
    }
}

void affichageElec1 (ECE_City * eceCity, Color color) {
    affichageEau(eceCity, color);
}



void affichageRoutePoser (ECE_City * eceCity) {
    for (int i = NB_LIGNE-1; i > 0; --i) {
        if (eceCity->orientation == 0) {
            for (int j = 0; j < NB_COLONNE; ++j) {
                afficherRoute(eceCity, i, j);
                if (eceCity->tabCase[i][j].Etat > ROUTE) {
                    affichageCase(eceCity, i, j, GRAY);
                }
            }
        }
        if (eceCity->orientation == 1) {
            for (int j = NB_COLONNE-1; j > 0; --j) {
                afficherRoute(eceCity, i, j);
                if (eceCity->tabCase[i][j].Etat > ROUTE) {
                    affichageCase(eceCity, i, j, GRAY);
                }
            }
        }
    }
}
void afficherBoiteOutils(ECE_City *eceCity){
    if(eceCity->image.boite_outils.perm || eceCity->image.boite_outils.temp){
        DrawTexture(eceCity->image.tabImageJeu[BOITE_OUTILS],0,0,WHITE);
        for (int i = 0; i < NB_BOUTON_BOS ; ++i) {
            if(eceCity->image.tabBoutonBOS[i].perm || eceCity->image.tabBoutonBOS[i].temp){
                DrawTexture(eceCity->image.tabImageJeu[i+5],0,0,WHITE);
            }
        }
    }


}


void affichageComplet (ECE_City * eceCity) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    switch (eceCity->modeJeu) {
        case COMMU:
            if(eceCity->nuit==1){
                DrawTexture(eceCity->image.tabImageJeu[FOND_COMMU_NUIT],0,0,WHITE);
            }
            else if(eceCity->nuit==0){
                DrawTexture(eceCity->image.tabImageJeu[FOND_COMMU],0,0,WHITE);
            }
            break;
        case CAPI:
            if(eceCity->nuit==1){
                DrawTexture(eceCity->image.tabImageJeu[FOND_CAPI_NUIT],0,0,WHITE);
            }
            else if(eceCity->nuit==0){
                DrawTexture(eceCity->image.tabImageJeu[FOND_CAPI],0,0,WHITE);
            }
    }
    DrawTexture(eceCity->image.image_affichage,0,0,WHITE);
    eceCity->orientation == 0?affichagePlateau0(*eceCity):affichagePlateau1(*eceCity);

    if (eceCity->etage == DESTRUCTION) {
        affichageRoutePoser(eceCity);
        affichageCaseDestruction(eceCity);
    }
    if (eceCity->etage == JEU && eceCity->EtatPlacement < ROUTE) {
        affichageCaseSelectionne(eceCity);
        affichageEtatCase(eceCity);
    }
    if (eceCity->etage == JEU && eceCity->EtatPlacement >= ROUTE) {
        affichageCaseSelectionne(eceCity);
        affichageRoutePoser(eceCity);
    }
    if (eceCity->etage == ELECTRICITE) {
        affichageElec(eceCity, YELLOW);
    }
    if (eceCity->etage == EAU) {
        affichageEau(eceCity, DARKBLUE);
    }
    if(eceCity->incendie.max ==1){
        DrawTexture(eceCity->image.image_flamme,0,0,WHITE);
    }
    DrawText(TextFormat("%d habitants", eceCity->nbHabitant),1710,240,25,BLACK);
    DrawText(TextFormat("%d ECE-Flouz", eceCity->eceFlouz), 1680, 148, 25, BLACK);
    DrawText(TextFormat("x%d", eceCity->t.speedTime), 1818, 1019, 25, BLACK);
    if(eceCity->impots!=0){
        DrawText(TextFormat(" +%d", eceCity->impots), 1550, 148, 30, BLUE);
    }
    afficherBoiteOutils(eceCity);


    affichage_temps(temps( eceCity));
    EndDrawing();
}