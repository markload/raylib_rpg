#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/player.h"

// Global Variables
#define TITLE "Game"
#define SCREEN_W 1408
#define SCREEN_H 1408
#define TILE_SIZE 8

Player pl;

static void Init() {
    InitWindow(SCREEN_W, SCREEN_H, TITLE);
}

static void DeInit() {
    CloseWindow();
}

static void Draw() {
    BeginDrawing();
    EndDrawing();
}

static void Update() {
    float timer = GetFrameTime();
    printf("%f\n", timer);
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
