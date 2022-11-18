#include "initialisation.h"


void initECECity (ECE_City * eceCity) {

    eceCity->coefTab = (float) TAILLE_CASE_Y / (float) TAILLE_CASE_X;
    initBatiment(eceCity, "../tailleBatiment");
    initCase(eceCity);
    initSouris(eceCity);
    eceCity->EtatPlacement = VIDE;
    eceCity->EtatPlacement = false;
    eceCity->orientation = 0;
    eceCity->etage = JEU;
    eceCity->upgrade.Upgrade = -1;
    eceCity->upgrade.upgradeEnCours = 0;
    eceCity->currentJeu = MENU;
    eceCity->t.speedTime = 1;
    eceCity->end = false;
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
    eceCity->idEnCours = 0;
}

void initBatiment (ECE_City * eceCity, char* fichier){
    FILE * ifs = fopen(fichier,"r");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    for (int i = 0; i < NB_BAT; ++i) {
        eceCity->batiment[i].nbHabitant = 0;
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

void initCase (ECE_City * eceCity){

    int x, y;


    for (int i = 0; i < NB_LIGNE; ++i) {
        x = X_TAB + i*TAILLE_CASE_X;
        y = Y_TAB - i*TAILLE_CASE_Y;
        for (int j = 0; j < NB_COLONNE; ++j) {
            eceCity->tabCase[i][j].Etat = VIDE;
            eceCity->tabCase[i][j].selec = false;

            eceCity->tabCase[i][j].pos.x = (float)x;
            eceCity->tabCase[i][j].pos.y = (float)y;
            if (i == 0) {
                eceCity->tabCase[0][j].repColonne = eceCity->tabCase[0][j].pos.y + eceCity->coefTab*eceCity->tabCase[0][j].pos.x;
            }
            if (j == 0) {
                eceCity->tabCase[i][0].repLigne = eceCity->tabCase[i][0].pos.y - eceCity->coefTab*eceCity->tabCase[i][0].pos.x;
            }
            x += TAILLE_CASE_X;
            y += TAILLE_CASE_Y;
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
    eceCity->image.image_barre1.x1 = 687;
    eceCity->image.image_barre1.y1 = 650;
    eceCity->image.image_barre1.x2 = 1191;
    eceCity->image.image_barre1.y2 = 738;
    eceCity->image.image_barre2.x1 = 687;
    eceCity->image.image_barre2.y1 = 780;
    eceCity->image.image_barre2.x2 = 1191;
    eceCity->image.image_barre2.y2 = 868;
    eceCity->image.image_barre3.x1 = 687;
    eceCity->image.image_barre3.y1 = 920;
    eceCity->image.image_barre3.x2 = 1191;
    eceCity->image.image_barre3.y2 = 1008;
    eceCity->image.image_quitter.x1 = 1705;
    eceCity->image.image_quitter.y1 = 1004;
    eceCity->image.image_quitter.x2 = 1880;
    eceCity->image.image_quitter.y2 = 1044;
}

void loadImages(ECE_City * eceCity){
    eceCity->image.image_menu = LoadTexture("../Images/ACCEUIL.png");
    eceCity->image.image_barre1 = LoadTexture("../Images/Boutons/12.png");
    eceCity->image.image_barre2 = LoadTexture("../Images/Boutons/8.png");
    eceCity->image.image_barre3 = LoadTexture("../Images/Boutons/6.png");
    eceCity->image.image_barregrise1 = LoadTexture("../Images/Boutons/13.png");
    eceCity->image.image_barregrise2 = LoadTexture("../Images/Boutons/9.png");
    eceCity->image.image_barregrise3 = LoadTexture("../Images/Boutons/7.png");
    eceCity->image.image_quitter = LoadTexture("../Images/Boutons/10.png");
    eceCity->image.image_quittergris = LoadTexture("../Images/Boutons/11.png");
    eceCity->image.image_test = LoadTexture("../Images/TESTFOND.png");
    eceCity->image.image_route = LoadTexture("../Images/Routes/ROUTEDROITE1.png");
    eceCity->image.tabImageBat[CABANE-2] = LoadTexture("../Images/Batiments/CABANEOK.png");
    eceCity->image.tabImageBat[MAISON-2] = LoadTexture("../Images/Batiments/MAISONOK.png");
    eceCity->image.tabImageBat[IMMEUBLE-2] = LoadTexture("../Images/Batiments/IMMEUBLEOK.png");
    eceCity->image.tabImageBat[GRATTE_CIEL-2] = LoadTexture("../Images/Batiments/GRATTECIELOK.png");
}

void unloadImages(ECE_City * eceCity){
    UnloadTexture(eceCity->image.image_menu);
    UnloadTexture(eceCity->image.image_barre1);
    UnloadTexture(eceCity->image.image_barre2);
    UnloadTexture(eceCity->image.image_barre3);
    UnloadTexture(eceCity->image.image_barregrise1);
    UnloadTexture(eceCity->image.image_barregrise2);
    UnloadTexture(eceCity->image.image_barregrise3);
    UnloadTexture(eceCity->image.image_quitter);
    UnloadTexture(eceCity->image.image_quittergris);
    UnloadTexture(eceCity->image.image_test);
    UnloadTexture(eceCity->image.image_route);
    UnloadTexture(eceCity->image.tabImageBat[CABANE-2]);
    UnloadTexture(eceCity->image.tabImageBat[MAISON-2]);
    UnloadTexture(eceCity->image.tabImageBat[IMMEUBLE-2]);
    UnloadTexture(eceCity->image.tabImageBat[GRATTE_CIEL-2]);
}