#include "Snake.h"
#include "States/Game.h"

#include <stdlib.h> /* abs */

Snake::Snake(std::weak_ptr<states::Game> game, sf::Vector2i head, Snake::Direction dir)
    : _pGame{game}
    , snake{head}
    , futureDirection{dir}
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

    if (auto sptr = _pGame.lock()) //promote weak_ptr to shared_ptr to use it
    {
        if (head.x<0 || head.y <0 || head.x>=100 || head.y>= 100) //TODO change the 100 to kGridSize
            return false; //we went out of bounds

        switch(sptr -> getBoardStateAt(head.x, head.y))
        {
            case states::Game::BoardState::kEmpty:
                break; //finish the movement

            case states::Game::BoardState::kWall:
            case states::Game::BoardState::kSnake:
                return false; //movement unsuccessful
                break;
            
            case states::Game::BoardState::kFood:
                length += 1;
                sptr -> foodEatenAt(head.x, head.y);
                break;

            default:
                break;
        } //switch
    } //if sptr
    
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