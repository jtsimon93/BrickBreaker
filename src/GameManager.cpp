#include "GameManager.h"

GameManager::GameManager()
    : gameState(0, 3, 1, 0)
{
    LoadSounds();
    Reset();
}

GameManager::~GameManager()
{
    UnloadSound(brickHitSound);
}

void GameManager::Draw() const
{
    DrawInfo();
    ball.Draw();
    paddle.Draw();

    for (const auto &brick : bricks)
    {
        if (brick.IsActive())
        {
            brick.Draw();
        }
    }

    if (isGamePaused)
    {
        DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 20) / 2, GetScreenHeight() / 2 - 10, 20, WHITE);
    }

    if (isGameOver)
    {
        DrawText("GAME OVER", GetScreenWidth() / 2 - MeasureText("GAME OVER", 20) / 2, GetScreenHeight() / 2 - 10, 20, WHITE);
    }
    else if (isGameWon)
    {
        DrawText("YOU WON!", GetScreenWidth() / 2 - MeasureText("YOU WON!", 20) / 2, GetScreenHeight() / 2 - 10, 20, WHITE);
    }
}

void GameManager::SetGameState(const GameState &newGameState)
{
    gameState = newGameState;
}

void GameManager::SetIsGameOver(bool newIsGameOver)
{
    isGameOver = newIsGameOver;
}

void GameManager::SetIsGamePaused(bool newIsGamePaused)
{
    isGamePaused = newIsGamePaused;
}

void GameManager::SetIsGameStarted(bool newIsGameStarted)
{
    isGameStarted = newIsGameStarted;
}

void GameManager::SetIsGameWon(bool newIsGameWon)
{
    isGameWon = newIsGameWon;
}


void GameManager::SetIsGameReset(bool newIsGameReset)
{
    isGameReset = newIsGameReset;
}

const GameState &GameManager::GetGameState() const
{
    return gameState;
}

bool GameManager::GetIsGameOver() const
{
    return isGameOver;
}

bool GameManager::GetIsGamePaused() const
{
    return isGamePaused;
}

bool GameManager::GetIsGameStarted() const
{
    return isGameStarted;
}

bool GameManager::GetIsGameWon() const
{
    return isGameWon;
}


bool GameManager::GetIsGameReset() const
{
    return isGameReset;
}

void GameManager::Update()
{
    if (isGameOver)
    {
        return;
    }

    if (isGamePaused) {
        PauseGameLoopSound();
    }

    if (!isGamePaused && isGameStarted)
    {
        ball.Update();
        paddle.Update();
        PlayGameLoopSound();
    }

    for (auto &brick : bricks)
    {
        brick.Update();

        if (brick.GetLives() <= 0)
        {
            gameState.SetBricksBroken(gameState.GetBricksBroken() + 1);

            // Remove the brick from the vector
            brick = bricks.back();
            bricks.pop_back();
            PlayBrickHitSound();
        }
    }

    if (ball.IsDied())
    {
        gameState.SetLives(gameState.GetLives() - 1);
        if (gameState.GetLives() <= 0)
        {
            isGameOver = true;
        }
        else
        {
            // Reset the ball position and speed
            ball.Reset();
            isGamePaused = true;
        }
    }

    if (bricks.empty())
    {
        isGameWon = true;
        isGameStarted = false;
        isGamePaused = false;
    }
}

void GameManager::HandleInput()
{
    paddle.HandleInput();

    // Handle game state input (space bar to start/pause)
    if (IsKeyPressed(KEY_SPACE))
    {
        if (!isGameStarted)
        {
            GameFirstStarts();
        }
        else if (isGameOver) {
            Reset();
        }
        else
        {
            // Toggle pause state
            isGamePaused = !isGamePaused;
        }
    }
}

void GameManager::GameFirstStarts()
{
    // Start the game by giving the ball initial velocity
    float initialSpeed = 5.0f;
    ball.SetSpeed({initialSpeed, -initialSpeed}); // Move up-right initially
    isGameStarted = true;
    isGameReset = false;
}

void GameManager::HandleCollisions()
{
    Rectangle paddleRect = {
        paddle.GetPosition().x,
        paddle.GetPosition().y,
        paddle.GetWidth(),
        paddle.GetHeight()};

    Rectangle ballRect = {
        ball.GetPosition().x - ball.GetRadius(),
        ball.GetPosition().y - ball.GetRadius(),
        ball.GetRadius() * 2,
        ball.GetRadius() * 2};

    ball.HandleCollision(paddleRect);

    for (auto &brick : bricks)
    {
        if (brick.IsActive() && CheckCollisionRecs(ballRect, brick.GetRect()))
        {
            if (brick.Hit())
            {
                gameState.SetScore(gameState.GetScore() + 10);
                ball.SetSpeed({ball.GetSpeed().x, -ball.GetSpeed().y}); // Reverse vertical speed
            }
        }
    }
}

void GameManager::DrawInfo() const
{
    // Calculate positions for horizontal layout
    int scoreWidth = MeasureText(TextFormat("Score: %d", gameState.GetScore()), 20);
    int livesWidth = MeasureText(TextFormat("Lives: %d", gameState.GetLives()), 20);

    // Position elements with equal spacing across top of screen
    int screenWidth = GetScreenWidth();
    int padding = 20; // Space between elements

    // Draw game information horizontally (score, lives, level)
    DrawText(TextFormat("Score: %d", gameState.GetScore()), padding, 10, 20, WHITE);
    DrawText(TextFormat("Lives: %d", gameState.GetLives()),
             screenWidth / 2 - livesWidth / 2, 10, 20, WHITE); // Centered
    DrawText(TextFormat("Level: %d", gameState.GetLevel()),
             screenWidth - MeasureText(TextFormat("Level: %d", gameState.GetLevel()), 20) - padding,
             10, 20, WHITE); // Right-aligned
}

void GameManager::Reset()
{
    ball.Reset();
    paddle.Reset();
    gameState.Reset();
    InitializeBricks();

    isGameOver = false;
    isGamePaused = false;
    isGameStarted = false;
    isGameWon = false;
    isGameReset = true;
}

void GameManager::InitializeBricks()
{
    bricks.clear();

    const float brickWidth = 40.0f;
    const float brickHeight = 20.0f;
    const float padding = 5.0f;
    const float startY = 50.0f;
    const int bricksPerRow = 7;
    const float totalBrickWidth = bricksPerRow * (brickWidth + padding) - padding;
    const float startX = (GetScreenWidth() - totalBrickWidth) / 2.0f;

    for (int row = 0; row < 3; row++)
    {
        int livesForRow = 3 - row;

        Color brickColor;
        switch (livesForRow)
        {
        case 3:
            brickColor = RED;
            break;
        case 2:
            brickColor = BLUE;
            break;
        case 1:
            brickColor = WHITE;
            break;
        default:
            brickColor = BLACK;
            break;
        }

        for (int col = 0; col < bricksPerRow; col++)
        {
            const float x = startX + col * (brickWidth + padding);
            const float y = startY + row * (brickHeight + padding);

            bricks.push_back(Brick(x, y, brickWidth, brickHeight, livesForRow, brickColor));
        }
    }
}

void GameManager::LoadSounds() {
    brickHitSound = {0};
    gameLoopSound = {0};
    brickHitSound = LoadSound("assets/sounds/brickbreak.mp3");
    gameLoopSound = LoadSound("assets/sounds/gameloopsound.mp3");
}

void GameManager::PlayBrickHitSound() const {
    if (IsAudioDeviceReady() && brickHitSound.frameCount > 0 && !IsSoundPlaying(brickHitSound) && IsSoundValid(brickHitSound)) {
        PlaySound(brickHitSound);
        SetSoundVolume(brickHitSound, 0.5f);
    }
}

void GameManager::PlayGameLoopSound() const {
    if (IsAudioDeviceReady() && gameLoopSound.frameCount > 0 && !IsSoundPlaying(gameLoopSound) && IsSoundValid(gameLoopSound)) {
        PlaySound(gameLoopSound);
    }
}

void GameManager::PauseGameLoopSound() const {
    if (IsSoundPlaying(gameLoopSound)) {
        PauseSound(gameLoopSound);
    }
}
