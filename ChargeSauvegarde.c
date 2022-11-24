#include "ChargeSauvegarde.h"
#include "EauEles.h"


void sauvegarde (ECE_City * eceCity) {
    FILE * ifs = fopen("../Sauvegarde","w");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fprintf(ifs,"%d\n", eceCity->modeJeu);
    fprintf(ifs,"%d\n", eceCity->nbHabitant);
    fprintf(ifs,"%d\n", eceCity->nbChateauEau);
    fprintf(ifs,"%d\n", eceCity->eceFlouz);
    fprintf(ifs,"%d\n", eceCity->nbSommetGraphe);

    fprintf(ifs,"%d\n", eceCity->t.secondereel);
    fprintf(ifs,"%d\n", eceCity->t.minutereel);
    fprintf(ifs,"%d\n", eceCity->t.heurereel);
    fprintf(ifs,"%d\n", eceCity->t.secondefictif);
    fprintf(ifs,"%d\n", eceCity->t.mois);
    fprintf(ifs,"%d\n", eceCity->t.annee);
    fprintf(ifs,"%d\n", eceCity->t.frames);
    fprintf(ifs,"%d\n", eceCity->t.speedTime);


    fprintf(ifs,"%d\n", eceCity->upgrade.Upgrade);
    fprintf(ifs,"%d\n", eceCity->upgrade.upgradeEnCours);
    fprintf(ifs,"%d\n", eceCity->upgrade.idEnCours);

    Sommet * parcoursGraphe = eceCity->graphe;
    Liste * parcoursGraphe2;
    while (parcoursGraphe != NULL) {

        fprintf(ifs,"%d\n", parcoursGraphe->id);
        fprintf(ifs,"%d\n", parcoursGraphe->ligne);
        fprintf(ifs,"%d\n", parcoursGraphe->colonne);
        fprintf(ifs,"%d\n", parcoursGraphe->batiment);
        fprintf(ifs,"%d\n", parcoursGraphe->nbAdjacent);
        parcoursGraphe2 = parcoursGraphe->tabAdjacent;
        while (parcoursGraphe2 != NULL) {
            fprintf(ifs,"%d\n", parcoursGraphe2->id);
            parcoursGraphe2 = parcoursGraphe2->next;
        }
        fprintf(ifs,"%d\n", parcoursGraphe->nbUpgrade);
        fprintf(ifs,"%d\n", parcoursGraphe->consoEau);
        fprintf(ifs,"%d\n", parcoursGraphe->nbChateauEau);
        for (int i = 0; i < parcoursGraphe->nbChateauEau; ++i) {
            fprintf(ifs,"%d\n", parcoursGraphe->idChateauEau[i]);
        }
        fprintf(ifs,"%d\n", parcoursGraphe->reserveChateauEau);

        parcoursGraphe = parcoursGraphe->next;
    }
    for (int i = 0; i < NB_LIGNE; ++i) {
        for (int j = 0; j < NB_COLONNE; ++j) {
            fprintf(ifs, "%d\n", eceCity->tabCase[i][j].Etat);
        }
    }
}

void load (ECE_City * eceCity) {
    initECECity(eceCity);

    eceCity->currentJeu = JEUMENU;


    FILE * ifs = fopen("Sauvegarde","r");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs,"%d", &eceCity->modeJeu);
    fscanf(ifs,"%d", &eceCity->nbHabitant);
    fscanf(ifs,"%d", &eceCity->nbChateauEau);
    fscanf(ifs,"%d", &eceCity->eceFlouz);
    fscanf(ifs,"%d", &eceCity->nbSommetGraphe);

    fscanf(ifs,"%d", &eceCity->t.secondereel);
    fscanf(ifs,"%d", &eceCity->t.minutereel);
    fscanf(ifs,"%d", &eceCity->t.heurereel);
    fscanf(ifs,"%d", &eceCity->t.secondefictif);
    fscanf(ifs,"%d", &eceCity->t.mois);
    fscanf(ifs,"%d", &eceCity->t.annee);
    fscanf(ifs,"%d", &eceCity->t.frames);
    fscanf(ifs,"%d", &eceCity->t.speedTime);


    fscanf(ifs,"%d", &eceCity->upgrade.Upgrade);
    fscanf(ifs,"%d", &eceCity->upgrade.upgradeEnCours);
    fscanf(ifs,"%d", &eceCity->upgrade.idEnCours);

    Sommet * parcoursGraphe = eceCity->graphe;
    Liste * parcoursGraphe2;
    while (parcoursGraphe != NULL) {

        fscanf(ifs,"%d", &parcoursGraphe->id);
        fscanf(ifs,"%d", &parcoursGraphe->ligne);
        fscanf(ifs,"%d", &parcoursGraphe->colonne);
        fscanf(ifs,"%d", &parcoursGraphe->batiment);
        fscanf(ifs,"%d", &parcoursGraphe->nbAdjacent);
        for (int i = 0; i < parcoursGraphe->nbAdjacent; ++i) {
            int id;
            fprintf(ifs, "%d", &id);
            ajoutListe(&parcoursGraphe->tabAdjacent, id);
        }
        fscanf(ifs,"%d", &parcoursGraphe->nbUpgrade);
        fscanf(ifs,"%d", &parcoursGraphe->consoEau);
        fscanf(ifs,"%d", &parcoursGraphe->nbChateauEau);
        for (int i = 0; i < parcoursGraphe->nbChateauEau; ++i) {
            fscanf(ifs,"%d", &parcoursGraphe->idChateauEau[i]);
        }
        fscanf(ifs,"%d", &parcoursGraphe->reserveChateauEau);

        parcoursGraphe = parcoursGraphe->next;
    }

    for (int i = 0; i < NB_LIGNE; ++i) {
        for (int j = 0; j < NB_COLONNE; ++j) {
            fscanf(ifs, "%d", &eceCity->tabCase[i][j].Etat);
        }
    }
}
