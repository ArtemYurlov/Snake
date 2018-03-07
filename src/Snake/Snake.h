#pragma once

#include <SFML/Graphics.hpp>
#include <list>

class Snake{
    public:
    enum Direction{kNorth, kEast, kSouth, kWest};
    Snake(sf::Vector2i head = sf::Vector2i{5,5}, Snake::Direction dir = Snake::Direction::kEast);
    
    unsigned int length = 10;
    std::list<sf::Vector2i> snake;    
    Direction currentDirection = Direction::kWest; //the direction the snake is currently moving in
    Direction futureDirection = Direction::kWest;   // the direction the snake will be moving at next tick

    bool move(); // true if success, TODO: false if collision

    bool turn(Snake::Direction dir); // true if success, false if imposible turn
};