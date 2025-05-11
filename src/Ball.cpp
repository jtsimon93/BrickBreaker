extern "C"
{
#include "raylib.h"
}
#include "Ball.h"
#include <cmath>

Ball::Ball()
{
    // Default constructor
    // Just set the ball not moving and in the center of the screen
    position.x = GetScreenWidth() / 2.0f;
    position.y = GetScreenHeight() / 2.0f;
    speed = {0.0f, 0.0f};
    radius = 10.0f;
    color = WHITE;
}

Ball::Ball(Vector2 position, Vector2 speed, float radius, Color color)
    : position(position), speed(speed), radius(radius), color(color) {}

void Ball::SetPosition(const Vector2 &newPosition)
{
    position = newPosition;
}

void Ball::SetSpeed(const Vector2 &newSpeed)
{
    speed = newSpeed;
}

void Ball::SetRadius(const float &newRadius)
{
    radius = newRadius;
}

void Ball::SetColor(const Color &newColor)
{
    color = newColor;
}

void Ball::SetDied(bool newDied)
{
    died = newDied;
}

const Vector2 &Ball::GetPosition() const
{
    return position;
}

const Vector2 &Ball::GetSpeed() const
{
    return speed;
}

float Ball::GetRadius() const
{
    return radius;
}

const Color &Ball::GetColor() const
{
    return color;
}

bool Ball::IsDied() const
{
    return died;
}

void Ball::Update()
{
    // Update position based on speed
    position.x += speed.x;
    position.y += speed.y;

    // Check for collision with the window borders
    bool collisionX = false;
    bool collisionY = false;

    // Handle horizontal borders
    if (position.x - radius < 0)
    {
        position.x = radius; // Prevent going out of bounds
        speed.x = -speed.x;  // Reverse horizontal direction
        collisionX = true;
    }
    else if (position.x + radius > GetScreenWidth())
    {
        position.x = GetScreenWidth() - radius; // Prevent going out of bounds
        speed.x = -speed.x;                     // Reverse horizontal direction
        collisionX = true;
    }

    // Handle vertical borders (top only, bottom is game over)
    if (position.y - radius < 0)
    {
        position.y = radius; // Prevent going out of bounds
        speed.y = -speed.y;  // Reverse vertical direction
        collisionY = true;
    }

    // Fix the "stuck in vertical motion" bug
    // If the ball is moving too vertically (very little horizontal movement)
    const float minHorizontalSpeed = 2.0f;
    if (std::abs(speed.x) < minHorizontalSpeed)
    {
        // Add some horizontal movement in the appropriate direction
        speed.x = (speed.x >= 0) ? minHorizontalSpeed : -minHorizontalSpeed;
    }

    // If the ball touches the bottom of the screen, set game over
    if (position.y + radius > GetScreenHeight())
    {
        SetSpeed({0.0f, 0.0f}); // Stop the ball
        SetDied(true);          // Mark the ball as dead
    }
}

void Ball::Draw() const
{
    DrawCircleV(position, radius, color);
}

void Ball::HandleCollision(const Rectangle &paddleRect)
{
    // Check for collision with the paddle
    if (CheckCollisionCircleRec(position, radius, paddleRect))
    {
        // Calculate the new speed based on the collision
        float paddleCenterX = paddleRect.x + paddleRect.width / 2.0f;
        float ballCenterX = position.x;

        // Calculate the angle of reflection based on where the ball hits the paddle
        float relativeIntersectX = ballCenterX - paddleCenterX;
        float normalizedRelativeIntersectionX = relativeIntersectX / (paddleRect.width / 2.0f);

        // Set the new speed based on the angle of reflection
        speed.x = normalizedRelativeIntersectionX * 5.0f; // Adjust this value for speed
        speed.y *= -1;                                    // Reverse vertical speed
    }
}

void Ball::Reset()
{
    // Reset ball position to the center of the screen
    position.x = GetScreenWidth() / 2.0f;
    position.y = GetScreenHeight() / 2.0f;

    // Reset speed to 0 (not moving)
    speed = {5.0f, -5.0f};

    // Set the ball as not dead
    died = false;
}