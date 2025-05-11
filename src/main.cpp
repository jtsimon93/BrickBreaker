extern "C"
{
#include "raylib.h"
}

#include <iostream>
#include <memory>
#include "GameManager.h"

int main()
{
    constexpr int screenWidth = 340;
    constexpr int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "Brick Breaker");
    InitAudioDevice();
    SetTargetFPS(60);

    auto gameManager = std::make_unique<GameManager>();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        gameManager->HandleCollisions();
        gameManager->HandleInput();
        gameManager->Update();
        gameManager->Draw();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}