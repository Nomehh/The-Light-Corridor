#include "Ball.hpp"

#define DEFAULT_DIR \
    HCoordinates { 0.005, -0.05, -0.001, CoordinateType::VECTOR }

Ball::Ball() : _coordinates(0, 0, 0, CoordinateType::POINT), _vectors(DEFAULT_DIR), _attached{true}
{
}

void Ball::draw() const
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    translate();
    glScalef(BALL_SIZE, BALL_SIZE, BALL_SIZE);
    drawSphere();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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
        this->set_vectors(DEFAULT_DIR);
        move(x, y);
        return;
    }
    move();
}

float Ball::get_x() const { return _coordinates.get_x(); }
float Ball::get_y() const { return _coordinates.get_y(); }
float Ball::get_z() const { return _coordinates.get_z(); }