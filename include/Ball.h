#pragma once
extern "C"
{
#include "raylib.h"
}

class Ball
{
private:
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
    bool died = false;

    void SetBallInitialPosition();
    void SetBallInitialSpeed();
    void SetBallInitialProperties();

public:
    Ball();
    Ball(Vector2 position, Vector2 speed, float radius, Color color);
    ~Ball() = default;

    void SetPosition(const Vector2 &newPosition);
    void SetSpeed(const Vector2 &newSpeed);
    void SetRadius(const float &newRadius);
    void SetColor(const Color &newColor);
    void SetDied(bool newDied);

    const Vector2 &GetPosition() const;
    const Vector2 &GetSpeed() const;
    float GetRadius() const;
    const Color &GetColor() const;
    bool IsDied() const;

    void Update();
    void Draw() const;
    void HandleCollision(const Rectangle &paddleRect);
    void Reset();
};
