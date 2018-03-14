#pragma once

#include <memory>
#include "Snake.h"

namespace states{
    class Game;
}

class Controller
{
    /*  Snake controller,
        Action space is just the direction to turn to at every move of the snake*/

    public:
    Controller(std::weak_ptr<states::Game> game, std::shared_ptr<Snake> snake)
    :   _pGame{game}
    ,   _cSnake{snake}
    {}

    virtual ~Controller() = default;

    virtual void update() = 0;
    virtual void processEvent(sf::Event e) = 0;

    virtual Snake::Direction getAction() = 0; //returns the direction for the snake to turn

    protected:
    std::weak_ptr<states::Game> _pGame;
    std::shared_ptr<Snake> _cSnake;

    
};