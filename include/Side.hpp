#pragma once

#include "HCoordinates.hpp"
#include "Color.hpp"

#include <vector>
#include <GL/gl.h>
#include <memory>
#include <iostream>
#include "Ball.hpp"
#include "SideIndicator.hpp"
#include <cmath>

class Side
{
public:
    Side(std::vector<HCoordinates> vertices, Color color, SideIndicator side_indicator)
        : _vertices{std::move(vertices)}, _color{std::move(color)}, _side_indicator{std::move(side_indicator)}
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
        GLfloat light_spec[] = {0.1, 0.1, 0.1};
        GLfloat amb[] = {_color._r, _color._g, _color._b, 1.0};
        GLfloat color[] = {_color._r, _color._g, _color._b, 1.0};

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_spec);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 5.);
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

    HCoordinates projectOntoPlane(const HCoordinates &center, const HCoordinates &planeNormal) const
    {
        auto dotProduct = center.dot(planeNormal);
        HCoordinates projection = center - (planeNormal * dotProduct);

        return projection;
    }

    bool front_back_check(const HCoordinates &ball) const
    {
        return ball.get_x() <= _vertices[0].get_x() && ball.get_x() >= _vertices[1].get_x() &&
               ball.get_z() <= _vertices[0].get_z() && ball.get_z() >= _vertices[3].get_z();
    }

    bool top_bottom_check(const HCoordinates &ball) const
    {
        return ball.get_x() <= _vertices[0].get_x() && ball.get_x() >= _vertices[1].get_x() &&
               ball.get_y() <= _vertices[0].get_y() && ball.get_y() >= _vertices[3].get_y();
    }

    bool left_right_check(const HCoordinates &ball) const
    {
        return ball.get_y() <= _vertices[0].get_y() && ball.get_y() >= _vertices[1].get_y() &&
               ball.get_z() <= _vertices[0].get_z() && ball.get_z() >= _vertices[3].get_z();
    }

    bool ball_in_quad(const HCoordinates &ball) const
    {
        switch (_side_indicator)
        {
        case SideIndicator::FRONT_BACK:
            return front_back_check(ball);
        case SideIndicator::LEFT_RIGHT:
            return left_right_check(ball);
        case SideIndicator::TOP_BOTTOM:
            return top_bottom_check(ball);
        }
    }

    void ball_collision(Ball &ball) const
    {
        HCoordinates v1 = _vertices[1] - _vertices[0];
        HCoordinates v2 = _vertices[3] - _vertices[0];
        HCoordinates normal = v1.cross(v2).normalized();

        auto d = normal.dot(_vertices[0]);
        auto distance = -normal.dot(ball.get_coordinates()) + d;

        auto ballOnPlane = projectOntoPlane(ball.get_coordinates(), normal);

        if (std::abs(distance) <= BALL_SIZE && ball_in_quad(ballOnPlane))
        {
            auto u = ball.get_vectors();
            auto dotProduct = u.dot(normal);
            HCoordinates reflectedVelocity = u - (normal * dotProduct * 2.0f);

            ball.set_vectors(reflectedVelocity);
            ball.updatePos(ball.get_x(), ball.get_y(), false);
        }
    }

    const std::vector<HCoordinates> &get_vertices() const { return _vertices; }

private:
    std::vector<HCoordinates> _vertices;
    const Color _color;
    SideIndicator _side_indicator;
};