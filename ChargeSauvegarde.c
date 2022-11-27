#include "ChargeSauvegarde.h"
#include "EauEles.h"


void sauvegarde (ECE_City * eceCity) {
    FILE * ifs = fopen("../Sauvegarde","w");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(1);
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
    fclose(ifs);
}


void load (ECE_City * eceCity) {
    initECECity(eceCity);

    eceCity->currentJeu = JEUMENU;

    FILE * ifs = fopen("Sauvegarde","r");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(1);
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

/*
FILE* creerFichier(){
    char chemin[LG_MAX_CHEMIN_SAUVEGARDE];
    char nomPartie[LG_MAX_NOM_PARTIE];
    printf("Comment voulez-vous appeler votre partie?\n");
    scanf("%s",nomPartie);
    sprintf(chemin,"%s/%s", CHEMIN_SAUVEGARDE, nomPartie);
    FILE* monFichier = fopen(chemin,"w");
    return monFichier;
}*/

/*
void copierJoueur(Joueur j[], Partie donneePartie, FILE* creerFichier(), FILE *myFile, Classe classe){
    for(int i=0; i < donneePartie.nbJoueurs; i++){
        fprintf(myFile, "JOUEUR:%s\n",donneePartie.nom);
        fprintf(myFile,"%s%\n",
                classe.nom,
                classe.skin,
                classe.sorts);
    }
}


int fermerFichier(FILE* myFile){
    return fclose (myFile);
}

int sauvegarderPartie(){
    FILE *sauvegarde = creerFichier();
    //ouvrirFichier();
    if (NULL != sauvegarde){
        copierJoueur(sauvegarde);
    }
    else {
        printf("Erreur sur création fichier\n");
    }
    if (0 != fermerFichier(sauvegarde)) {
        printf ("Erreur lors de la fermeture du fichier de sauvegarde\n");
    }
}*/