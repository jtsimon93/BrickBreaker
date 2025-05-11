#pragma once

extern "C"
{
#include "raylib.h"
}

class Brick
{
private:
    Rectangle rect;
    int lives;
    int maxLives;
    bool active;
    Color color;

public:
    Brick();
    Brick(float x, float y, float width, float height, int lives, Color color);
    ~Brick() = default;

    Rectangle GetRect() const;
    int GetLives() const;
    bool IsActive() const;

    bool Hit();

    void Draw() const;
    void Update();
};