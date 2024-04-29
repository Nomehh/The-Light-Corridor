#include "Ball.hpp"

Ball::Ball() : _coordinates(0, 0, 0, CoordinateType::POINT), _vectors(0.05, -0.005, 0, CoordinateType::VECTOR), _attached{true}
{
}

void Ball::draw() const
{
    glPushMatrix();
    translate();
    glScalef(BALL_SIZE, BALL_SIZE, BALL_SIZE);
    drawSphere();
    glPopMatrix();
}

void Ball::move(float x, float z)
{
    _coordinates = HCoordinates{x, 13, z};
}

void Ball::move()
{
    _coordinates += _vectors;
}

void Ball::translate() const
{
    _coordinates.translate();
}

void Ball::updatePos(float x, float y, bool isAttached)
{
    _attached = isAttached;
    if (_attached)
    {
        move(x, y);
        return;
    }
    move();
}

float Ball::get_x() const { return _coordinates.get_x(); }
float Ball::get_y() const { return _coordinates.get_y(); }
float Ball::get_z() const { return _coordinates.get_z(); }