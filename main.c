//
// Created by maell on 07/11/2022.
//
#include <stdio.h>
#include "test.c"
#include <time.h>
#include <raylib.h>
int main ()
{
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Raylib > Allegro");


    while (!WindowShouldClose()) {
        float f = (float)GetScreenWidth() / (float)GetScreenHeight();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib > Allegro", 12 * f, 12 * f, 20 * f, BLACK);
        DrawText("Popo > tout le monde", 30 * f, 30 * f, 30 * f, BLACK);
        EndDrawing();
    }
    return 0;
}
