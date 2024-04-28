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

private:
    Side _racket;
};