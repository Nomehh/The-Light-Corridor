#include "Level.hpp"

Level Level::generate_first_level()
{
    std::vector<Wall> obstacles;
    std::string code = "level1";

    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -15, TOP_LIMIT), CORRIDOR_WIDTH / 3, CORRIDOR_HEIGHT, 3, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(RIGHT_LIMIT - CORRIDOR_WIDTH / 3, -25, TOP_LIMIT), CORRIDOR_WIDTH / 3, CORRIDOR_HEIGHT, 3, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(RIGHT_LIMIT - CORRIDOR_WIDTH / 3, -35, TOP_LIMIT), CORRIDOR_WIDTH / 3, CORRIDOR_HEIGHT, 3, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -45, TOP_LIMIT), CORRIDOR_WIDTH / 3, CORRIDOR_HEIGHT, 3, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(RIGHT_LIMIT - CORRIDOR_WIDTH / 3, -45, TOP_LIMIT), CORRIDOR_WIDTH / 3, CORRIDOR_HEIGHT, 3, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -55, -0.7), CORRIDOR_WIDTH, 0.3, 2, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -59, -0.4), CORRIDOR_WIDTH, 0.6, 2, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -63, 0), CORRIDOR_WIDTH, 1, 3, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -73, TOP_LIMIT), CORRIDOR_WIDTH, 1.2, 3, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -90, TOP_LIMIT), CORRIDOR_WIDTH / 3 + 0.3f, CORRIDOR_HEIGHT, 15, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(RIGHT_LIMIT - CORRIDOR_WIDTH / 3, -90, TOP_LIMIT), CORRIDOR_WIDTH / 3 + 0.3f, CORRIDOR_HEIGHT, 15, Color::generateRandomColor()));

    return Level(code, obstacles);
}

Level Level::generate_second_level()
{
    std::vector<Wall> obstacles;
    std::string code = "level2";

    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -15, TOP_LIMIT), CORRIDOR_WIDTH / 3, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(RIGHT_LIMIT - CORRIDOR_WIDTH / 3, -20, TOP_LIMIT), CORRIDOR_WIDTH / 3, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(RIGHT_LIMIT - CORRIDOR_WIDTH / 3, -25, TOP_LIMIT), CORRIDOR_WIDTH / 3, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -30, TOP_LIMIT), CORRIDOR_WIDTH, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -35, TOP_LIMIT), CORRIDOR_WIDTH, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(RIGHT_LIMIT - CORRIDOR_WIDTH / 3, -40, TOP_LIMIT), CORRIDOR_WIDTH / 3, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, -43, TOP_LIMIT), CORRIDOR_WIDTH, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(RIGHT_LIMIT - CORRIDOR_WIDTH / 3, -50, TOP_LIMIT), CORRIDOR_WIDTH / 3, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(RIGHT_LIMIT - CORRIDOR_WIDTH / 3, -58, TOP_LIMIT), CORRIDOR_WIDTH / 3, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));
    obstacles.emplace_back(Wall::create_obstacle(HCoordinates(LEFT_LIMIT, 10, TOP_LIMIT), CORRIDOR_WIDTH, 3, CORRIDOR_HEIGHT, Color::generateRandomColor()));

    return Level(code, obstacles);
}