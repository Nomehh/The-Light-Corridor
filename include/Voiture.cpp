#include "Voiture.hpp"
#include <iostream>

Voiture::Voiture(int speed)
{
    _speed = speed;
}

void Voiture::get_speed()
{
    std::cout << "Speed: " << _speed << std::endl;
}