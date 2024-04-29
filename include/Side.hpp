#pragma once

#include "HCoordinates.hpp"
#include "Color.hpp"

#include <vector>
#include <GL/gl.h>
#include <memory>
#include <iostream>
#include "Ball.hpp"
#include <cmath>

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

    void ball_collision(Ball &ball) const
    {
        // Calcul du vecteur normal au plan
        HCoordinates v1 = _vertices[1] - _vertices[0];
        HCoordinates v2 = _vertices[2] - _vertices[0];
        HCoordinates normal = v1.cross(v2).normalized();

        // Calcul du coefficient d de l'équation du plan : ax + by + cz + d = 0
        float d = -normal.dot(_vertices[0]);

        // Calcul de la distance entre le centre de la sphère et le plan
        float distance = normal.dot(ball.get_coordinates()) + d;

        // Si la distance est inférieure au rayon de la sphère, il y a collision
        if (std::abs(distance) <= BALL_SIZE)
        {
            // Calculer la réflexion de la vitesse de la balle par rapport au vecteur normal
            auto u = ball.get_vectors();
            auto dotProduct = u.dot(normal);
            HCoordinates reflectedVelocity = u - (normal * dotProduct * 2.0f);

            // Mettre à jour la direction de la balle avec la réflexion calculée
            ball.set_vectors(reflectedVelocity);
        }
    }

private:
    std::vector<HCoordinates> _vertices;
    const Color _color;
};