#include "EauEles.h"
#include "affichage.h"



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


void etapePasAPas (ECE_City * eceCity, int id, Liste ** filAttente, int * reserveElec, int idCentral) {
    if (*reserveElec > 0) {
        Sommet * parcoursGraphe = eceCity->graphe;
        Sommet * parcoursGraphe2;
        while (parcoursGraphe->id != id) {
            parcoursGraphe = parcoursGraphe->next;
        }
        if (parcoursGraphe->batiment >= TERRAIN_VAGUE && parcoursGraphe->batiment <= GRATTE_CIEL) {
            if (parcoursGraphe->consoElec <= eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax) {
                if (*reserveElec > eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax - parcoursGraphe->consoElec) {
                    *reserveElec -= eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax - parcoursGraphe->consoElec;
                    parcoursGraphe->consoElec = eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax;
                }
                else {
                    parcoursGraphe->consoElec += *reserveElec;
                    *reserveElec = 0;
                }
                parcoursGraphe->idCEntral[parcoursGraphe->nbCentral] = idCentral;
                parcoursGraphe->nbCentral++;
            } il y a quz gui 
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
                    if (parcoursGraphe2->decouverteBFS == false) {
                        ajoutListe(filAttente, parcoursTabAdjacent->id);
                    }
                }
                parcoursTabAdjacent = parcoursTabAdjacent->next;
            }
        }
        parcoursGraphe->decouverteBFS = true;
    }
}

void repartitionElec (ECE_City * eceCity) {
    Sommet * parcoursGraphe = eceCity->graphe;
    eceCity->nbCentral = 0;
    eceCity->nbHabitant = 0;
    Liste * filAttenteCentral = NULL;
    while (parcoursGraphe != NULL) {
        parcoursGraphe->nbCentral = 0;
        if (parcoursGraphe->batiment >= CABANE && parcoursGraphe->batiment <= GRATTE_CIEL) {
            eceCity->nbHabitant += eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax;
            parcoursGraphe->consoElec = 0;
            parcoursGraphe->decouvertePasApasElec = 0;
            parcoursGraphe->reserveCentral = 0;
            for (int i = 0; i < parcoursGraphe->nbCentral; ++i) {
                parcoursGraphe->idCEntral[i] = 0;
            }
        }
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
