//
// Created by maell on 07/11/2022.
//

#include <raylib.h>
#define FPS 60

int main ()
{
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Raylib > Allegro");

    SetTargetFPS(FPS);
    int frames=0;
    int secondereel = 0;
    int minutereel = 0;
    int heurereel = 0;
    int secondefictif = 0;
    int mois = 0;
    int annee = 0;




    while (!WindowShouldClose()) {
        float f = (float)GetScreenWidth() / (float)GetScreenHeight();
        frames++;
        //TEMPMS REEL
        if(frames==60) {
            secondereel++;
            secondefictif++;
            frames = 0;
            if(secondereel==60){
                minutereel++;
                secondereel = 0;
                if(minutereel==60){
                    heurereel++;
                    minutereel = 0;
                }
            }
            if(secondefictif==15){
                mois++;
                secondefictif = 0;
                if(mois == 12){
                    annee ++;
                    mois =0;
                }
            }

        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib > Allegro5", 12 * f , 12*f , 20*f , BLACK);
// AFFICHAGE TEMPS REEL DE JEU
        if(minutereel < 10 ){
            if(secondereel < 10){
                DrawText(TextFormat(" Temps de jeu : 0%d : 0%d : 0%d \n", heurereel, minutereel,secondereel), 20 * f, 40 * f, 20 * f, BLACK);
            }
            else {
                DrawText(TextFormat(" Temps de jeu : 0%d : 0%d : %d \n", heurereel, minutereel,secondereel), 20 * f, 40 * f, 20 * f, BLACK);
            }
        }
        else{
            if(secondereel < 10){
                DrawText(TextFormat(" Temps de jeu : 0%d : %d : 0%d \n", heurereel, minutereel,secondereel), 20 * f, 40 * f, 20 * f, BLACK);
            }
            else {
                DrawText(TextFormat(" Temps de jeu : 0%d : %d : %d \n", heurereel, minutereel,secondereel), 20 * f, 40 * f, 20 * f, BLACK);
            }
        }
//AFFICHAGE TEMPS FICTIF
        if(annee < 10 ){
            if(mois < 10){
                DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", annee,mois), 20 * f, 60 * f, 20 * f, BLACK);
            }
            else {
                DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", annee,mois), 20 * f, 60 * f, 20 * f, BLACK);
            }
        }
        else{
            if(mois < 10){
                DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", annee,mois), 20 * f, 60 * f, 20 * f, BLACK);
            }
            else {
                DrawText(TextFormat(" Temps fictif : années : 0%d mois :  0%d \n", annee,mois), 20 * f, 60 * f, 20 * f, BLACK);
            }
        }

        EndDrawing();



    }

    return 0;
}
