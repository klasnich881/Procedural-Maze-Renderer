#include "raylib.h"

int main() {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Procedural Maze Raycaster - Sprint 1");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("TICKET-1 COMPLETE: Engine Online", 220, 280, 20, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}