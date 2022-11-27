#include "EauEles.h"
#include "affichage.h"

//**************************      EAU        *********************************************************

void ajoutListe (Liste ** filAttente, int id) {
    if (*filAttente == NULL) {
        *filAttente = malloc(sizeof (Liste));
        (*filAttente)->id = id;
        (*filAttente)->next = NULL;
    }
    else {
        Liste * parcoursListe = *filAttente;
        while (parcoursListe->next != NULL){
            parcoursListe = parcoursListe->next;
        }
        parcoursListe->next = malloc(sizeof(Liste));
        parcoursListe->next->id = id;
        parcoursListe->next->next = NULL;
    }
}

void nextFilAttente (Liste ** filAttente) {
    *filAttente = (*filAttente)->next;
}

void etapeBFS (ECE_City * eceCity, int id, Liste ** filAttente, int * reserveEau, int idChateau) {
    if (*reserveEau > 0) {
        Sommet * parcoursGraphe = eceCity->graphe;
        Sommet * parcoursGraphe2;
        while (parcoursGraphe->id != id) {
            parcoursGraphe = parcoursGraphe->next;
        }
        if (parcoursGraphe->batiment >= TERRAIN_VAGUE && parcoursGraphe->batiment <= GRATTE_CIEL) {
            if (parcoursGraphe->consoEau <= eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax) {
                if (*reserveEau > eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax - parcoursGraphe->consoEau) {
                    *reserveEau -= eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax - parcoursGraphe->consoEau;
                    parcoursGraphe->consoEau = eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax;
                }
                else {
                    parcoursGraphe->consoEau += *reserveEau;
                    *reserveEau = 0;
                }
                parcoursGraphe->idChateauEau[parcoursGraphe->nbChateauEau] = idChateau;
                parcoursGraphe->nbChateauEau++;
            }
        }
        else if (parcoursGraphe->batiment == ROUTE || parcoursGraphe->id == idChateau){
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

void BFS_Chateau (ECE_City * eceCity, int idChateau) {
    int reserveEau = 5000;
    Liste * filAttenteBatiment = NULL;
    Sommet * parcoursGraphe = eceCity->graphe;
    while (parcoursGraphe != NULL) {
        parcoursGraphe->decouverteBFS = false;
        parcoursGraphe = parcoursGraphe->next;
    }

    etapeBFS(eceCity, idChateau, &filAttenteBatiment, &reserveEau, idChateau);

    while (filAttenteBatiment != NULL) {
        etapeBFS(eceCity, filAttenteBatiment->id, &filAttenteBatiment, &reserveEau, idChateau);
        nextFilAttente(&filAttenteBatiment);
    }
    parcoursGraphe = eceCity->graphe;
    while (parcoursGraphe != NULL) {
        if (parcoursGraphe->id == idChateau) {
            parcoursGraphe->consoEau = reserveEau;
        }
        for (int i = 0; i < parcoursGraphe->nbChateauEau; ++i) {
            if (parcoursGraphe->idChateauEau[i] == idChateau) {
                parcoursGraphe->reserveChateauEau += reserveEau;
            }
        }

        parcoursGraphe = parcoursGraphe->next;
    }

}

void repartitionEau (ECE_City  * eceCity) {
    Sommet * parcoursGraphe = eceCity->graphe;
    eceCity->nbChateauEau = 0;
    eceCity->nbHabitant = 0;
    Liste * filAttenteChateau = NULL;
    while (parcoursGraphe != NULL) {
        if (parcoursGraphe->batiment >= CABANE && parcoursGraphe->batiment <= GRATTE_CIEL) {
            eceCity->nbHabitant += eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax;
            parcoursGraphe->consoEau = 0;
            parcoursGraphe->decouverteBFS = 0;
            parcoursGraphe->reserveChateauEau = 0;
            for (int i = 0; i < parcoursGraphe->nbChateauEau; ++i) {
                parcoursGraphe->idChateauEau[i] = 0;
            }
        }
        parcoursGraphe->nbChateauEau = 0;
        if (parcoursGraphe->batiment == CHATEAU_EAU) {
            ajoutListe(&filAttenteChateau, parcoursGraphe->id);
            eceCity->nbChateauEau++;
        }
        parcoursGraphe = parcoursGraphe->next;
    }
    while (filAttenteChateau != NULL) {
        BFS_Chateau(eceCity, filAttenteChateau->id);
        nextFilAttente(&filAttenteChateau);
    }

}

void affichageEau (ECE_City * eceCity, Color color) {
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
            if (eceCity->tabCase[i][j].Etat == CHATEAU_EAU) {
                affichageCase(eceCity, i, j, BLUE);
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
                    DrawText(TextFormat("%d", parcoursGraphe->consoEau), eceCity->tabCase[i][j].pos.x+40, eceCity->tabCase[i][j].pos.y-20, 20, BLACK);
                    DrawText(TextFormat("/%d", eceCity->batiment[parcoursGraphe->batiment-1].nbHabitantMax), eceCity->tabCase[i][j].pos.x+30, eceCity->tabCase[i][j].pos.y, 20, BLACK);
                    parcoursGraphe->dejaEcrit = true;
                }
            }
            else if (eceCity->tabCase[i][j].Etat == CHATEAU_EAU) {
                parcoursGraphe = eceCity->graphe;
                while (parcoursGraphe->ligne > i || parcoursGraphe->ligne+eceCity->batiment[parcoursGraphe->batiment-1].longueur <= i
                       || parcoursGraphe->colonne > j || parcoursGraphe->colonne+eceCity->batiment[parcoursGraphe->batiment-1].largeur <= j) {
                    parcoursGraphe = parcoursGraphe->next;
                }
                if (parcoursGraphe->dejaEcrit == false) {
                    DrawText(TextFormat("Stokage :", parcoursGraphe->consoEau), eceCity->tabCase[i][j].pos.x +40, eceCity->tabCase[i][j].pos.y-10, 20, BLACK);
                    DrawText(TextFormat("%d/5000", parcoursGraphe->consoEau), eceCity->tabCase[i][j].pos.x +60, eceCity->tabCase[i][j].pos.y+10, 20, BLACK);
                    parcoursGraphe->dejaEcrit = true;
                }
            }
        }
    }
}

//**************************      ELEC      *********************************************************