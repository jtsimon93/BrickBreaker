extern "C"
{
#include "raylib.h"
}
#include "Paddle.h"

Paddle::Paddle()
{
    Reset();
}

Paddle::Paddle(Vector2 position, Vector2 speed, float width, float height, Color color)
{
    // Parameterized constructor
    this->position = position;
    this->speed = speed;
    this->width = width;
    this->height = height;
    this->color = color;
}

void Paddle::SetPosition(const Vector2 &newPosition)
{
    position = newPosition;
}

void Paddle::SetSpeed(const Vector2 &newSpeed)
{
    speed = newSpeed;
}

void Paddle::SetWidth(const float &newWidth)
{
    width = newWidth;
}

void Paddle::SetHeight(const float &newHeight)
{
    height = newHeight;
}

const Vector2 &Paddle::GetPosition() const
{
    return position;
}

const Vector2 &Paddle::GetSpeed() const
{
    return speed;
}

float Paddle::GetWidth() const
{
    return width;
}

float Paddle::GetHeight() const
{
    return height;
}

const Color Paddle::GetColor() const
{
    return color;
}

void Paddle::Update()
{
    // Update paddle position based on speed
    position.x += speed.x;
    position.y += speed.y;

    // Keep paddle within screen bounds
    if (position.x < 0)
        position.x = 0;
    if (position.x + width > GetScreenWidth())
        position.x = GetScreenWidth() - width;
}

void Paddle::Draw() const
{
    DrawRectangle((int)position.x, (int)position.y, (int)width, (int)height, color);
}

void Paddle::HandleInput()
{
    // Reset speed first
    speed.x = 0;

    // Handle left/right movement
    if (IsKeyDown(KEY_LEFT))
    {
        speed.x = -10.0f; // Move left
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        speed.x = 10.0f; // Move right
    }
}

void Paddle::Reset() {
    SetPaddleInitialPosition();
    SetPaddleInitialSpeed();
    SetPaddleInitialProperties();
}

void Paddle::SetPaddleInitialPosition() {
    position = {(float)(GetScreenWidth() / 2) - 50, (float)(GetScreenHeight() - 50)};
}

void Paddle::SetPaddleInitialSpeed() {
    speed = {0.0f, 0.0f}; // No initial speed
}

void Paddle::SetPaddleInitialProperties() {
    width = 100.0f;
    height = 20.0f;
    color = WHITE;
}
