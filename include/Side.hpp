#pragma once

#include "HCoordinates.hpp"
#include "Color.hpp"

#include <vector>
#include <GL/gl.h>
#include <memory>
#include <iostream>

class Side
{
public:
    Side(std::vector<HCoordinates> vertices, Color color)
        : _vertices{std::move(vertices)}, _color{std::move(color)}
    {
    }

    void advance(double dy)
    {
        for (auto &vertex : _vertices)
        {
            vertex += dy;
        }
    }

    void draw() const
    {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(_color._r, _color._g, _color._b);
        for (const auto &vertex : _vertices)
        {
            vertex.draw();
        }
        glEnd();
    }

    void drawRacket() const
    {
        glBegin(GL_LINE_LOOP);
        glColor3f(_color._r, _color._g, _color._b);
        for (const auto &vertex : _vertices)
        {
            vertex.draw();
        }
        glEnd();
    }

    std::vector<HCoordinates> &get_vertices()
    {
        return _vertices;
    }

    void print() const
    {
        std::cout << "Side vertices: ";
        for (const auto &vertex : _vertices)
        {
            vertex.print();
        }
        std::cout << std::endl;
    }

private:
    std::vector<HCoordinates> _vertices;
    const Color _color;
};