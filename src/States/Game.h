#pragma once

#include "State.h"

#include "../Snake/Snake.h"

#include <array>
#include <memory>
#include <set>

#include "../Misc/RNG.h" //for randomFood

namespace states {



class Game : public State, public std::enable_shared_from_this<Game>
{
  public:
    Game(std::weak_ptr<::Game> stateMachine);
    //Methods called by the StateMachine (parent)
    void init()                             override;

    void handleEvent(sf::Event e)           override;
    void handleInput()                      override;
    void update(sf::Time deltaTime)         override;
    void fixedUpdate(sf::Time deltaTime)    override;
    void render(sf::RenderTarget &renderer) override;

    //Own stuff
    void buildGrid();

    enum BoardState{kEmpty, kFood, kSnake, kWall};
    BoardState getBoardStateAt(unsigned int x, unsigned int y);

    bool spawnFoodAtRandom(); //returns true if food placed successfully, false if no cells left for food
    bool spawnFoodAt(unsigned int x, unsigned int y); //returns true if food is placed, false if food already exists at the loc

    void foodEatenAt(unsigned int x, unsigned int y);

  private:
    static const unsigned int kGridSize = 50;
    
    typedef std::array<std::array<BoardState, kGridSize>, kGridSize> Grid;
    Grid _grid = {}; // 2-d snake grid initialized to 0s   

    std::shared_ptr<Snake> snake;
    std::vector<sf::Vector2i> food;

    std::unique_ptr<Random<>> rng;

    enum gameMode{kClassic, kRecursive};
    gameMode gMode = gameMode::kClassic; // TODO
};

}