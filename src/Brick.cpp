#include "Brick.h"

Brick::Brick()
{
    rect = {0, 0, 0, 0};
    lives = 0;
    maxLives = 0;
    active = false;
    color = BLACK;
};

Brick::Brick(float x, float y, float width, float height, int lives, Color color)
    : rect{x, y, width, height}, lives(lives), maxLives(lives), active(true), color(color) {}

Rectangle Brick::GetRect() const
{
    return rect;
}

int Brick::GetLives() const
{
    return lives;
}

bool Brick::IsActive() const
{
    return active;
}

bool Brick::Hit()
{
    if (lives > 0)
    {
        lives--;
        if (lives == 0)
        {
            active = false;
        }
        return true;
    }
    return false;
}

void Brick::Draw() const
{
    DrawRectangleRec(rect, color);
}

void Brick::Update()
{
    switch (lives)
    {
    case 1:
        color = WHITE;
        break;
    case 2:
        color = BLUE;
        break;
    case 3:
        color = RED;
        break;
    default:
        color = BLACK;
        break;
    }

    if (lives <= 0)
    {
        active = false;
    }
}
