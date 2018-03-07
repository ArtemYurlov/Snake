#pragma once

#include "State.h"

#include "../Snake/Snake.h"

#include <array>
#include <memory>

namespace states {



class Game : public State, public std::enable_shared_from_this<Game>
{
  public:
    Game(std::weak_ptr<::Game> stateMachine);

    void handleEvent(sf::Event e)           override;
    void handleInput()                      override;
    void update(sf::Time deltaTime)         override;
    void fixedUpdate(sf::Time deltaTime)    override;
    void render(sf::RenderTarget &renderer) override;

  private:
    enum boardState{kEmpty, kFood, kSnake, kWall};
    typedef std::array<std::array<boardState, 100>, 100> Grid;
    Grid _grid = {}; // 2-d snake grid initialized to 0s
    

    std::shared_ptr<Snake> snake;
    enum gameMode{kClassic, kRecursive};
    gameMode gMode = gameMode::kClassic; // TODO
};

}