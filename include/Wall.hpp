#pragma once

#include "Side.hpp"
#include "Color.hpp"

#include <vector>
#include <memory>

#define CORRIDOR_PART_SIZE 5.0f

class Wall
{
public:
    Wall(std::vector<Side> sides)
        : _sides{std::move(sides)}
    {
    }

    static Wall create_corridor_part(float starting_y_point)
    {
        std::vector<Side> sides;
        std::vector<HCoordinates> vertices;

        vertices.emplace_back(2, starting_y_point, 1);
        vertices.emplace_back(-2, starting_y_point, 1);
        vertices.emplace_back(-2, starting_y_point - CORRIDOR_PART_SIZE, 1);
        vertices.emplace_back(2, starting_y_point - CORRIDOR_PART_SIZE, 1);
        sides.emplace_back(vertices, Color(0.5, 0.3, 0.0));

        vertices.clear();
        vertices.emplace_back(2, starting_y_point, -1);
        vertices.emplace_back(-2, starting_y_point, -1);
        vertices.emplace_back(-2, starting_y_point - CORRIDOR_PART_SIZE, -1);
        vertices.emplace_back(2, starting_y_point - CORRIDOR_PART_SIZE, -1);
        sides.emplace_back(vertices, Color(0.3, 0., 0.5));

        vertices.clear();
        vertices.emplace_back(2, starting_y_point, 1);
        vertices.emplace_back(2, starting_y_point, -1);
        vertices.emplace_back(2, starting_y_point - CORRIDOR_PART_SIZE, -1);
        vertices.emplace_back(2, starting_y_point - CORRIDOR_PART_SIZE, 1);
        sides.emplace_back(vertices, Color(0.4, 0., 0.5));

        vertices.clear();
        vertices.emplace_back(-2, starting_y_point, 1);
        vertices.emplace_back(-2, starting_y_point, -1);
        vertices.emplace_back(-2, starting_y_point - CORRIDOR_PART_SIZE, -1);
        vertices.emplace_back(-2, starting_y_point - CORRIDOR_PART_SIZE, 1);
        sides.emplace_back(vertices, Color(0.6, 0., 0.5));

        return Wall(sides);
    }

    static std::vector<Wall> initial_corridor()
    {
        std::vector<Wall> walls;
        for (int i = 0; i < 6; i++)
        {
            walls.emplace_back(create_corridor_part(i * CORRIDOR_PART_SIZE));
        }
        return walls;
    }

    void advance_wall(float dy)
    {
        for (auto &side : _sides)
        {
            side.advance(dy);
        }
    }

    void draw() const
    {
        for (const auto &side : _sides)
        {
            side.draw();
        }
    }

private:
    std::vector<Side> _sides;
};