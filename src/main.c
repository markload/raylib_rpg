#include <raylib.h>
#include <stdbool.h>

#include "../include/player.h"
#include "../include/level.h"



// Global Variables
#define WINDOW_SIZE 1408

Player *pl;
Camera2D cam;
Level *level;



// Main Functions
static void Init() {
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Game");
    SetTargetFPS(60);

    // Init Player
    pl = NewPlayer(32,
                   LoadTexture("assets/Tilesets/Characters/Char1_32x32.png"),
                   0, 3, 0.2f
    );

    // Init Level
    level = NewLevel(16, "assets/Tilemaps/my_home.map");
}

static void Draw() {
    BeginDrawing();
    BeginMode2D(cam);

    ClearBackground(SKYBLUE);
    level->Draw(level);
    pl->Draw(pl);

    EndMode2D();
    EndDrawing();
}

static void Update() {
    // Update Player
    pl->Update(pl);

    // Update Camera
    cam = (Camera2D){(Vector2){WINDOW_SIZE/2 - pl->tilesize/2, WINDOW_SIZE/2 - pl->tilesize/2},
        (Vector2){pl->dest.x + pl->tilesize/2, pl->dest.y + pl->tilesize/2},
        0.0f, 8.0f
    };
}

static void DeInit() {
    DelPlayer(pl);
    DelLevel(level);
    CloseWindow();
}

int main() {
    Init();

    while (!WindowShouldClose()) {
        Update();
        Draw();
    }

    DeInit();

    return 0;
}
