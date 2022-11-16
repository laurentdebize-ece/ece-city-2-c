#include "graphe.h"



void detectionAdjacentRouteAjoutGraphe (ECE_City * eceCity, Sommet * ajoutGraphe, int ligne, int colonne) {
    if (eceCity->tabCase[ligne][colonne].Etat != VIDE) {
        if (eceCity->tabCase[ligne][colonne].Etat != ROUTE && ajoutGraphe->batiment == ROUTE ||
        eceCity->tabCase[ligne][colonne].Etat == ROUTE && ajoutGraphe->batiment) {
            Sommet * parcourGraphe = eceCity->graphe;

            if (eceCity->tabCase[ligne][colonne].Etat == ROUTE){

                while (parcourGraphe->ligne != ligne || parcourGraphe->colonne != colonne) {
                    parcourGraphe = parcourGraphe->next;
                }
            }
            else {
                while (ligne < parcourGraphe->ligne ||
                       ligne >= parcourGraphe->ligne + eceCity->batiment[parcourGraphe->batiment].longueur ||
                       colonne < parcourGraphe->colonne ||
                       colonne >= parcourGraphe->colonne + eceCity->batiment[parcourGraphe->batiment].largeur) {
                    parcourGraphe = parcourGraphe->next;
                }
            }

            if (ajoutGraphe->tabAdjacent == NULL) {
                ajoutGraphe->tabAdjacent = calloc(1, sizeof (int));
            }
            else {
                ajoutGraphe->tabAdjacent = realloc(ajoutGraphe->tabAdjacent, (ajoutGraphe->nbAdjacent+1)*sizeof (int));
            }
            ajoutGraphe->nbAdjacent++;
            ajoutGraphe->tabAdjacent[ajoutGraphe->nbAdjacent-1] = parcourGraphe->id;

            if (parcourGraphe->tabAdjacent == NULL) {
                parcourGraphe->tabAdjacent = calloc(1, sizeof (int));
            }
            else {
                parcourGraphe->tabAdjacent = realloc(parcourGraphe->tabAdjacent, (parcourGraphe->nbAdjacent+1)*sizeof (int));
            }
            parcourGraphe->nbAdjacent++;
            parcourGraphe->tabAdjacent[parcourGraphe->nbAdjacent-1] = ajoutGraphe->id;
        }
    }
}

void ajoutRouteGraphe (ECE_City * eceCity) {
    eceCity->nbSommetGraphe++;
    if (eceCity->graphe == NULL){
        eceCity->graphe = malloc(sizeof(Sommet));
        eceCity->graphe->id = eceCity->idEnCours;
        eceCity->idEnCours++;
        eceCity->graphe->batiment = eceCity->EtatPlacement;
        eceCity->graphe->colonne = eceCity->souris.posColonne;
        eceCity->graphe->ligne = eceCity->souris.posLigne;
        eceCity->graphe->next = NULL;
        eceCity->graphe->nbUpgrade = eceCity->upgrade.upgradeEnCours;
        eceCity->graphe->tabAdjacent = NULL;
        eceCity->graphe->nbAdjacent = 0;
    }
    else {
        Sommet * ajoutGraphe = eceCity->graphe;
        while (ajoutGraphe->next != NULL) {
            ajoutGraphe = ajoutGraphe->next;
        }

        ajoutGraphe->next = malloc(sizeof (Sommet));
        ajoutGraphe->next->id = eceCity->idEnCours;
        eceCity->idEnCours++;
        ajoutGraphe->next->batiment = eceCity->EtatPlacement;
        ajoutGraphe->next->ligne = eceCity->souris.posLigne;
        ajoutGraphe->next->colonne = eceCity->souris.posColonne;
        ajoutGraphe->next->next = NULL;
        ajoutGraphe->next->nbUpgrade = eceCity->upgrade.upgradeEnCours;
        ajoutGraphe->next->tabAdjacent = NULL;
        ajoutGraphe->next->nbAdjacent = 0;
        if (eceCity->EtatPlacement != ROUTE) {
            for (int i = eceCity->souris.posLigne; i < eceCity->souris.posLigne + eceCity->batiment[eceCity->EtatPlacement-1].longueur; ++i) {
                detectionAdjacentRouteAjoutGraphe(eceCity, ajoutGraphe->next, i, eceCity->souris.posColonne-1);
                detectionAdjacentRouteAjoutGraphe(eceCity, ajoutGraphe->next, i, eceCity->souris.posColonne + eceCity->batiment[eceCity->EtatPlacement-1].largeur);
            }
            for (int j = eceCity->souris.posColonne; j < eceCity->souris.posColonne + eceCity->batiment[eceCity->EtatPlacement-1].largeur; ++j) {
                detectionAdjacentRouteAjoutGraphe(eceCity, ajoutGraphe->next, eceCity->souris.posLigne - 1, j);
                detectionAdjacentRouteAjoutGraphe(eceCity, ajoutGraphe->next, eceCity->souris.posLigne + eceCity->batiment[eceCity->EtatPlacement-1].longueur
                                                  , j);
            }
        }
        else {
            detectionAdjacentRouteAjoutGraphe(eceCity, ajoutGraphe->next, eceCity->souris.posLigne+1, eceCity->souris.posColonne);
            detectionAdjacentRouteAjoutGraphe(eceCity, ajoutGraphe->next, eceCity->souris.posLigne-1, eceCity->souris.posColonne);
            detectionAdjacentRouteAjoutGraphe(eceCity, ajoutGraphe->next, eceCity->souris.posLigne, eceCity->souris.posColonne+1);
            detectionAdjacentRouteAjoutGraphe(eceCity, ajoutGraphe->next, eceCity->souris.posLigne, eceCity->souris.posColonne-1);
        }
    }
}

