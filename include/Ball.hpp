#pragma once

#include "HCoordinates.hpp"
#include "3D_tools.hpp"
#include "CoordinateType.hpp"
#include <GLFW/glfw3.h>
#include <vector>

#define BALL_SIZE 0.1f

class Ball
{
public:
    Ball();
    void draw() const;
    void move(float x, float z);
    void move();
    void translate() const;
    void updatePos(float x, float y, bool isAttached);
    bool is_inside(std::vector<HCoordinates> _vertices);

    float get_x() const;
    float get_y() const;
    float get_z() const;

    const HCoordinates &get_coordinates() const { return _coordinates; }
    const HCoordinates &get_vectors() const { return _vectors; }

    void set_vectors(HCoordinates vectors) { _vectors = std::move(vectors); }

private:
    HCoordinates _coordinates;
    HCoordinates _vectors;
    bool _attached;
};