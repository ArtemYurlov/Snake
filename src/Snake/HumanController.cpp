#include "HumanController.h"

#include "../States/Game.h"

HumanController::HumanController(std::weak_ptr<states::Game> game, std::shared_ptr<Snake> snake)
    :   Controller(game, snake)
{

}

Snake::Direction HumanController::getAction()
{
    return curTurningDirection;
}

void HumanController::processEvent(sf::Event e) 
{
    switch(e.type)
    {
        case sf::Event::KeyPressed:
            switch  (e.key.code){
                case sf::Keyboard::W:
                    curTurningDirection = Snake::Direction::kNorth;
                    break;
                
                case sf::Keyboard::S:
                    curTurningDirection = Snake::Direction::kSouth;
                    break;

                case sf::Keyboard::A:
                    curTurningDirection = Snake::Direction::kWest;
                    break;

                case sf::Keyboard::D:
                    curTurningDirection = Snake::Direction::kEast;
                    break;
                default:
                    break;
            }
            break;
            default:
                break;
    }
}

void HumanController::update() 
{
    //nothing to do
}