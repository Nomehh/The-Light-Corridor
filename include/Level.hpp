#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Wall.hpp"

class Level
{
public:
    Level(std::string code, std::vector<Wall> obstacles)
        : _code{std::move(code)}, _obstacles{obstacles}
    {
    }

    static Level generate_first_level();
    static Level generate_second_level();
    static Level generate_third_level();
    static Level generate_fourth_level();
    static Level generate_fifth_level();

private:
    std::string _code;
    std::vector<Wall> _obstacles;
};