#include "jeu.h"
#include "graphe.h"



int detectionImageRoute (ECE_City * eceCity, int ligne, int colonne) {
    if ((eceCity->tabCase[ligne-1][colonne].Etat == ROUTE || eceCity->tabCase[ligne+1][colonne].Etat == ROUTE) &&
        eceCity->tabCase[ligne][colonne+1].Etat != ROUTE && eceCity->tabCase[ligne][colonne-1].Etat != ROUTE) {
        return ROUTEBASHAUT-eceCity->orientation==0?0:1;
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat != ROUTE && eceCity->tabCase[ligne+1][colonne].Etat != ROUTE &&
        (eceCity->tabCase[ligne][colonne+1].Etat == ROUTE || eceCity->tabCase[ligne][colonne-1].Etat == ROUTE)) {
        return ROUTEHAUTBAS+eceCity->orientation;
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat != ROUTE && eceCity->tabCase[ligne+1][colonne].Etat == ROUTE &&
        eceCity->tabCase[ligne][colonne+1].Etat == ROUTE && eceCity->tabCase[ligne][colonne-1].Etat != ROUTE) {
        return ROUTEVIRAGEDROITE+eceCity->orientation;
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat != ROUTE && eceCity->tabCase[ligne+1][colonne].Etat == ROUTE &&
        eceCity->tabCase[ligne][colonne+1].Etat != ROUTE && eceCity->tabCase[ligne][colonne-1].Etat == ROUTE) {
        return ROUTEVIRAGEHAUT+eceCity->orientation;
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat == ROUTE && eceCity->tabCase[ligne+1][colonne].Etat != ROUTE &&
        eceCity->tabCase[ligne][colonne+1].Etat != ROUTE && eceCity->tabCase[ligne][colonne-1].Etat == ROUTE) {
        return ROUTEVIRAGEGAUCHE+eceCity->orientation;
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat == ROUTE && eceCity->tabCase[ligne+1][colonne].Etat != ROUTE &&
        eceCity->tabCase[ligne][colonne+1].Etat == ROUTE && eceCity->tabCase[ligne][colonne-1].Etat != ROUTE) {
        return ROUTEVIRAGEBAS-(eceCity->orientation==0?0:3);
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat == ROUTE && eceCity->tabCase[ligne+1][colonne].Etat == ROUTE &&
        eceCity->tabCase[ligne][colonne+1].Etat != ROUTE && eceCity->tabCase[ligne][colonne-1].Etat == ROUTE) {
        return ROUTETRIPLEHAUTDROITE-(eceCity->orientation==0?0:3);
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat != ROUTE && eceCity->tabCase[ligne+1][colonne].Etat == ROUTE &&
        eceCity->tabCase[ligne][colonne+1].Etat == ROUTE && eceCity->tabCase[ligne][colonne-1].Etat == ROUTE) {
        return ROUTETRIPLE+eceCity->orientation;
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat == ROUTE && eceCity->tabCase[ligne+1][colonne].Etat != ROUTE &&
        eceCity->tabCase[ligne][colonne+1].Etat == ROUTE && eceCity->tabCase[ligne][colonne-1].Etat == ROUTE) {
        return ROUTETRIPLEBASDROITE+eceCity->orientation;
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat == ROUTE && eceCity->tabCase[ligne+1][colonne].Etat == ROUTE &&
        eceCity->tabCase[ligne][colonne+1].Etat == ROUTE && eceCity->tabCase[ligne][colonne-1].Etat != ROUTE) {
        return ROUTETRIPLEBASGAUCHE+eceCity->orientation;
    }
    if (eceCity->tabCase[ligne-1][colonne].Etat == ROUTE && eceCity->tabCase[ligne+1][colonne].Etat == ROUTE &&
        eceCity->tabCase[ligne][colonne+1].Etat == ROUTE && eceCity->tabCase[ligne][colonne-1].Etat == ROUTE) {
        return ROUTECROISEMENT;
    }
    return ROUTEBASHAUT;
}

int positionRoute (int route) {
    if (route == ROUTEHAUTBAS || route == ROUTEVIRAGEGAUCHE) {
        return POS_ROUTE_Y_2;
    }
    return POS_ROUTE_Y;
}


void detection_case_souris_0 (ECE_City * eceCity) {
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


void detection_case_souris_1 (ECE_City * eceCity) {
    eceCity->souris.posLigne = -1;
    eceCity->souris.posColonne = -1;
    eceCity->souris.repLigne = eceCity->souris.pos.y + eceCity->coefTab*eceCity->souris.pos.x;
    eceCity->souris.repColonne = eceCity->souris.pos.y - eceCity->coefTab*eceCity->souris.pos.x;
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
        if (eceCity->tabCase[0][i].repColonne > eceCity->souris.repColonne){
            if (i!=NB_COLONNE-1 && eceCity->tabCase[0][i+1].repColonne < eceCity->souris.repColonne) {
                eceCity->souris.posColonne = i;
                i=NB_COLONNE;
            }
            else if (i == NB_COLONNE-1 && eceCity->tabCase[0][i].repColonne > eceCity->souris.repColonne) {
                if (eceCity->souris.repColonne > eceCity->tabCase[0][i].pos.y+TAILLE_CASE_Y + eceCity->coefTab*(eceCity->tabCase[0][i].pos.x+TAILLE_CASE_X)) {
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
    if (eceCity->orientation == 0)
        eceCity->souris.pos.y += 13;
    else
        eceCity->souris.pos.x -= 16;
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
    if (IsKeyPressed(KEY_RIGHT)) {
        if (eceCity->t.speedTime < 4){
            eceCity->t.frames = 0;
            eceCity->t.speedTime++;
        }
    }
    if (IsKeyPressed(KEY_LEFT)) {
        if (eceCity->t.speedTime > 0) {
            eceCity->t.frames = 0;
            eceCity->t.speedTime--;
        }
    }
    if (IsKeyPressed(KEY_O)) {
        if (eceCity->orientation == 0) {
            eceCity->orientation++;
            initCase1(eceCity);
        }
        else {
            eceCity->orientation--;
            initCase0(eceCity);
        }
    }
}

void detectionEtatPlacement (ECE_City * eceCity) {
    GetKeyPressed();
    detectEtat(eceCity, KEY_R, ROUTE);
    detectEtat(eceCity, KEY_T, TERRAIN_VAGUE);
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
        if (eceCity->eceFlouz > eceCity->batiment[eceCity->EtatPlacement-1].prix) {
            eceCity->eceFlouz -= eceCity->batiment[eceCity->EtatPlacement-1].prix;
            for (int i = 0; i < NB_LIGNE; ++i) {
                for (int j = 0; j < NB_COLONNE; ++j) {
                    if (eceCity->tabCase[i][j].selec == true) {
                        eceCity->tabCase[i][j].Etat = eceCity->EtatPlacement;
                    }
                }
            }
        }
        repartitionEau(eceCity);
        eceCity->EtatPlacement = VIDE;
    }
    else if (eceCity->EtatPlacement == ROUTE && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if (eceCity->eceFlouz > eceCity->batiment[eceCity->EtatPlacement-1].prix) {
            eceCity->eceFlouz -= eceCity->batiment[eceCity->EtatPlacement-1].prix;
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
}

void upgradeBatiment (ECE_City * eceCity) {
    if (eceCity->upgrade.Upgrade != -1){
        Sommet * parcoursGraphe = eceCity->graphe;
        while (parcoursGraphe != NULL) {
            if (parcoursGraphe->nbUpgrade == eceCity->upgrade.Upgrade && parcoursGraphe->consoEau == eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax) {
                if (parcoursGraphe->batiment >= TERRAIN_VAGUE && parcoursGraphe->batiment < GRATTE_CIEL) {
                    parcoursGraphe->batiment++;
                    for (int i = parcoursGraphe->ligne; i < parcoursGraphe->ligne + eceCity->batiment[parcoursGraphe->batiment-1].longueur; ++i) {
                        for (int j = parcoursGraphe->colonne; j < parcoursGraphe->colonne + eceCity->batiment[parcoursGraphe->batiment-1].largeur; ++j) {
                            eceCity->tabCase[i][j].Etat = parcoursGraphe->batiment;
                        }
                    }
                    repartitionEau(eceCity);
                }
            }
            parcoursGraphe = parcoursGraphe->next;
        }
    }
}

void fonctionJeu (ECE_City * eceCity) {
    eceCity->souris.pos = getPosMouse(eceCity);
    upgradeBatiment(eceCity);

    eceCity->orientation == 0?detection_case_souris_0(eceCity):detection_case_souris_1(eceCity);

    poserBatiment(eceCity);

    detectionEtatPlacement(eceCity);

    affichageComplet (eceCity);
}
void menu(ECE_City *eceCity){

    eceCity->souris.pos = getPosMouse(eceCity);
    affichage_menu(*eceCity);

    for (int i = BOUTON_1; i <= BOUTON_QUITTER; ++i) {
        if ((eceCity->image.tabBoutonMenu[i].x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabBoutonMenu[i].x2 )&& ( eceCity->image.tabBoutonMenu[i].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabBoutonMenu[i].y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
            eceCity->currentJeu= i==BOUTON_1?JEUMENU:i==BOUTON_2?CHARGER:i==BOUTON_3?REGLE:QUITTER;
        }
    }

}
void fonction_principale(ECE_City * eceCity){



    while (!eceCity->end){

        float f = (float)GetScreenWidth() / (float)GetScreenHeight();

        switch (eceCity->currentJeu) {
            case MENU:
                menu(eceCity);
                break;
            case JEUMENU:
                fonctionJeu(eceCity);
                break;
            case CHARGER:
                menu(eceCity);
                break;
            case REGLE:
                menu(eceCity);
                break;
            case QUITTER:
                eceCity->end = true;
                break;
        }
        if(WindowShouldClose()){
            eceCity->end = true;
        }
    }
    unloadImages(eceCity);
}

void Eau(ECE_City * eceCity, Sommet * ajoutGraphe, int ligne, int colonne) {



    // Ajout bfs eau prend l echemin le plus court
    // ce programme uniquemment une reprise j'ai pour l'instant rien fait
    if (eceCity->tabCase[ligne][colonne].Etat != VIDE) {
        if (eceCity->tabCase[ligne][colonne].Etat != ROUTE && ajoutGraphe->batiment == ROUTE ||
            eceCity->tabCase[ligne][colonne].Etat == ROUTE && ajoutGraphe->batiment) {
            Sommet * parcourGraphe = eceCity->graphe;

            if (eceCity->tabCase[ligne][colonne].Etat == ROUTE){

                while (parcourGraphe->ligne != ligne || parcourGraphe->colonne != colonne) {
                    parcourGraphe = parcourGraphe->next;
                }
            }
            else {
                while (ligne < parcourGraphe->ligne ||
                       ligne >= parcourGraphe->ligne + eceCity->batiment[parcourGraphe->batiment].longueur ||
                       colonne < parcourGraphe->colonne ||
                       colonne >= parcourGraphe->colonne + eceCity->batiment[parcourGraphe->batiment].largeur) {
                    parcourGraphe = parcourGraphe->next;
                }
            }

            if (ajoutGraphe->tabAdjacent == NULL) {
                ajoutGraphe->tabAdjacent = calloc(1, sizeof (int));
            }
            else {
                ajoutGraphe->tabAdjacent = realloc(ajoutGraphe->tabAdjacent, (ajoutGraphe->nbAdjacent+1)*sizeof (int));
            }
            ajoutGraphe->nbAdjacent++;
            ajoutGraphe->tabAdjacent[ajoutGraphe->nbAdjacent-1] = parcourGraphe->id;

            if (parcourGraphe->tabAdjacent == NULL) {
                parcourGraphe->tabAdjacent = calloc(1, sizeof (int));
            }
            else {
                parcourGraphe->tabAdjacent = realloc(parcourGraphe->tabAdjacent, (parcourGraphe->nbAdjacent+1)*sizeof (int));
            }
            parcourGraphe->nbAdjacent++;
            parcourGraphe->tabAdjacent[parcourGraphe->nbAdjacent-1] = ajoutGraphe->id;
        }
    }
}