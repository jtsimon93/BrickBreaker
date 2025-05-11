#include "GameState.h"

GameState::GameState(int score, int lives, int level, int bricksBroken)
    : score(score), lives(lives), level(level), bricksBroken(bricksBroken) {}

void GameState::SetScore(const int newScore)
{
    score = newScore;
}

void GameState::SetLives(const int newLives)
{
    lives = newLives;
}

void GameState::SetLevel(const int newLevel)
{
    level = newLevel;
}

void GameState::SetBricksBroken(const int newBricksBroken)
{
    bricksBroken = newBricksBroken;
}

int GameState::GetScore() const
{
    return score;
}

int GameState::GetLives() const
{
    return lives;
}

int GameState::GetLevel() const
{
    return level;
}

int GameState::GetBricksBroken() const
{
    return bricksBroken;
}

void GameState::Reset()
{
    score = 0;
    lives = 3;
    level = 1;
    bricksBroken = 0;
}