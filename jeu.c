//
// Created by maell on 10/11/2022.
//

#include "jeu.h"
void fonction_principale(){

    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Raylib > Allegro");

    SetTargetFPS(FPS);
    TIME t = {0};




    while (!WindowShouldClose()) {
        float f = (float)GetScreenWidth() / (float)GetScreenHeight();



        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib > Allegro5", 12  , 12, 20 , BLACK);
        affichage_temps(temps(&t));
        EndDrawing();



    }

}