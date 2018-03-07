#include "Snake.h"

#include <stdlib.h> /* abs */

Snake::Snake(sf::Vector2i head, Snake::Direction dir)
    : snake{head},
    futureDirection{dir}
{}

bool Snake::move(){

    sf::Vector2i head = sf::Vector2i{snake.front()}; //new head of the snake (if the move is successful)
    switch(futureDirection)
    {
        case kNorth:
            head.y -= 1;
            break;
        case kEast:
            head.x += 1;
            break;
        case kSouth:
            head.y += 1;
            break;
        case kWest:
            head.x -= 1;
            break;
    }

    //execute movmement
    currentDirection = futureDirection;

    snake.emplace_front(head);
    while(snake.size() > length)
    {
        snake.pop_back();
    }

    return true;

}

bool Snake::turn(Snake::Direction dir){
    if (abs(currentDirection - dir) == 2) // if we try and turn 180
        return false;

    futureDirection = dir;
    return true;
}