#pragma once

#include "Side.hpp"
#include "HCoordinates.hpp"
#include "Color.hpp"
#include <vector>
#include "GL/gl.h"
#include <iostream>

#define RACKET_SIZE 0.2f
#define DIST 13.f

class Racket
{
public:
    Racket();
    Racket(float x, float z);

    void draw() const;

    void updatePos(float x, float z);

    void print() const
    {
        return _racket.print();
    }

    void check_collision(Ball &ball) const;

    HCoordinates projectOntoPlane(const HCoordinates &center, const HCoordinates &planeNormal) const;

    bool front_back_check(const HCoordinates &ball) const
    {
        return ball.get_x() <= _racket.get_vertices()[0].get_x() && ball.get_x() >= _racket.get_vertices()[1].get_x() &&
               ball.get_z() <= _racket.get_vertices()[0].get_z() && ball.get_z() >= _racket.get_vertices()[3].get_z();
    }

private:
    Side _racket;
    HCoordinates _center = HCoordinates(0, 13, 0);
};