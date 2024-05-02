#pragma once

#include "Side.hpp"
#include "Color.hpp"

#include <vector>
#include <memory>
#include "Ball.hpp"

#define CORRIDOR_PART_SIZE 5.0f
#define LEFT_LIMIT 2.f
#define RIGHT_LIMIT -2.f
#define TOP_LIMIT 1.f
#define BOTTOM_LIMIT -1.f
#define CORRIDOR_WIDTH 4.f
#define CORRIDOR_HEIGHT 2.f

class Wall
{
public:
    Wall(std::vector<Side> sides)
        : _sides{std::move(sides)}
    {
    }

    static Wall create_obstacle(HCoordinates top_left_front, float width, float height, float depth, Color color)
    {
        std::vector<Side> sides;
        std::vector<HCoordinates> vertices;

        // front side
        vertices.emplace_back(top_left_front, 0, 0, 0);
        vertices.emplace_back(top_left_front, width, 0, 0);
        vertices.emplace_back(top_left_front, width, 0, height);
        vertices.emplace_back(top_left_front, 0, 0, height);
        sides.emplace_back(vertices, color, SideIndicator::FRONT_BACK);

        // top side
        vertices.clear();
        vertices.emplace_back(top_left_front, 0, 0, 0);
        vertices.emplace_back(top_left_front, width, 0, 0);
        vertices.emplace_back(top_left_front, width, depth, 0);
        vertices.emplace_back(top_left_front, 0, depth, 0);
        sides.emplace_back(vertices, color, SideIndicator::TOP_BOTTOM);

        // back side
        vertices.clear();
        vertices.emplace_back(top_left_front, 0, depth, 0);
        vertices.emplace_back(top_left_front, width, depth, 0);
        vertices.emplace_back(top_left_front, width, depth, height);
        vertices.emplace_back(top_left_front, 0, depth, height);
        sides.emplace_back(vertices, color, SideIndicator::FRONT_BACK);

        // bottom side
        vertices.clear();
        vertices.emplace_back(top_left_front, 0, 0, height);
        vertices.emplace_back(top_left_front, width, 0, height);
        vertices.emplace_back(top_left_front, width, depth, height);
        vertices.emplace_back(top_left_front, 0, depth, height);
        sides.emplace_back(vertices, color, SideIndicator::TOP_BOTTOM);

        // left side
        vertices.clear();
        vertices.emplace_back(top_left_front, 0, 0, 0);
        vertices.emplace_back(top_left_front, 0, depth, 0);
        vertices.emplace_back(top_left_front, 0, depth, height);
        vertices.emplace_back(top_left_front, 0, 0, height);
        sides.emplace_back(vertices, color, SideIndicator::LEFT_RIGHT);

        // right side
        vertices.clear();
        vertices.emplace_back(top_left_front, width, 0, 0);
        vertices.emplace_back(top_left_front, width, depth, 0);
        vertices.emplace_back(top_left_front, width, depth, height);
        vertices.emplace_back(top_left_front, width, 0, height);
        sides.emplace_back(vertices, color, SideIndicator::LEFT_RIGHT);

        return Wall(sides);
    }

    static Wall create_corridor_part(float starting_y_point)
    {
        std::vector<Side> sides;
        std::vector<HCoordinates> vertices;

        vertices.emplace_back(LEFT_LIMIT, starting_y_point, TOP_LIMIT);
        vertices.emplace_back(RIGHT_LIMIT, starting_y_point, TOP_LIMIT);
        vertices.emplace_back(RIGHT_LIMIT, starting_y_point - CORRIDOR_PART_SIZE, TOP_LIMIT);
        vertices.emplace_back(LEFT_LIMIT, starting_y_point - CORRIDOR_PART_SIZE, TOP_LIMIT);
        sides.emplace_back(vertices, Color(0.35, 0.36, 0.40), SideIndicator::TOP_BOTTOM);

        vertices.clear();
        vertices.emplace_back(LEFT_LIMIT, starting_y_point, BOTTOM_LIMIT);
        vertices.emplace_back(RIGHT_LIMIT, starting_y_point, BOTTOM_LIMIT);
        vertices.emplace_back(RIGHT_LIMIT, starting_y_point - CORRIDOR_PART_SIZE, BOTTOM_LIMIT);
        vertices.emplace_back(LEFT_LIMIT, starting_y_point - CORRIDOR_PART_SIZE, BOTTOM_LIMIT);
        sides.emplace_back(vertices, Color(0.35, 0.36, 0.40), SideIndicator::TOP_BOTTOM);

        vertices.clear();
        vertices.emplace_back(LEFT_LIMIT, starting_y_point, TOP_LIMIT);
        vertices.emplace_back(LEFT_LIMIT, starting_y_point - CORRIDOR_PART_SIZE, TOP_LIMIT);
        vertices.emplace_back(LEFT_LIMIT, starting_y_point - CORRIDOR_PART_SIZE, BOTTOM_LIMIT);
        vertices.emplace_back(LEFT_LIMIT, starting_y_point, BOTTOM_LIMIT);
        sides.emplace_back(vertices, Color(0.43, 0.45, 0.49), SideIndicator::LEFT_RIGHT);

        vertices.clear();
        vertices.emplace_back(RIGHT_LIMIT, starting_y_point, TOP_LIMIT);
        vertices.emplace_back(RIGHT_LIMIT, starting_y_point - CORRIDOR_PART_SIZE, TOP_LIMIT);
        vertices.emplace_back(RIGHT_LIMIT, starting_y_point - CORRIDOR_PART_SIZE, BOTTOM_LIMIT);
        vertices.emplace_back(RIGHT_LIMIT, starting_y_point, BOTTOM_LIMIT);
        sides.emplace_back(vertices, Color(0.43, 0.45, 0.49), SideIndicator::LEFT_RIGHT);

        return Wall(sides);
    }

    static std::vector<Wall> initial_corridor()
    {
        std::vector<Wall> walls;
        for (int i = 0; i < 64; i++)
        {
            walls.emplace_back(create_corridor_part(15 + i * -CORRIDOR_PART_SIZE));
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

    void ball_collision(Ball &ball) const
    {
        for (const auto &side : _sides)
        {
            side.ball_collision(ball);
        }
    }

private:
    std::vector<Side> _sides;
};