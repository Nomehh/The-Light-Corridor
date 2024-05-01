#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Wall.hpp"
#include "HCoordinates.hpp"

class Level
{
public:
    Level(std::string code, std::vector<Wall> obstacles)
        : _code{std::move(code)}, _obstacles{std::move(obstacles)}
    {
    }

    static Level generate_first_level();
    static Level generate_second_level();
    static Level generate_third_level();

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
};