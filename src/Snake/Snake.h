#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

namespace states{
    class Game;
}

class Snake{
    public:
    enum Direction{kNorth, kEast, kSouth, kWest};
    Snake(std::weak_ptr<states::Game> game, sf::Vector2i head = sf::Vector2i{2,2}, Snake::Direction dir = Snake::Direction::kEast);
    
    std::list<sf::Vector2i> snake; // connected list of POSITIONS of snake (head and body)

    bool move(); // true if success, false if collision

    bool turn(Snake::Direction dir); // true if success, false if imposible turn

    private:
    //parent
    std::weak_ptr<states::Game> _pGame;

    //other vars
    unsigned int length = 3;

    Direction currentDirection = Direction::kWest; //the direction the snake is currently moving in
    Direction futureDirection = Direction::kWest;   // the direction the snake will be moving at next tick


};