#pragma once

#include "HCoordinates.hpp"
#include "3D_tools.hpp"
#include "CoordinateType.hpp"
#include <GLFW/glfw3.h>

class Ball
{
public:
    Ball();
    void draw() const;

private:
    HCoordinates _coordinates;
    HCoordinates _vectors;
    bool attached;
};