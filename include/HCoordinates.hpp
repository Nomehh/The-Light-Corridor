#pragma once

#include "CoordinateType.hpp"
#include <GL/gl.h>
#include <iostream>
#include <cmath>

class HCoordinates
{
public:
    HCoordinates(float x, float y, float z, CoordinateType hcoordinate)
        : _x{x}, _y{y}, _z{z}, _homogeneous_coordinate{hcoordinate} {}

    HCoordinates(float x, float y, float z)
        : _x{x}, _y{y}, _z{z}, _homogeneous_coordinate{CoordinateType::POINT} {}

    HCoordinates(HCoordinates initial_point, float width, float depth, float height)
        : _x{initial_point._x - width}, _y{initial_point._y - depth}, _z{initial_point._z - height}, _homogeneous_coordinate{CoordinateType::POINT}
    {
    }

    void operator+=(const HCoordinates &other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
    }

    HCoordinates operator+(const HCoordinates &other) const
    {
        return HCoordinates(_x + other._x, _y + other._y, _z + other._z);
    }

    HCoordinates operator-(const HCoordinates &other) const
    {
        return HCoordinates(_x - other._x, _y - other._y, _z - other._z);
    }

    void operator+=(float dy)
    {
        _y += dy;
    }

    bool operator<=(const HCoordinates &other) const
    {
        return _x <= other._x && _y <= other._y && _z <= other._z;
    }

    HCoordinates cross(const HCoordinates &c) const
    {
        return HCoordinates(_y * c._z - _z * c._y, _z * c._x - _x * c._z, _x * c._y - _y * c._x);
    }

    HCoordinates normalized() const
    {
        float lg = this->length();
        return HCoordinates(_x / lg, _y / lg, _z / lg);
    }

    float dot(const HCoordinates &a) const
    {
        return (_x * a._x + _y * a._y + _z * a._z);
    }

    HCoordinates operator*(float scalar) const
    {
        return HCoordinates(_x * scalar, _y * scalar, _z * scalar);
    }

    float length() const
    {
        return sqrt(_x * _x + _y * _y + _z * _z);
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

    void translate() const
    {
        glTranslatef(_x, _y, _z);
    }

    float get_x() const
    {
        return _x;
    }

    float get_y() const
    {
        return _y;
    }

    float get_z() const
    {
        return _z;
    }

private:
    float _x;
    float _y;
    float _z;
    CoordinateType _homogeneous_coordinate;
};