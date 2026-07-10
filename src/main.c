#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

static void Init() {
    InitWindow(1408, 1408, "Game");
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
