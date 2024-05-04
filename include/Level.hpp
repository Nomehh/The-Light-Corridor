#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Wall.hpp"
#include "HCoordinates.hpp"

class Level
{
public:
    Level(std::string code, std::vector<Wall> obstacles, size_t depth_end_level)
        : _code{std::move(code)}, _obstacles{std::move(obstacles)}, _depth_end_level{depth_end_level}
    {
    }

    static Level generate_first_level();
    static Level generate_second_level(size_t depth_first_level);

    size_t depth_end_level() const
    {
        return _depth_end_level;
    }

    void load_level(std::vector<Wall> &obstacles)
    {
        for (auto obstacle : _obstacles)
        {
            obstacles.emplace_back(std::move(obstacle));
        }
    }

private:
    std::string _code;
    std::vector<Wall> _obstacles;
    size_t _depth_end_level;
};