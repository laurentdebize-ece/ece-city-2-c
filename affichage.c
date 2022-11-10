//
// Created by maell on 10/11/2022.
//

#include "affichage.h"
void affichage_temps(TIME t){
    // AFFICHAGE TEMPS REEL DE JEU
    if(t.minutereel < 10 ){
        if(t.secondereel < 10){
            DrawText(TextFormat(" Temps de jeu : 0%d : 0%d : 0%d \n", t.heurereel, t.minutereel,t.secondereel), 20 , 40 , 20 , BLACK);
        }
        else {
            DrawText(TextFormat(" Temps de jeu : 0%d : 0%d : %d \n", t.heurereel, t.minutereel,t.secondereel), 20 , 40, 20 , BLACK);
        }
    }
    else{
        if(t.secondereel < 10){
            DrawText(TextFormat(" Temps de jeu : 0%d : %d : 0%d \n", t.heurereel, t.minutereel,t.secondereel), 20 , 40, 20, BLACK);
        }
        else {
            DrawText(TextFormat(" Temps de jeu : 0%d : %d : %d \n", t.heurereel, t.minutereel,t.secondereel), 20 , 40 , 20 , BLACK);
        }
    }
//AFFICHAGE TEMPS FICTIF
    if(t.annee < 10 ){
        if(t.mois < 10){
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", t.annee,t.mois), 20 , 60 , 20 , BLACK);
        }
        else {
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", t.annee,t.mois), 20, 60 , 20, BLACK);
        }
    }
    else{
        if(t.mois < 10){
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", t.annee,t.mois), 20, 60 , 20 , BLACK);
        }
        else {
            DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", t.annee,t.mois), 20, 60, 20 , BLACK);
        }
    }

}