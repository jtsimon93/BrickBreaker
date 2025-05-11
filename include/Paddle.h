#pragma once

extern "C"
{
#include "raylib.h"
}

class Paddle
{
private:
    Vector2 position;
    Vector2 speed;
    float width;
    float height;
    Color color;

    void SetPaddleInitialPosition();
    void SetPaddleInitialSpeed();
    void SetPaddleInitialProperties();

public:
    Paddle();
    Paddle(Vector2 position, Vector2 speed, float width, float height, Color color);
    ~Paddle() = default;

    void SetPosition(const Vector2 &newPosition);
    void SetSpeed(const Vector2 &newSpeed);
    void SetWidth(const float &newWidth);
    void SetHeight(const float &newHeight);

    const Vector2 &GetPosition() const;
    const Vector2 &GetSpeed() const;
    float GetWidth() const;
    float GetHeight() const;
    const Color GetColor() const;

    void HandleInput();
    void Update();
    void Draw() const;
    void Reset();
};