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
    eceCity->currentJeu = MENU;
    eceCity->t.speedTime = 1;
    eceCity->end = false;
    eceCity->nuit = 0;
    eceCity->image.varTabImageBat = 0;
    initGraphe(eceCity);
    loadImages(eceCity);
    initBouton(eceCity);
}

void initSouris (ECE_City * eceCity) {
    eceCity->souris.pos.x = 0;
    eceCity->souris.pos.y = 0;
    eceCity->souris.posLigne = 0;
    eceCity->souris.posColonne = 0;
    eceCity->souris.oldPosColonne = 0;
    eceCity->souris.oldPosLigne = 0;
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
}

void loadImages(ECE_City * eceCity){
    eceCity->image.image_menu = LoadTexture("../Images/ACCEUIL.png");
    eceCity->image.image_fond = LoadTexture("../Images/FOND.png");
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
    eceCity->image.image_fond_nuit = LoadTexture("../Images/TESTFONDNUIT.png");
    eceCity->image.tabImageBat[TERRAIN_VAGUE_NUIT] = LoadTexture("../Images/Batiments/NUIT/TERRAINVAGUENUIT.png");
    eceCity->image.tabImageBat[CABANE_NUIT] = LoadTexture("../Images/Batiments/NUIT/CABANENUIT.png");
    eceCity->image.tabImageBat[MAISON_NUIT] = LoadTexture("../Images/Batiments/NUIT/MAISONNUIT.png");
    eceCity->image.tabImageBat[IMMEUBLE_NUIT] = LoadTexture("../Images/Batiments/NUIT/IMMEUBLENUIT.png");
    eceCity->image.tabImageBat[GRATTE_CIEL_NUIT] = LoadTexture("../Images/Batiments/NUIT/GRATTECIELNUIT.png");


    }

void unloadImages(ECE_City * eceCity){
    UnloadTexture(eceCity->image.image_menu);
    UnloadTexture(eceCity->image.image_fond);
    UnloadTexture(eceCity->image.image_fond_nuit);
    for (int i = BOUTON_1; i <= BOUTON_QUITTER_GRIS; ++i) {
        UnloadTexture(eceCity->image.tabBoutonMenu[i]);
    }
    for (int i = 0; i < NB_IMAGE_ROUTE; ++i) {
        UnloadTexture(eceCity->image.tabImageRoute[i]);
    }
    for (int i = 0; i < NB_IMAGE_BAT; ++i) {
        UnloadTexture(eceCity->image.tabImageBat[i]);
    }
}