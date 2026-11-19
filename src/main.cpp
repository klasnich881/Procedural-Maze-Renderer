#include "raylib.h"
#include "MazeMap.h"
int main() {
    const int tileSize = 32;
    MazeMap maze(21,21);
    maze.generateMaze();
    InitWindow(maze.getWidth() * tileSize,maze.getHeight() * tileSize, "Procedural Maze Raycaster - Sprint 1");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_R)) maze.generateMaze();
        BeginDrawing();
        ClearBackground(BLACK);
        for(int y = 0; y < maze.getHeight(); ++y){

            for(int x = 0; x < maze.getWidth(); ++x){
                Color tileColor = maze.isWall(x,y) ? DARKGRAY : RAYWHITE;
                DrawRectangle(x * (tileSize - 1), y * (tileSize - 1),tileSize - 1, tileSize - 1, tileColor);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}