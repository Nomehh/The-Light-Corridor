#pragma once

struct Color
{
    Color(float r, float g, float b)
        : _r{r}, _g{g}, _b{b}
    {
    }

    float _r = 0.;
    float _g = 0.;
    float _b = 0.;

    static Color generateRandomColor()
    {
        return Color{static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX};
    }
};