#include "initialisation.h"


void initECECity (ECE_City * eceCity) {

    eceCity->coefTab = (float) TAILLE_CASE_Y / (float) TAILLE_CASE_X;
    initBatiment(eceCity, "../tailleBatiment");
    initCase0(eceCity);
    initEtatCase(eceCity);
    initSouris(eceCity);
    eceCity->EtatPlacement = VIDE;
    eceCity->EtatPlacement = false;
    eceCity->orientation = 0;
    eceCity->eceFlouz = 500000;
    eceCity->etage = JEU;
    eceCity->upgrade.Upgrade = -1;
    eceCity->upgrade.upgradeEnCours = 0;
    eceCity->currentJeu = JEUMENU;
    eceCity->t.speedTime = 1;
    eceCity->end = false;
    eceCity->nuit = 0;
    eceCity->modeJeu = COMMU;
    eceCity->image.varTabImageBat = 0;
    eceCity->image.boite_outils.temp = false;
    eceCity->image.boite_outils.perm = false;

    for (int i = 0; i < NB_BOUTON_BOS; ++i) {
        eceCity->image.tabBoutonBOS[i].temp = false;
        eceCity->image.tabBoutonBOS[i].perm = false;
        eceCity->image.tabBoutonBOS[i].clique= 0;
    }
    eceCity->incendie.varSeconde = 1;
    eceCity->incendie.num =15;
    eceCity->incendie.var =0;
    eceCity->incendie.feu =0;
    eceCity->incendie.max =0;
    eceCity->incendie.proba=3;
    initGraphe(eceCity);
    loadImages(eceCity);
    initBouton(eceCity);

    eceCity->image.tabBoutonBOS[BOS_ROUTE-5].equivalenceClavier=KEY_R;
    eceCity->image.tabBoutonBOS[BOS_MAISON-5].equivalenceClavier=KEY_T;
    eceCity->image.tabBoutonBOS[BOS_ELEC-5].equivalenceClavier=KEY_E;
    eceCity->image.tabBoutonBOS[BOS_EAU-5].equivalenceClavier=KEY_H;
    eceCity->image.tabBoutonBOS[BOS_POMPIER-5].equivalenceClavier=KEY_P;
}


void initSouris (ECE_City * eceCity) {
    eceCity->souris.pos.x = 0;
    eceCity->souris.pos.y = 0;
    eceCity->souris.posLigne = 0;
    eceCity->souris.posColonne = 0;
    eceCity->souris.repLigne = 0;
    eceCity->souris.repColonne = 0;
}

void initGraphe (ECE_City * eceCity) {
    eceCity->graphe = NULL;
    eceCity->nbSommetGraphe = 0;
    eceCity->upgrade.idEnCours = 0;
}

void initBatiment (ECE_City * eceCity, char* fichier){
    FILE * ifs = fopen(fichier,"r");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    for (int i = 0; i < NB_BAT; ++i) {
        fscanf(ifs,"%d", &eceCity->batiment[i].longueur);
        fscanf(ifs,"%d", &eceCity->batiment[i].largeur);
        fscanf(ifs,"%d", &eceCity->batiment[i].nbHabitantMax);
        fscanf(ifs,"%d", &eceCity->batiment[i].prix);
        eceCity->batiment[i].feu =0;
        eceCity->batiment[i].nomBatiment = calloc(30, sizeof (char));
        int j = 0;
        char  caractere;
        fscanf (ifs, "%c", &caractere);
        fscanf (ifs, "%c", &caractere);
        while (caractere != '!') {
            eceCity->batiment[i].nomBatiment[j]=caractere;
            fscanf (ifs, "%c", &caractere);
            j++;
        }
    }
}

void initEtatCase (ECE_City * eceCity) {
    for (int i = 0; i < NB_LIGNE; ++i) {
        for (int j = 0; j < NB_COLONNE; ++j) {
            eceCity->tabCase[i][j].Etat = VIDE;
            eceCity->tabCase[i][j].selec = false;
        }
    }
}

void initCase0 (ECE_City * ece_city){

    int x, y;

    for (int i = 0; i < NB_LIGNE; ++i) {
        x = X_TAB + i*TAILLE_CASE_X;
        y = Y_TAB - i*TAILLE_CASE_Y;
        for (int j = 0; j < NB_COLONNE; ++j) {
            ece_city->tabCase[i][j].pos.x = (float)x;
            ece_city->tabCase[i][j].pos.y = (float)y;
            if (i == 0) {
                ece_city->tabCase[0][j].repColonne = ece_city->tabCase[0][j].pos.y + ece_city->coefTab * ece_city->tabCase[0][j].pos.x;
            }
            if (j == 0) {
                ece_city->tabCase[i][0].repLigne = ece_city->tabCase[i][0].pos.y - ece_city->coefTab * ece_city->tabCase[i][0].pos.x;
            }
            x += TAILLE_CASE_X;
            y += TAILLE_CASE_Y;
        }
    }
}

void initCase1 (ECE_City * ece_city){

    int x, y;

    for (int i = 0; i < NB_LIGNE; ++i) {
        y = NB_COLONNE*TAILLE_CASE_Y + Y_TAB - i*TAILLE_CASE_Y;
        x = NB_LIGNE*TAILLE_CASE_X + X_TAB - i*TAILLE_CASE_X;
        for (int j = 0; j < NB_COLONNE; ++j) {

            ece_city->tabCase[i][j].pos.x = (float)x;
            ece_city->tabCase[i][j].pos.y = (float)y;
            if (i == 0) {
                ece_city->tabCase[0][j].repColonne = ece_city->tabCase[0][j].pos.y - ece_city->coefTab * ece_city->tabCase[0][j].pos.x;
            }
            if (j == 0) {
                ece_city->tabCase[i][0].repLigne = ece_city->tabCase[i][0].pos.y + ece_city->coefTab * ece_city->tabCase[i][0].pos.x;
            }
            x += TAILLE_CASE_X;
            y -= TAILLE_CASE_Y;
        }
    }
}

void falseCaseSelec (ECE_City * eceCity) {
    for (int i = 0; i < NB_LIGNE; ++i) {
        for (int j = 0; j < NB_COLONNE; ++j) {
            eceCity->tabCase[i][j].selec = false;
        }
    }
}

void initBouton(ECE_City * eceCity){
    eceCity->image.tabBoutonMenu[BOUTON_1].x1 = 687;
    eceCity->image.tabBoutonMenu[BOUTON_1].y1 = 650;
    eceCity->image.tabBoutonMenu[BOUTON_1].x2 = 1191;
    eceCity->image.tabBoutonMenu[BOUTON_1].y2 = 738;
    eceCity->image.tabBoutonMenu[BOUTON_2].x1 = 687;
    eceCity->image.tabBoutonMenu[BOUTON_2].y1 = 780;
    eceCity->image.tabBoutonMenu[BOUTON_2].x2 = 1191;
    eceCity->image.tabBoutonMenu[BOUTON_2].y2 = 868;
    eceCity->image.tabBoutonMenu[BOUTON_3].x1 = 687;
    eceCity->image.tabBoutonMenu[BOUTON_3].y1 = 920;
    eceCity->image.tabBoutonMenu[BOUTON_3].x2 = 1191;
    eceCity->image.tabBoutonMenu[BOUTON_3].y2 = 1008;
    eceCity->image.tabBoutonMenu[BOUTON_QUITTER].x1 = 1705;
    eceCity->image.tabBoutonMenu[BOUTON_QUITTER].y1 = 1004;
    eceCity->image.tabBoutonMenu[BOUTON_QUITTER].x2 = 1880;
    eceCity->image.tabBoutonMenu[BOUTON_QUITTER].y2 = 1044;
    eceCity->image.bouton_capi.x1 = 1045;
    eceCity->image.bouton_capi.y1 = 250;
    eceCity->image.bouton_capi.x2 = 1715;
    eceCity->image.bouton_capi.y2 = 932;
    eceCity->image.bouton_commu.x1 = 185;
    eceCity->image.bouton_commu.y1 = 250;
    eceCity->image.bouton_commu.x2 = 855;
    eceCity->image.bouton_commu.y2 = 932;
    eceCity->image.boite_outils.x1 = 50;
    eceCity->image.boite_outils.y1 = 700;
    eceCity->image.boite_outils.x2 = 260;
    eceCity->image.boite_outils.y2 = 1010;
    eceCity->image.tabBoutonBOS[BOS_DESTRUCTION-5].x1 = 282;
    eceCity->image.tabBoutonBOS[BOS_DESTRUCTION-5].y1 = 725;
    eceCity->image.tabBoutonBOS[BOS_DESTRUCTION-5].x2 = 372;
    eceCity->image.tabBoutonBOS[BOS_DESTRUCTION-5].y2 = 815;
    eceCity->image.tabBoutonBOS[BOS_ROUTE-5].x1 = 62;
    eceCity->image.tabBoutonBOS[BOS_ROUTE-5].y1 = 635;
    eceCity->image.tabBoutonBOS[BOS_ROUTE-5].x2 = 152;
    eceCity->image.tabBoutonBOS[BOS_ROUTE-5].y2 = 725;
    eceCity->image.tabBoutonBOS[BOS_BAT-5].x1 = 192;
    eceCity->image.tabBoutonBOS[BOS_BAT-5].y1 = 636;
    eceCity->image.tabBoutonBOS[BOS_BAT-5].x2 = 277;
    eceCity->image.tabBoutonBOS[BOS_BAT-5].y2 = 721;
    eceCity->image.tabBoutonBOS[BOS_ELEC-5].x1 = 298;
    eceCity->image.tabBoutonBOS[BOS_ELEC-5].y1 = 648;
    eceCity->image.tabBoutonBOS[BOS_ELEC-5].x2 = 353;
    eceCity->image.tabBoutonBOS[BOS_ELEC-5].y2 = 703;
    eceCity->image.tabBoutonBOS[BOS_POMPIER-5].x1 = 278 ;
    eceCity->image.tabBoutonBOS[BOS_POMPIER-5].y1 = 579;
    eceCity->image.tabBoutonBOS[BOS_POMPIER-5].x2 = 333;
    eceCity->image.tabBoutonBOS[BOS_POMPIER-5].y2 = 634;
    eceCity->image.tabBoutonBOS[BOS_EAU-5].x1 = 208;
    eceCity->image.tabBoutonBOS[BOS_EAU-5].y1 = 552;
    eceCity->image.tabBoutonBOS[BOS_EAU-5].x2 = 263;
    eceCity->image.tabBoutonBOS[BOS_EAU-5].y2 = 607;
    eceCity->image.tabBoutonBOS[BOS_MAISON-5].x1 = 144;
    eceCity->image.tabBoutonBOS[BOS_MAISON-5].y1 = 576;
    eceCity->image.tabBoutonBOS[BOS_MAISON-5].x2 = 199;
    eceCity->image.tabBoutonBOS[BOS_MAISON-5].y2 = 631;
}




void loadImages(ECE_City * eceCity){
    eceCity->image.image_menu = LoadTexture("../Images/ACCEUIL.png");
    eceCity->image.image_bonhomme = LoadTexture("../Images/BONHOMME.png");
    eceCity->image.tabImageJeu[FOND_COMMU]= LoadTexture("../Images/FOND.png");
    eceCity->image.tabImageJeu[FOND_COMMU_NUIT] = LoadTexture("../Images/FOND_NUIT.png");
    eceCity->image.tabImageJeu[FOND_CAPI] = LoadTexture("../Images/FONDCAPITALISTE.png");
    eceCity->image.tabImageJeu[FOND_CAPI_NUIT] = LoadTexture("../Images/FONDNUITCAPITALISTE.png");
    eceCity->image.tabImageJeu[BOITE_OUTILS] = LoadTexture("../Images/bouton boite outils/BOITEOUTILS.png");
    eceCity->image.tabImageJeu[BOS_BAT] = LoadTexture("../Images/bouton boite outils/BOS_BAT.png");
    eceCity->image.tabImageJeu[BOS_ELEC] = LoadTexture("../Images/bouton boite outils/BOS_ELEC.png");
    eceCity->image.tabImageJeu[BOS_EAU] = LoadTexture("../Images/bouton boite outils/BOS_EAU.png");
    eceCity->image.tabImageJeu[BOS_DESTRUCTION] = LoadTexture("../Images/bouton boite outils/BOS_DESTRUCTION.png");
    eceCity->image.tabImageJeu[BOS_MAISON] = LoadTexture("../Images/bouton boite outils/BOS_MAISON.png");
    eceCity->image.tabImageJeu[BOS_POMPIER] = LoadTexture("../Images/bouton boite outils/BOS_POMPIER.png");
    eceCity->image.tabImageJeu[BOS_ROUTE] = LoadTexture("../Images/bouton boite outils/BOS_ROUTE.png");
    eceCity->image.image_choix = LoadTexture("../Images/CHOIX.png");
    eceCity->image.image_flamme = LoadTexture("../Images/FLAMME.png");
    eceCity->image.image_affichage = LoadTexture("../Images/AFFICHAGE.png");
    eceCity->image.tabBoutonMenu[BOUTON_1] = LoadTexture("../Images/Boutons/12.png");
    eceCity->image.tabBoutonMenu[BOUTON_2] = LoadTexture("../Images/Boutons/8.png");
    eceCity->image.tabBoutonMenu[BOUTON_3] = LoadTexture("../Images/Boutons/6.png");
    eceCity->image.tabBoutonMenu[BOUTON_1_GRIS] = LoadTexture("../Images/Boutons/13.png");
    eceCity->image.tabBoutonMenu[BOUTON_2_GRIS] = LoadTexture("../Images/Boutons/9.png");
    eceCity->image.tabBoutonMenu[BOUTON_3_GRIS] = LoadTexture("../Images/Boutons/7.png");
    eceCity->image.tabBoutonMenu[BOUTON_QUITTER] = LoadTexture("../Images/Boutons/10.png");
    eceCity->image.tabBoutonMenu[BOUTON_QUITTER_GRIS] = LoadTexture("../Images/Boutons/11.png");
    eceCity->image.tabImageRoute[ROUTEBASHAUT] = LoadTexture("../Images/Routes/ROUTEDROITEBASHAUT.png");
    eceCity->image.tabImageRoute[ROUTEHAUTBAS] = LoadTexture("../Images/Routes/ROUTEDROITEHAUTBAS3.png");
    eceCity->image.tabImageRoute[ROUTEVIRAGEHAUT] = LoadTexture("../Images/Routes/ROUTEVIRAGEHAUT.png");
    eceCity->image.tabImageRoute[ROUTEVIRAGEDROITE] = LoadTexture("../Images/Routes/ROUTEVIRAGEDROITE.png");
    eceCity->image.tabImageRoute[ROUTEVIRAGEGAUCHE] = LoadTexture("../Images/Routes/ROUTEVIRAGEGAUCHE.png");
    eceCity->image.tabImageRoute[ROUTEVIRAGEBAS] = LoadTexture("../Images/Routes/ROUTEVIRAGEBAS.png");
    eceCity->image.tabImageRoute[ROUTETRIPLE] = LoadTexture("../Images/Routes/ROUTETRIPLEHAUTGAUCHE.png");
    eceCity->image.tabImageRoute[ROUTETRIPLEBASDROITE] = LoadTexture("../Images/Routes/ROUTETRIPLEBASDROITE.png");
    eceCity->image.tabImageRoute[ROUTETRIPLEBASGAUCHE] = LoadTexture("../Images/Routes/ROUTETRIPLEBASGAUCHE.png");
    eceCity->image.tabImageRoute[ROUTETRIPLEHAUTDROITE] = LoadTexture("../Images/Routes/ROUTETRIPLEHAUTDROITE.png");
    eceCity->image.tabImageRoute[ROUTECROISEMENT] = LoadTexture("../Images/Routes/ROUTECROISEMENT.png");
    eceCity->image.tabImageBat[TERRAIN_VAGUE-2] = LoadTexture("../Images/Batiments/JOUR/TERRAINVAGUE.png");
    eceCity->image.tabImageBat[CABANE-2] = LoadTexture("../Images/Batiments/JOUR/CABANEOK.png");
    eceCity->image.tabImageBat[MAISON-2] = LoadTexture("../Images/Batiments/JOUR/MAISONOK.png");
    eceCity->image.tabImageBat[IMMEUBLE-2] = LoadTexture("../Images/Batiments/JOUR/IMMEUBLEOK.png");
    eceCity->image.tabImageBat[GRATTE_CIEL-2] = LoadTexture("../Images/Batiments/JOUR/GRATTECIELOK.png");
    eceCity->image.tabImageBat[CHATEAU_EAU-2] = LoadTexture("../Images/Batiments/CHATEAU_EAU_SENS1.png");
    eceCity->image.tabImageBat[CHATEAU_EAU_SENS] = LoadTexture("../Images/Batiments/CHATEAU_EAU_SENS2.png");
    eceCity->image.tabImageBat[TERRAIN_VAGUE_NUIT-2] = LoadTexture("../Images/Batiments/NUIT/TERRAINVAGUENUIT.png");
    eceCity->image.tabImageBat[CABANE_NUIT-2] = LoadTexture("../Images/Batiments/NUIT/CABANENUIT.png");
    eceCity->image.tabImageBat[MAISON_NUIT-2] = LoadTexture("../Images/Batiments/NUIT/MAISONNUIT.png");
    eceCity->image.tabImageBat[IMMEUBLE_NUIT-2] = LoadTexture("../Images/Batiments/NUIT/IMMEUBLENUIT.png");
    eceCity->image.tabImageBat[GRATTE_CIEL_NUIT-2] = LoadTexture("../Images/Batiments/NUIT/GRATTECIELNUIT.png");
    eceCity->image.tabImageBat[CENTRALE_ELECTRIQUE-2] = LoadTexture("../Images/Batiments/CENTRALE.png");
    eceCity->image.tabImageBat[TERRAIN_VAGUE_FEU-2] = LoadTexture("../Images/Batiments/FEU/TERRAIN_VAGUE_FEU.png");
    eceCity->image.tabImageBat[CABANE_FEU-2] = LoadTexture("../Images/Batiments/FEU/CABANE_FEU.png");
    eceCity->image.tabImageBat[MAISON_FEU-2] = LoadTexture("../Images/Batiments/FEU/MAISON_FEU.png");
    eceCity->image.tabImageBat[IMMEUBLE_FEU-2] = LoadTexture("../Images/Batiments/FEU/IMMEUBLE_FEU.png");
    eceCity->image.tabImageBat[GRATTE_CIEL_FEU-2] = LoadTexture("../Images/Batiments/FEU/GRATTE_CIEL_FEU.png");
}


void unloadImages(ECE_City * eceCity){
    UnloadTexture(eceCity->image.image_menu);
    UnloadTexture(eceCity->image.image_bonhomme);
    UnloadTexture(eceCity->image.image_choix);
    UnloadTexture(eceCity->image.image_flamme);
    UnloadTexture(eceCity->image.image_affichage);
    for (int i = BOUTON_1; i <= BOUTON_QUITTER_GRIS; ++i) {
        UnloadTexture(eceCity->image.tabBoutonMenu[i]);
    }
    for (int i = 0; i < NB_IMAGE_ROUTE; ++i) {
        UnloadTexture(eceCity->image.tabImageRoute[i]);
    }
    for (int i = 0; i < NB_IMAGE_BAT; ++i) {
        UnloadTexture(eceCity->image.tabImageBat[i]);
    }
    for (int i = 0; i < NB_IMAGE_JEU; ++i) {
        UnloadTexture(eceCity->image.tabImageJeu[i]);
    }
}