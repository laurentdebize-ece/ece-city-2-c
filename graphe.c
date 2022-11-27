#include "graphe.h"
#include "EauEles.h"


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

            ajoutListe(&ajoutGraphe->tabAdjacent, parcourGraphe->id);
            ajoutGraphe->nbAdjacent++;

            ajoutListe(&parcourGraphe->tabAdjacent, ajoutGraphe->id);
            parcourGraphe->nbAdjacent++;
        }
    }
}

void ajoutRouteGraphe (ECE_City * eceCity) {
    eceCity->nbSommetGraphe++;
    if (eceCity->graphe == NULL){
        eceCity->graphe = malloc(sizeof(Sommet));
        eceCity->graphe->id = eceCity->upgrade.idEnCours;
        eceCity->upgrade.idEnCours++;
        eceCity->graphe->batiment = eceCity->EtatPlacement;
        eceCity->graphe->colonne = eceCity->souris.posColonne;
        eceCity->graphe->ligne = eceCity->souris.posLigne;
        eceCity->graphe->next = NULL;
        eceCity->graphe->poser = NULL;
        eceCity->graphe->detruire = false;
        eceCity->graphe->nbUpgrade =  eceCity->upgrade.upgradeEnCours;
        eceCity->graphe->tabAdjacent = NULL;
        eceCity->graphe->nbAdjacent = 0;
    }
    else {
        Sommet * ajoutGraphe = eceCity->graphe;
        while (ajoutGraphe->next != NULL) {
            ajoutGraphe = ajoutGraphe->next;
        }

        ajoutGraphe->next = malloc(sizeof (Sommet));
        ajoutGraphe->next->id = eceCity->upgrade.idEnCours;
        eceCity->upgrade.idEnCours++;
        ajoutGraphe->next->batiment = eceCity->EtatPlacement;
        ajoutGraphe->next->ligne = eceCity->souris.posLigne;
        ajoutGraphe->next->colonne = eceCity->souris.posColonne;
        ajoutGraphe->next->next = NULL;
        ajoutGraphe->next->nbUpgrade = eceCity->upgrade.upgradeEnCours;
        ajoutGraphe->next->tabAdjacent = NULL;
        ajoutGraphe->next->poser = NULL;
        ajoutGraphe->next->detruire = false;
        ajoutGraphe->next->nbAdjacent = 0;
        ajoutGraphe->next->consoEau = 0;
        ajoutGraphe->next->consoElec = 0;
        ajoutGraphe->next->reserveChateauEau = 0;
        ajoutGraphe->next->reserveCentral = 0;
        ajoutGraphe->next->dejaEcrit = false;
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

