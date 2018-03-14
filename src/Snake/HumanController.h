#pragma once

#include "Controller.h"

class HumanController : public Controller
{
    /*  Snake controlled by keyboard input,
        Action space is just the direction to turn to at every move of the snake*/

    public:
    HumanController(std::weak_ptr<states::Game> game, std::shared_ptr<Snake> snake);

    void update()                   override;
    void processEvent(sf::Event e)  override;
    Snake::Direction getAction()    override; //returns the direction for the snake to turn

    private:
    std::weak_ptr<states::Game> _pGame;
    std::shared_ptr<Snake> _cSnake;

    Snake::Direction curTurningDirection = Snake::Direction::kWest; //we will store the direction to turn to on next move
};