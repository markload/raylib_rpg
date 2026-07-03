#include <raylib.h>
#include <stdbool.h>

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
