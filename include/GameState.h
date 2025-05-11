#pragma once

class GameState
{
private:
    int score;
    int lives;
    int level;
    int bricksBroken;

public:
    GameState(int score, int lives, int level, int bricksBroken);
    ~GameState() = default;

    void SetScore(const int newScore);
    void SetLives(const int newLives);
    void SetLevel(const int newLevel);
    void SetBricksBroken(const int newBricksBroken);

    int GetScore() const;
    int GetLives() const;
    int GetLevel() const;
    int GetBricksBroken() const;

    void Reset();
};