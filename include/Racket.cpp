#include "Racket.hpp"

Racket::Racket() : _racket{std::vector<HCoordinates>{
                               HCoordinates{0.2f, 13.f, 0.2f},
                               HCoordinates{-0.2f, 13.f, 0.2f},
                               HCoordinates{-0.2f, 13.f, -0.2f},
                               HCoordinates{0.2f, 13.f, -0.2f}},
                           Color{1, 1, 1}}
{
}
Racket::Racket(float x, float z) : _racket{std::vector<HCoordinates>{
                                               HCoordinates{x + 0.2f, 13.f, z + 0.2f},
                                               HCoordinates{-x + 0.2f, 13.f, z + 0.2f},
                                               HCoordinates{-x + 0.2f, 13.f, z - 0.2f},
                                               HCoordinates{x + 0.2f, 13.f, z - 0.2f}},
                                           Color{1, 1, 1}}

{
}

void Racket::draw() const
{
    _racket.drawRacket();
}

void Racket::updatePos(float x, float z)
{
    auto &coordinates = _racket.get_vertices();
    coordinates[0] = HCoordinates{x + RACKET_SIZE, DIST, z + RACKET_SIZE};
    coordinates[1] = HCoordinates{x - RACKET_SIZE, DIST, z + RACKET_SIZE};
    coordinates[2] = HCoordinates{x - RACKET_SIZE, DIST, z - RACKET_SIZE};
    coordinates[3] = HCoordinates{x + RACKET_SIZE, DIST, z - RACKET_SIZE};
}
