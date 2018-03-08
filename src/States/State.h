#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Misc/NonCopyable.h"
#include "../Misc/NonMovable.h"

class Game;

namespace states{

class State
{
  public:
    State(std::weak_ptr<::Game> stateMachine)
    : _pGame{stateMachine}
    {
    }

    virtual void init() {}

    virtual void handleEvent(sf::Event e)           = 0;
    virtual void handleInput()                      = 0;
    virtual void update(sf::Time deltaTime)         = 0; //every frame update
    virtual void fixedUpdate(sf::Time deltaTime)    = 0; //update every tick
    virtual void render(sf::RenderTarget &renderer) = 0; //draw

    virtual void pause(){}
    virtual void resume(){}

  protected:
    std::weak_ptr<::Game> _pGame;
};

}