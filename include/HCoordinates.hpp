#pragma once

#include "CoordinateType.hpp"
#include <GL/gl.h>
#include <iostream>
class HCoordinates
{
public:
    HCoordinates(float x, float y, float z, CoordinateType hcoordinate)
        : _x{x}, _y{y}, _z{z}, _homogeneous_coordinate{hcoordinate} {}

    HCoordinates(float x, float y, float z)
        : _x{x}, _y{y}, _z{z}, _homogeneous_coordinate{CoordinateType::POINT} {}

    void operator+=(const HCoordinates &other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
    }

    void operator+=(float dy)
    {
        _y += dy;
    }

    void draw() const
    {
        if (_homogeneous_coordinate == CoordinateType::POINT)
        {
            glVertex3f(_x, _y, _z);
        }
    }

    void print() const
    {
        std::cout << "HCoordinates x: " << _x << " y: " << _y << " z: " << _z << std::endl;
    }

private:
    float _x;
    float _y;
    float _z;
    CoordinateType _homogeneous_coordinate;
};