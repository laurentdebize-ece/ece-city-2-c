#include "initialisation.h"


void initECECity (ECE_City * eceCity) {

    eceCity->coefTab = (float) TAILLE_CASE_Y / (float) TAILLE_CASE_X;
    initBatiment(eceCity, "../tailleBatiment");
    initCase(eceCity);
    eceCity->EtatPlacement = VIDE;
    eceCity->EtatPlacement = false;

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