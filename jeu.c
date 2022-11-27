#include "jeu.h"
#include "graphe.h"


// Déclenche des incendies aléatoirement, les incendies sont réglés si il y a une caserne sinon deviennent des ruines
void incendie(ECE_City*eceCity){
    temps(eceCity);
    Sommet * parcoursGraphe = eceCity->graphe;
    ajoutCaserne(eceCity);
    while(parcoursGraphe != NULL) {
        if (parcoursGraphe->batiment >= TERRAIN_VAGUE && parcoursGraphe->batiment <= GRATTE_CIEL){
            if( eceCity->incendie.varSeconde == 1&&eceCity->incendie.feu==0){
                eceCity->incendie.proba= rand() %2500;
                if(eceCity->incendie.proba == 1&&parcoursGraphe->feu ==0){
                    eceCity->incendie.feu=1;
                    eceCity->incendie.max=1;
                    parcoursGraphe->feu = 1;
                    if(eceCity->incendie.feu==1&&eceCity->nbCaserne!=0&&eceCity->incendie.var==0){
                        eceCity->incendie.feu=0;
                        parcoursGraphe->feu = 0;
                    }
                    else if(eceCity->incendie.feu==1&&eceCity->incendie.var==0){
                        parcoursGraphe->batiment=TERRAIN_VAGUE-2;
                        eceCity->incendie.feu=0;
                        parcoursGraphe->feu = 2;
                    }
                }

                    if(eceCity->incendie.feu==0&&parcoursGraphe->feu == 1){
                        parcoursGraphe->feu = 0;
                    }

            }
        }
        parcoursGraphe = parcoursGraphe->next;
    }
}

//Les habitants payent chaque mois la cagnotte globale
void impots( ECE_City * eceCity,Sommet * parcoursGraphe){
    if(parcoursGraphe->nbUpgrade == eceCity->upgrade.Upgrade){
        eceCity->impots =  (eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax)* 10;
        eceCity->eceFlouz = eceCity->eceFlouz + eceCity->impots;
    }
}

//Boite à outils pour selectionner à la souris les foncytionnalités qu'on souhaite
void boiteOutils(ECE_City *eceCity){
    eceCity->souris.pos = getPosMouse(eceCity);
    eceCity->image.boite_outils.temp = false;
    if((eceCity->image.boite_outils.x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.boite_outils.x2 )&& ( eceCity->image.boite_outils.y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.boite_outils.y2  )){
        eceCity->image.boite_outils.temp = true;
    }
    if(eceCity->image.boite_outils.perm==false&&(eceCity->image.boite_outils.x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.boite_outils.x2 )&& ( eceCity->image.boite_outils.y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.boite_outils.y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
        eceCity->image.boite_outils.perm = true;
    }
    else if(eceCity->image.boite_outils.perm&&(eceCity->image.boite_outils.x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.boite_outils.x2 )&& ( eceCity->image.boite_outils.y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.boite_outils.y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
        eceCity->image.boite_outils.perm = false;
        for (int i = 0; i < NB_BOUTON_BOS; ++i) {
            eceCity->image.tabBoutonBOS[i].perm = false;
        }
    }
    if(eceCity->image.boite_outils.perm || eceCity->image.boite_outils.temp) {
        for (int i = 0; i < NB_BOUTON_BOS; ++i) {
            eceCity->image.tabBoutonBOS[i].temp = false;
            if (i < 3 || i >= 3 && eceCity->image.tabBoutonBOS[2].perm == true) {
                if((eceCity->image.tabBoutonBOS[i].x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabBoutonBOS[i].x2 )&& ( eceCity->image.tabBoutonBOS[i].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabBoutonBOS[i].y2  )){
                    eceCity->image.tabBoutonBOS[i].temp = true;
                }
                if(eceCity->image.tabBoutonBOS[i].perm==false&&(eceCity->image.tabBoutonBOS[i].x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabBoutonBOS[i].x2 )&& ( eceCity->image.tabBoutonBOS[i].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabBoutonBOS[i].y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                    eceCity->image.tabBoutonBOS[i].perm = true;
                    if (i != 0) {
                        eceCity->etage = JEU;
                    }
                    if (i < 3) {
                        for (int j = 0; j < NB_BOUTON_BOS; ++j) {
                            if (j != i) {
                                eceCity->image.tabBoutonBOS[j].perm = false;
                            }
                        }
                    }
                    if (i >= 3) {
                        for (int j = 0; j < NB_BOUTON_BOS; ++j) {
                            if (j != i && j != 2) {
                                eceCity->image.tabBoutonBOS[j].perm = false;
                            }
                        }
                    }
                    if(eceCity->image.tabBoutonBOS[i].clique==0){
                        eceCity->image.tabBoutonBOS[i].clique = 1;
                    }
                }
                else if(eceCity->image.tabBoutonBOS[i].perm&&(eceCity->image.tabBoutonBOS[i].x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabBoutonBOS[i].x2 )&& ( eceCity->image.tabBoutonBOS[i].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabBoutonBOS[i].y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                    eceCity->image.tabBoutonBOS[i].perm = false;
                    if(eceCity->image.tabBoutonBOS[i].clique==2){
                        eceCity->image.tabBoutonBOS[i].clique = 3;
                    }
                }
            }
        }

    }
}

//Détermine quelle image de route est necessaire selon la ligne ou la cologne et selon si d'autre route sont a cote ou non
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

//Detection sur quelle case est la souris sur la map isométrique
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

//Récupération des données de position de la souris
Vector2 getPosMouse (ECE_City * eceCity) {
    eceCity->souris.pos = GetMousePosition();
    if (eceCity->orientation == 0)
        eceCity->souris.pos.y += 13;
    else
        eceCity->souris.pos.x -= 16;
    return eceCity->souris.pos;
}

//Détection de l'etat (ce qu'on peut poser) au clavier ou a la sourie
void detectEtat (ECE_City * eceCity, int key, int plac) {
    for (int i=0; i < NB_BOUTON_BOS ; ++i) {
        if(key == eceCity->image.tabBoutonBOS[i].equivalenceClavier){
            eceCity->bouton.equivalenceClavier = i;
        }
    }
    if (IsKeyPressed(key)||eceCity->image.tabBoutonBOS[eceCity->bouton.equivalenceClavier].clique==1) {
        if (eceCity->EtatPlacement == plac) {
            eceCity->EtatPlacement = VIDE;
        }
        else{
            eceCity->EtatPlacement = plac;
            eceCity->image.tabBoutonBOS[eceCity->bouton.equivalenceClavier].clique = 2;
        }
    }
    else if (eceCity->image.tabBoutonBOS[eceCity->bouton.equivalenceClavier].clique == 3){
        eceCity->EtatPlacement = VIDE;
        eceCity->image.tabBoutonBOS[eceCity->bouton.equivalenceClavier].clique = 0;
    }

    for (int i = 0; i < NB_BOUTON_BOS; ++i) {
        if(eceCity->image.tabBoutonBOS[eceCity->bouton.equivalenceClavier].perm == false){
            eceCity->bouton.equivalenceClavier = 0;
        }
    }
}

//Detection destrction ou de l'etage (du point de vue)
void detectEtage (ECE_City * eceCity) {
    eceCity->souris.pos = getPosMouse(eceCity);

    if (IsKeyDown(KEY_Y)) {
        printf ("ok");
    }
    if (eceCity->image.tabBoutonBOS[0].clique == 1) {
        eceCity->image.tabBoutonBOS[0].clique = 2;
        eceCity->etage = DESTRUCTION;
    }
    if (eceCity->image.tabBoutonBOS[0].clique == 3) {
        eceCity->image.tabBoutonBOS[0].clique = 0;
        eceCity->etage = JEU;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        if (eceCity->etage < EAU)
            eceCity->etage++;
    }
    if (IsKeyPressed(KEY_UP)) {
        if (eceCity->etage > DESTRUCTION)
            eceCity->etage--;
    }
    if (eceCity->etage != JEU) {
        eceCity->EtatPlacement = VIDE;
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        if (eceCity->t.speedTime < 4){
            eceCity->t.frames = 0;
            eceCity->t.speedTime++;
        }
    }
    if((eceCity->image.tabImageJeu[FOND_COMMU].x1<= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabImageJeu[FOND_COMMU].x2 )&& ( eceCity->image.tabImageJeu[FOND_COMMU].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabImageJeu[FOND_COMMU].y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))){
        if (eceCity->t.speedTime < 4){
            eceCity->t.frames = 0;
            eceCity->t.speedTime++;
        }
    }
    if((eceCity->image.tabImageJeu[FOND_CAPI].x1<= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabImageJeu[FOND_CAPI].x2 )&& ( eceCity->image.tabImageJeu[FOND_CAPI].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabImageJeu[FOND_CAPI].y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))){
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
    if((eceCity->image.tabImageJeu[FOND_COMMU].x1<= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabImageJeu[FOND_COMMU].x2 )&& ( eceCity->image.tabImageJeu[FOND_COMMU].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabImageJeu[FOND_COMMU].y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
        if (eceCity->t.speedTime > 0) {
            eceCity->t.frames = 0;
            eceCity->t.speedTime--;
        }
    }
    if((eceCity->image.tabImageJeu[FOND_CAPI].x1<= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabImageJeu[FOND_CAPI].x2 )&& ( eceCity->image.tabImageJeu[FOND_CAPI].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabImageJeu[FOND_CAPI].y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
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

//identification des touches a appuyer selon ce que l'on souhaite poser
void detectionEtatPlacement (ECE_City * eceCity) {
    GetKeyPressed();
    getPosMouse(eceCity);
    detectEtat(eceCity, KEY_R, ROUTE);
    detectEtat(eceCity, KEY_T, TERRAIN_VAGUE);
    detectEtat(eceCity, KEY_E, CENTRALE_ELECTRIQUE);
    detectEtat(eceCity, KEY_H, CHATEAU_EAU);
    detectEtat(eceCity, KEY_P, CASERNE_POMPIER);
    detectEtage(eceCity);
    modeNuit(eceCity);
}
//Verifie si on peut poser un batiment
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

//Placement des routes et des batiments sur la map selon les coordonnees
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
        for (int i = 3; i < NB_BOUTON_BOS; ++i) {
            eceCity->image.tabBoutonBOS[i].perm = false;
            eceCity->image.tabBoutonBOS[i].clique = 0;
        }
        repartitionEau(eceCity);
        repartitionElec(eceCity);

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
                        repartitionEau(eceCity);
                        repartitionElec(eceCity);
                    }
                }
            }
        }
    }
}

//evolution des batiments
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
                    repartitionElec(eceCity);
                }
            }
            parcoursGraphe = parcoursGraphe->next;
        }
    }
}


void upgradeBatimentCOMMUNISTE (ECE_City * eceCity) {
    if (eceCity->upgrade.Upgrade != -1){
        Sommet * parcoursGraphe = eceCity->graphe;
        while (parcoursGraphe != NULL) {
            impots(eceCity,parcoursGraphe);
            if (parcoursGraphe->nbUpgrade == eceCity->upgrade.Upgrade && parcoursGraphe->consoEau == eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax) {
                if (parcoursGraphe->batiment >= TERRAIN_VAGUE && parcoursGraphe->batiment < GRATTE_CIEL &&
                    parcoursGraphe->reserveChateauEau >= eceCity->batiment[parcoursGraphe->batiment].nbHabitantMax - eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax &&
                    parcoursGraphe->reserveCentral >= eceCity->batiment[parcoursGraphe->batiment].nbHabitantMax - eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax) {
                    parcoursGraphe->batiment++;
                    for (int i = parcoursGraphe->ligne; i < parcoursGraphe->ligne + eceCity->batiment[parcoursGraphe->batiment-1].longueur; ++i) {
                        for (int j = parcoursGraphe->colonne; j < parcoursGraphe->colonne + eceCity->batiment[parcoursGraphe->batiment-1].largeur; ++j) {
                            eceCity->tabCase[i][j].Etat = parcoursGraphe->batiment;
                        }
                    }
                    repartitionEau(eceCity);
                    repartitionElec(eceCity);
                }
                else if (parcoursGraphe->batiment == RUINE &&
                    parcoursGraphe->reserveChateauEau >= eceCity->batiment[parcoursGraphe->batiment].nbHabitantMax - eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax &&
                    parcoursGraphe->reserveCentral >= eceCity->batiment[parcoursGraphe->batiment].nbHabitantMax - eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax) {
                    parcoursGraphe->batiment = CABANE;
                    for (int i = parcoursGraphe->ligne; i < parcoursGraphe->ligne + eceCity->batiment[parcoursGraphe->batiment-1].longueur; ++i) {
                        for (int j = parcoursGraphe->colonne; j < parcoursGraphe->colonne + eceCity->batiment[parcoursGraphe->batiment-1].largeur; ++j) {
                            eceCity->tabCase[i][j].Etat = parcoursGraphe->batiment;
                        }
                    }
                    repartitionEau(eceCity);
                    repartitionElec(eceCity);
                }
            }
            parcoursGraphe = parcoursGraphe->next;
        }
    }
}

void downgradeBatimentCOMMUNISTE (ECE_City * eceCity) {
    if (eceCity->upgrade.Upgrade != -1){
        Sommet * parcoursGraphe = eceCity->graphe;
        while (parcoursGraphe != NULL) {
            if (parcoursGraphe->nbUpgrade == eceCity->upgrade.Upgrade && parcoursGraphe->consoEau < eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax || parcoursGraphe->consoElec < eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax) {
                if (parcoursGraphe->batiment > CABANE && parcoursGraphe->batiment <= GRATTE_CIEL) {
                    parcoursGraphe->batiment--;
                    for (int i = parcoursGraphe->ligne; i < parcoursGraphe->ligne + eceCity->batiment[parcoursGraphe->batiment-1].longueur; ++i) {
                        for (int j = parcoursGraphe->colonne; j < parcoursGraphe->colonne + eceCity->batiment[parcoursGraphe->batiment-1].largeur; ++j) {
                            eceCity->tabCase[i][j].Etat = parcoursGraphe->batiment;
                        }
                    }
                    repartitionEau(eceCity);
                    repartitionElec(eceCity);
                }
                else if (parcoursGraphe->batiment == CABANE) {
                    parcoursGraphe->batiment = RUINE;
                    for (int i = parcoursGraphe->ligne; i < parcoursGraphe->ligne + eceCity->batiment[parcoursGraphe->batiment-1].longueur; ++i) {
                        for (int j = parcoursGraphe->colonne; j < parcoursGraphe->colonne + eceCity->batiment[parcoursGraphe->batiment-1].largeur; ++j) {
                            eceCity->tabCase[i][j].Etat = parcoursGraphe->batiment;
                        }
                    }
                    repartitionEau(eceCity);
                    repartitionElec(eceCity);
                }
            }
            parcoursGraphe = parcoursGraphe->next;
        }
    }
}

void modeNuit(ECE_City * eceCity){
    if(IsKeyPressed(KEY_SPACE)){
        if(eceCity->nuit==0){
            eceCity->nuit = 1;
            eceCity->image.varTabImageBat = 0;
        }
        else if(eceCity->nuit==1){
            eceCity->nuit = 0;
            eceCity->image.varTabImageBat = 0;
            }
    }
}

void detruireBatiment (ECE_City * eceCity){
    Sommet * parcoursGraphe = eceCity->graphe;

    while (parcoursGraphe != NULL) {
        parcoursGraphe->detruire = false;
        parcoursGraphe = parcoursGraphe->next;
    }
    if (eceCity->souris.posLigne != -1 && eceCity->souris.posColonne != -1 && eceCity->tabCase[eceCity->souris.posLigne][eceCity->souris.posColonne].Etat != VIDE) {
        parcoursGraphe = eceCity->graphe;
        while (parcoursGraphe->ligne > eceCity->souris.posLigne ||
                parcoursGraphe->ligne + eceCity->batiment[parcoursGraphe->batiment-1].longueur <= eceCity->souris.posLigne ||
                parcoursGraphe->colonne > eceCity->souris.posColonne ||
                parcoursGraphe->colonne + eceCity->batiment[parcoursGraphe->batiment-1].largeur <= eceCity->souris.posColonne) {
            parcoursGraphe = parcoursGraphe->next;
        }
        parcoursGraphe->detruire = true;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        parcoursGraphe = eceCity->graphe;
        while (parcoursGraphe != NULL) {
            if (parcoursGraphe->detruire == true) {
                if (parcoursGraphe->batiment == CHATEAU_EAU) {
                    eceCity->nbChateauEau--;
                }
                if (parcoursGraphe->batiment == CENTRALE_ELECTRIQUE) {
                    eceCity->nbCentral--;
                }
                eceCity->nbSommetGraphe--;
                Sommet * parcoursGraphe2 = eceCity->graphe;
                while (parcoursGraphe2 != NULL) {
                    if (parcoursGraphe2->tabAdjacent != NULL) {
                        if (parcoursGraphe2->tabAdjacent->id == parcoursGraphe->id) {
                            parcoursGraphe2->tabAdjacent = parcoursGraphe2->tabAdjacent->next;
                            parcoursGraphe2->nbAdjacent--;
                        }
                        else {
                            Liste * parcoursTabAdjacent = parcoursGraphe2->tabAdjacent;
                            while (parcoursTabAdjacent->next != NULL) {
                                if (parcoursTabAdjacent->next->id == parcoursGraphe->id) {
                                    parcoursTabAdjacent->next = parcoursTabAdjacent->next->next;
                                    parcoursGraphe2->nbAdjacent--;
                                }
                                if (parcoursTabAdjacent->next == NULL) {
                                    break;
                                }
                                parcoursTabAdjacent = parcoursTabAdjacent->next;
                            }

                        }
                    }
                    parcoursGraphe2 = parcoursGraphe2->next;
                }
                for (int i = 0; i < NB_LIGNE; ++i) {
                    for (int j = 0; j < NB_COLONNE; ++j) {
                        if (parcoursGraphe->ligne <= i &&
                            parcoursGraphe->ligne + eceCity->batiment[parcoursGraphe->batiment-1].longueur > i &&
                            parcoursGraphe->colonne <= j &&
                            parcoursGraphe->colonne + eceCity->batiment[parcoursGraphe->batiment-1].largeur > j) {
                            eceCity->tabCase[i][j].Etat = VIDE;
                        }
                    }
                }
                if (eceCity->graphe->batiment == CHATEAU_EAU) {
                    eceCity->nbChateauEau--;
                }
                if (parcoursGraphe == eceCity->graphe) {
                    eceCity->graphe = eceCity->graphe->next;
                }
                else {
                    parcoursGraphe2 = eceCity->graphe;
                    while (parcoursGraphe2->next != parcoursGraphe){
                        parcoursGraphe2 = parcoursGraphe2->next;
                    }
                    parcoursGraphe2->next = parcoursGraphe2->next->next;
                }
                repartitionEau(eceCity);
                repartitionElec(eceCity);
            }
            parcoursGraphe = parcoursGraphe->next;
        }
    }
}

void Upgrade (ECE_City * eceCity) {
    if (eceCity->modeJeu == COMMU) {
        upgradeBatimentCOMMUNISTE(eceCity);
        downgradeBatimentCOMMUNISTE(eceCity);
    }
    if (eceCity->modeJeu == CAPI) {
        upgradeBatimentCOMMUNISTE(eceCity);
        downgradeBatimentCOMMUNISTE(eceCity);
    }
}

void poserDetruireBatiment (ECE_City * eceCity) {
    if (eceCity->etage == JEU) {
        poserBatiment(eceCity);
    }
    if (eceCity->etage == DESTRUCTION) {
        detruireBatiment(eceCity);
    }
}

void fonctionJeu (ECE_City * eceCity) {
    eceCity->souris.pos = getPosMouse(eceCity);
    boiteOutils(eceCity);
    Upgrade(eceCity);
    eceCity->orientation == 0?detection_case_souris_0(eceCity):detection_case_souris_1(eceCity);

    poserDetruireBatiment(eceCity);

    detectionEtatPlacement(eceCity);
    incendie(eceCity);
    affichageComplet (eceCity);
}
void modeJeu ( ECE_City* eceCity){
    eceCity->souris.pos = getPosMouse(eceCity);
    affichage_mode(eceCity);

    if((eceCity->image.bouton_commu.x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.bouton_commu.x2 )&& ( eceCity->image.bouton_commu.y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.bouton_commu.y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
        eceCity->modeJeu = COMMU;
        eceCity->currentJeu = JEUMENU;
    }
    if((eceCity->image.bouton_capi.x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.bouton_capi.x2 )&& ( eceCity->image.bouton_capi.y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.bouton_capi.y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
        eceCity->modeJeu = CAPI;
        eceCity->currentJeu = JEUMENU;
    }
    if((eceCity->image.tabBoutonMenu[BOUTON_QUITTER].x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabBoutonMenu[BOUTON_QUITTER].x2 )&& ( eceCity->image.tabBoutonMenu[BOUTON_QUITTER].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabBoutonMenu[BOUTON_QUITTER].y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
        eceCity->currentJeu = QUITTER;
    }

}
void menu(ECE_City *eceCity){

    eceCity->souris.pos = getPosMouse(eceCity);
    affichage_menu(*eceCity);

    for (int i = BOUTON_1; i <= BOUTON_QUITTER; ++i) {
        if ((eceCity->image.tabBoutonMenu[i].x1 <= eceCity->souris.pos.x )&&(eceCity->souris.pos.x <= eceCity->image.tabBoutonMenu[i].x2 )&& ( eceCity->image.tabBoutonMenu[i].y1  <= eceCity->souris.pos.y)&&( eceCity->souris.pos.y <= eceCity->image.tabBoutonMenu[i].y2  )&&(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
            eceCity->currentJeu = i==BOUTON_1?MODEJEU:i==BOUTON_2?CHARGER:i==BOUTON_3?REGLE:QUITTER;
        }
    }

}
void fonction_principale(ECE_City * eceCity){

    while (!eceCity->end){

        switch (eceCity->currentJeu) {
            case MENU:
                menu(eceCity);
                break;
            case MODEJEU:
                modeJeu(eceCity);
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
    sauvegarde(eceCity);
    unloadImages(eceCity);
}
