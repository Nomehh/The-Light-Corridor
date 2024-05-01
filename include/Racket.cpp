#include "Racket.hpp"

Racket::Racket() : _racket{std::vector<HCoordinates>{
                               HCoordinates{0.2f, 13.f, 0.2f},
                               HCoordinates{-0.2f, 13.f, 0.2f},
                               HCoordinates{-0.2f, 13.f, -0.2f},
                               HCoordinates{0.2f, 13.f, -0.2f}},
                           Color{1, 1, 1},
                           SideIndicator::FRONT_BACK}
{
}
Racket::Racket(float x, float z) : _racket{std::vector<HCoordinates>{
                                               HCoordinates{x + 0.2f, 13.f, z + 0.2f},
                                               HCoordinates{-x + 0.2f, 13.f, z + 0.2f},
                                               HCoordinates{-x + 0.2f, 13.f, z - 0.2f},
                                               HCoordinates{x + 0.2f, 13.f, z - 0.2f}},
                                           Color{1, 1, 1},
                                           SideIndicator::FRONT_BACK}

{
}

void Racket::draw() const
{
    _racket.drawRacket();
}

void Racket::updatePos(float x, float z)
{
    _center = HCoordinates(x, 13, z);
    auto &coordinates = _racket.get_vertices();
    coordinates[0] = HCoordinates{x + RACKET_SIZE, DIST, z + RACKET_SIZE};
    coordinates[1] = HCoordinates{x - RACKET_SIZE, DIST, z + RACKET_SIZE};
    coordinates[2] = HCoordinates{x - RACKET_SIZE, DIST, z - RACKET_SIZE};
    coordinates[3] = HCoordinates{x + RACKET_SIZE, DIST, z - RACKET_SIZE};
}

HCoordinates Racket::projectOntoPlane(const HCoordinates &center, const HCoordinates &planeNormal) const
{
    auto dotProduct = center.dot(planeNormal);
    HCoordinates projection = center - (planeNormal * dotProduct);

    return projection;
}

void Racket::check_collision(Ball &ball) const
{
    HCoordinates v1 = _racket.get_vertices()[1] - _racket.get_vertices()[0];
    HCoordinates v2 = _racket.get_vertices()[3] - _racket.get_vertices()[0];
    HCoordinates normal = v1.cross(v2).normalized();

    auto d = normal.dot(_racket.get_vertices()[0]);
    auto distance = -normal.dot(ball.get_coordinates()) + d;

    auto ballOnPlane = projectOntoPlane(ball.get_coordinates(), normal);

    if (std::abs(distance) <= BALL_SIZE && front_back_check(ballOnPlane))
    {
        auto u = ballOnPlane - _center;
        auto dotProduct = ;
        HCoordinates reflectedVelocity = u - (normal * dotProduct * 2.0f);

        ball.set_vectors(u.cross(normal));
        ball.updatePos(ball.get_x(), ball.get_y(), false);
    }
}
