#include "Game.h"

#include "../Game.h"
//#include "../Misc/RNG.h" //for random food

#include "../Snake/HumanController.h" //TODO move to factory

#include <memory>
#include <iostream>

namespace states{

Game::Game(std::weak_ptr<::Game> StateMachine)
    : State{StateMachine}
{

}

void Game::init()
{
    snake = std::make_shared<Snake>(shared_from_this());
    controller = std::make_shared<HumanController>(shared_from_this(), snake); //TODO move to factory
        rng = std::make_unique<Random<>>(); //for spawnFoodAtRandom
    spawnFoodAtRandom();
}

void Game::handleEvent(sf::Event e)
{
    switch(e.type)
    {
        case sf::Event::KeyPressed:
            switch  (e.key.code){
                case sf::Keyboard::Escape:
                    if (auto sptr = _pGame.lock())
                        sptr->popState();
                    break;
                
                default:
                    break;
                
                // case sf::Keyboard::P:
                //     if (gMode == gameMode::kClassic)
                //         gMode = kRecursive;
                //     else
                //         gMode = kClassic;

            }
            break;
            default:
                break;
    }

    controller->processEvent(e);
}

void Game::handleInput()
{

}

void Game::update(sf::Time deltaTime)
{
    buildGrid();
    controller->update();
}

void Game::buildGrid()
{
    // Full grid update TODO make more efficient
    _grid = {};
    for (unsigned int i = 0; i < kGridSize; ++i) //add walls around the perimmiter
    {
        _grid[i][0]             = BoardState::kWall;
        _grid[i][kGridSize - 1] = BoardState::kWall;
        _grid[0][i]             = BoardState::kWall;
        _grid[kGridSize - 1][i] = BoardState::kWall;
    }

    for (auto v : food){ // add the food to the _grid
        _grid[v.x][v.y] = BoardState::kFood;
    }
        
    for (auto v : snake->snake){ // add the snake to the _grid

        if (v.x >= kGridSize || v.x < 0 || v.y < 0 || v.y >= kGridSize)
            continue;

        _grid[v.x][v.y] = BoardState::kSnake;
    }
}

void Game::fixedUpdate(sf::Time deltaTime)
{
    // if (gMode == kClassic)
        snake->turn(controller->getAction());
        snake->move();

    //std::cout << snake->snake.front().x <<" "<< snake->snake.front().y << " "; 
}

void Game::render(sf::RenderTarget &renderer)
{
    const int boxSize = 10;
    sf::RectangleShape box = sf::RectangleShape({boxSize, boxSize});
    box.setFillColor({50,50,50});
    for (unsigned int row = 0; row < kGridSize; row++)
        for (unsigned int col = 0; col < kGridSize; col++)
        {
            switch(_grid[row][col])
            {
                case kEmpty:
                    box.setFillColor({50,50,50});
                    break;
                case kWall:
                    box.setFillColor({150,140,130});
                    break;
                case kSnake:
                    box.setFillColor({255,255,255});
                    break;
                case kFood:
                    box.setFillColor({255,80,60});
                    break;
                
            }
            box.setPosition(50+row*(boxSize + 1), 50+col*(boxSize + 1));
            renderer.draw(box);
        }
}


//------------Own stuff-----------
Game::BoardState Game::getBoardStateAt(unsigned int x, unsigned int y)
{
    if (x >= kGridSize || y >= kGridSize)
        throw "_grid out of bounds!";

    return _grid[x][y];
}

bool Game::spawnFoodAt(unsigned int x, unsigned int y)
{
    if (x >= kGridSize || y >= kGridSize)
        throw "_grid out of bounds!";
    
    for (auto f : food)
        if (f.x == x && f.y == y)
            return false; // food already exists

    food.emplace_back(sf::Vector2i(x,y));
    return true;
}

bool Game::spawnFoodAtRandom()
{
    buildGrid(); //build the grid since we will be using it

    int numOfFreeCells = 0; //count all the cells food can appear in
    for (int i = 0; i< kGridSize * kGridSize; ++i) //multi-dimensional arrays are stored back-to-back so this is fine
        if (_grid[0][i] == BoardState::kEmpty)
            numOfFreeCells++;

    if (numOfFreeCells == 0)
        return false; //no cells left to place the food on

    int n = rng->getIntInRange(0, numOfFreeCells); // place food at n_th free cell

    int placeFoodAt = 0; // the free coordinate
    for (; placeFoodAt < kGridSize * kGridSize; ++placeFoodAt) //super-index iteration
        if (_grid[0][placeFoodAt] == BoardState::kEmpty) // then this cell is avaliable for food
            if (n==0)   //we want to place out food here
                break;
            else        //mo not this cell
                n--;       
    
    std::cout << "food placed at: " << placeFoodAt/kGridSize << " " //debug
        << placeFoodAt%kGridSize << " num of free: " << numOfFreeCells << " total foods: " << food.size() << " ";

    auto success = spawnFoodAt(placeFoodAt / kGridSize, placeFoodAt % kGridSize); //place the food at the free space we found
    buildGrid(); // update the grid with the new food
    return success;
}

void Game::foodEatenAt(unsigned int x, unsigned int y)
{
    for (auto it = food.begin(); it != food.end(); )
    {
        if ((*it).x == x && (*it).y == y)
            food.erase(it);
        else
            it++;
    }

    spawnFoodAtRandom();
}


} // namespace states