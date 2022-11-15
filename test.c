#include "test.h"


TIME temps(TIME *t){

    t->frames++;
    //TEMPMS REEL
    if(t->frames==60) {
        t->secondereel++;
        t->secondefictif++;
        t->frames = 0;
        if(t->secondereel==60){
            t->minutereel++;
            t->secondereel = 0;
            if(t->minutereel==60){
                t->heurereel++;
                t->minutereel = 0;
            }
        }
        if(t->secondefictif==15){
            t->mois++;
            t->secondefictif = 0;
            if(t->mois == 12){
                t->annee ++;
                t->mois =0;
            }
        }

    }
    return *t;
}

void drawplateau (){
    for (float i = 0; i <= NB_LIGNE; ++i) {
        DrawLine3D((Vector3){0, 0.01, i}, (Vector3){NB_COLONNE, 0.01, i}, WHITE);
    }
    for (float i = 0; i <= NB_COLONNE; ++i) {
        DrawLine3D((Vector3){i, 0.01, 0}, (Vector3){i, 0.01, NB_LIGNE}, WHITE);
    }
}

void detectionCase3D (RayCollision  * posSouris3D) {
    float ret = posSouris3D->point.x;
    for (int i = 0; i < NB_LIGNE; ++i) {
        if (posSouris3D->point.z > i && posSouris3D->point.z < i+1){
            posSouris3D->point.z = i+0.5;
        }
    }
    for (int i = 0; i < NB_COLONNE; ++i) {
        if (posSouris3D->point.x > i && posSouris3D->point.x < i+1){
            posSouris3D->point.x = i+0.5;
        }
    }
    if (ret == posSouris3D->point.x) {
        posSouris3D->point.x = 0;
    }
}

void fonction3D(ECE_City * eceCity){

    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Raylib > Allegro");

    Vector3 posCentre = { 22.5f, 0.0f, 17.5f };

    Ray ray;
    RayCollision posSouris3D;

    Camera3D camera = { 0 };
    camera.position = (Vector3){ -7.0f, 50.0f, -7.0f };
    camera.target = (Vector3){ 16.36f, 0.0f, 12.72f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 plan1 = { 0.0f, 0.0f, 0.0f };
    Vector3 plan2 = { NB_COLONNE, 0.0f, 0.0f };
    Vector3 plan3 = { NB_COLONNE, 0.0f, NB_LIGNE };
    Vector3 plan4 = { 0.0f, 0.0f, NB_LIGNE };

    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();
        mousePos.y += 13;
        ray = GetMouseRay(mousePos, camera);

        BeginDrawing();
        BeginMode3D(camera);
        ClearBackground(GRAY);

        DrawPlane(posCentre, (Vector2){46, 36}, BLACK);
        drawplateau();

        posSouris3D = GetRayCollisionQuad(ray, plan1, plan2, plan3, plan4);
        detectionCase3D(&posSouris3D);
        if (posSouris3D.point.x != 0) {
            DrawCube(posSouris3D.point, 0.8, 0.3, 0.8, BLUE);
        }

        EndMode3D();
        EndDrawing();
    }
}
