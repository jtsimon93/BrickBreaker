#pragma once

#include "GameState.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <vector>

class GameManager
{
private:
    GameState gameState;
    bool isGameOver;
    bool isGamePaused;
    bool isGameStarted;
    bool isGameWon;
    bool isGameReset;

    Ball ball;
    Paddle paddle;
    std::vector<Brick> bricks;

    void InitializeBricks();

public:
    GameManager();
    ~GameManager() = default;

    void SetGameState(const GameState &newGameState);
    void SetIsGameOver(bool newIsGameOver);
    void SetIsGamePaused(bool newIsGamePaused);
    void SetIsGameStarted(bool newIsGameStarted);
    void SetIsGameWon(bool newIsGameWon);
    void SetIsGameReset(bool newIsGameReset);

    const GameState &GetGameState() const;
    bool GetIsGameOver() const;
    bool GetIsGamePaused() const;
    bool GetIsGameStarted() const;
    bool GetIsGameWon() const;
    bool GetIsGameReset() const;

    void Draw() const;
    void Update();
    void HandleInput();
    void GameFirstStarts();
    void HandleCollisions();
    void DrawInfo() const;
    void Reset();
};