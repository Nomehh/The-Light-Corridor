#include "Ball.hpp"

Ball::Ball() : _coordinates(0, 0, 0, CoordinateType::POINT), _vectors(0, 0, 0, CoordinateType::VECTOR), attached{true}
{
}

void Ball::draw() const
{
    drawSphere();
}
