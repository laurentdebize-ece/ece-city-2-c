#include "EauEles.h"
#include "affichage.h"



void etapePasAPas (ECE_City * eceCity, int id, Liste ** filAttente, int * reserveElec, int idCentral) {
    if (*reserveElec > 0) {
        Sommet * parcoursGraphe = eceCity->graphe;
        Sommet * parcoursGraphe2;
        while (parcoursGraphe->id != id) {
            parcoursGraphe = parcoursGraphe->next;
        }
        if (parcoursGraphe->batiment >= TERRAIN_VAGUE && parcoursGraphe->batiment <= GRATTE_CIEL) {
            if (parcoursGraphe->consoElec < eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax || !eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax) {
                if (*reserveElec >= eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax) {
                    *reserveElec -= eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax;
                    parcoursGraphe->consoElec = eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax;
                }
                parcoursGraphe->idCEntral[parcoursGraphe->nbCentral] = idCentral;
                parcoursGraphe->nbCentral++;
            }
        }
        else {
            Liste * parcoursTabAdjacent = parcoursGraphe->tabAdjacent;
            while (parcoursTabAdjacent != NULL) {
                Liste * parcoursListe = *filAttente;
                int dansLaFil = 0;
                while (parcoursListe != NULL) {
                    if (parcoursListe->id == parcoursTabAdjacent->id) {
                        dansLaFil = 1;
                    }
                    parcoursListe = parcoursListe->next;
                }
                if (!dansLaFil) {
                    parcoursGraphe2 = eceCity->graphe;
                    while (parcoursGraphe2->id != parcoursTabAdjacent->id) {
                        parcoursGraphe2 = parcoursGraphe2->next;
                    }
                    if (parcoursGraphe2->decouvertePasApasElec == false) {
                        ajoutListe(filAttente, parcoursTabAdjacent->id);
                    }
                }
                parcoursTabAdjacent = parcoursTabAdjacent->next;
            }
        }
        parcoursGraphe->decouvertePasApasElec = true;
    }
}

void ParcoursElec (ECE_City * eceCity, int idCentral){
    int reserveElec = 5000;
    Liste * filAttenteBatimentELec = NULL;
    Sommet * parcoursGraphe = eceCity->graphe;

    while (parcoursGraphe != NULL) {
        parcoursGraphe->decouvertePasApasElec = false;
        parcoursGraphe = parcoursGraphe->next;
    }

    etapePasAPas(eceCity, idCentral, &filAttenteBatimentELec, &reserveElec, idCentral);

    while (filAttenteBatimentELec != NULL) {
        etapePasAPas(eceCity, filAttenteBatimentELec->id, &filAttenteBatimentELec, &reserveElec, idCentral);
        nextFilAttente(&filAttenteBatimentELec);
    }
    parcoursGraphe = eceCity->graphe;
    while (parcoursGraphe != NULL) {
        if (parcoursGraphe->id == idCentral) {
            parcoursGraphe->consoElec = reserveElec;
        }
        for (int i = 0; i < parcoursGraphe->nbCentral; ++i) {
            if (parcoursGraphe->idCEntral[i] == idCentral) {
                parcoursGraphe->reserveCentral += reserveElec;
            }
        }

        parcoursGraphe = parcoursGraphe->next;
    }
}


void repartitionElec (ECE_City * eceCity) {
    Sommet * parcoursGraphe = eceCity->graphe;
    eceCity->nbCentral = 0;
    eceCity->nbHabitant = 0;
    Liste * filAttenteCentral = NULL;
    if (IsKeyDown(KEY_Y)){
        printf ("ok");
    }
    while (parcoursGraphe != NULL) {
        if (parcoursGraphe->batiment >= CABANE && parcoursGraphe->batiment <= GRATTE_CIEL) {
            eceCity->nbHabitant += eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax;
            parcoursGraphe->consoElec = 0;
            parcoursGraphe->decouvertePasApasElec = 0;
            parcoursGraphe->reserveCentral = 0;
            for (int i = 0; i < parcoursGraphe->nbCentral; ++i) {
                parcoursGraphe->idCEntral[i] = 0;
            }
        }
        parcoursGraphe->nbCentral = 0;
        if (parcoursGraphe->batiment == CENTRALE_ELECTRIQUE) {
            ajoutListe(&filAttenteCentral, parcoursGraphe->id);
            eceCity->nbCentral++;
        }
        parcoursGraphe = parcoursGraphe->next;
    }
    while (filAttenteCentral != NULL) {
        ParcoursElec(eceCity, filAttenteCentral->id);
        nextFilAttente(&filAttenteCentral);
    }

}

void affichageElec (ECE_City * eceCity, Color color) {
    Sommet * parcoursGraphe = eceCity->graphe;
    while (parcoursGraphe != NULL) {
        parcoursGraphe->dejaEcrit = false;
        parcoursGraphe = parcoursGraphe->next;
    }
    for (int i = 0; i < NB_LIGNE; ++i) {
        for (int j = 0; j < NB_COLONNE; ++j) {
            if (eceCity->tabCase[i][j].Etat == ROUTE) {
                affichageCase(eceCity, i, j, color);
            }
            if (eceCity->tabCase[i][j].Etat >= CABANE && eceCity->tabCase[i][j].Etat <= GRATTE_CIEL) {
                affichageCase(eceCity, i, j, GRAY);
            }
            if (eceCity->tabCase[i][j].Etat == CENTRALE_ELECTRIQUE) {
                affichageCase(eceCity, i, j, GREEN);
            }
        }
    }
    for (int i = 0; i < NB_LIGNE; ++i) {
        for (int j = 0; j < NB_COLONNE; ++j) {
            if (eceCity->tabCase[i][j].Etat >= CABANE && eceCity->tabCase[i][j].Etat <= GRATTE_CIEL) {
                parcoursGraphe = eceCity->graphe;
                while (parcoursGraphe->ligne > i || parcoursGraphe->ligne+eceCity->batiment[parcoursGraphe->batiment-1].longueur <= i
                       || parcoursGraphe->colonne > j || parcoursGraphe->colonne+eceCity->batiment[parcoursGraphe->batiment-1].largeur <= j) {
                    parcoursGraphe = parcoursGraphe->next;
                }
                if (parcoursGraphe->dejaEcrit == false) {
                    DrawText(TextFormat("%d", parcoursGraphe->consoElec), eceCity->tabCase[i][j].pos.x+40, eceCity->tabCase[i][j].pos.y-20, 20, BLACK);
                    DrawText(TextFormat("/%d", eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax), eceCity->tabCase[i][j].pos.x+30, eceCity->tabCase[i][j].pos.y, 20, BLACK);
                    parcoursGraphe->dejaEcrit = true;
                }
            }
            else if (eceCity->tabCase[i][j].Etat == CENTRALE_ELECTRIQUE) {
                parcoursGraphe = eceCity->graphe;
                while (parcoursGraphe->ligne > i || parcoursGraphe->ligne+eceCity->batiment[parcoursGraphe->batiment-1].longueur <= i
                       || parcoursGraphe->colonne > j || parcoursGraphe->colonne+eceCity->batiment[parcoursGraphe->batiment-1].largeur <= j) {
                    parcoursGraphe = parcoursGraphe->next;
                }
                if (parcoursGraphe->dejaEcrit == false) {
                    DrawText(TextFormat("Stokage :"), eceCity->tabCase[i][j].pos.x +40, eceCity->tabCase[i][j].pos.y-10, 20, BLACK);
                    DrawText(TextFormat("%d/5000", parcoursGraphe->consoElec), eceCity->tabCase[i][j].pos.x +60, eceCity->tabCase[i][j].pos.y+10, 20, BLACK);
                    parcoursGraphe->dejaEcrit = true;
                }
            }
        }
    }
}