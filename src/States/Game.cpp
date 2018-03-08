#include "Game.h"

#include "../Game.h"

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
                //TODO move all these to snake controller
                case sf::Keyboard::W:
                    snake->turn(Snake::Direction::kNorth);
                    break;
                
                case sf::Keyboard::S:
                    snake->turn(Snake::Direction::kSouth);
                    break;

                case sf::Keyboard::A:
                    snake->turn(Snake::Direction::kWest);
                    break;

                case sf::Keyboard::D:
                    snake->turn(Snake::Direction::kEast);
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
}

void Game::handleInput()
{

}

void Game::update(sf::Time deltaTime)
{
    // Full grid update TODO make more efficient
    _grid = {};
    for (int i = 0; i < 100; ++i)
    {
        _grid[i][0] = BoardState::kWall;
        _grid[i][99] = BoardState::kWall;
        _grid[0][i] = BoardState::kWall;
        _grid[99][i] = BoardState::kWall;
    }
        
    for (auto v : snake->snake){

        if (v.x >= 100 || v.x < 0 || v.y < 0 || v.y >= 100)
            continue;
        _grid[v.x][v.y] = BoardState::kSnake;
    }
}

void Game::fixedUpdate(sf::Time deltaTime)
{
    // if (gMode == kClassic)
        snake->move();

    //std::cout << snake->snake.front().x <<" "<< snake->snake.front().y << " "; 
}

void Game::render(sf::RenderTarget &renderer)
{
    sf::RectangleShape box = sf::RectangleShape({5,5});
    box.setFillColor({50,50,50});
    for (int row = 0; row < 100; row++)
        for (int col = 0; col < 100; col++)
        {
            switch(_grid[row][col])
            {
                case kEmpty:
                    box.setFillColor({50,50,50});
                    break;
                case kWall:
                    box.setFillColor({150,150,150});
                    break;
                case kSnake:
                    box.setFillColor({255,255,255});
                    break;
                case kFood:
                    box.setFillColor({255,80,60});
                    break;
                
            }
            box.setPosition(50+row*6, 50+col*6);
            renderer.draw(box);
        }
}


//------------Own stuff-----------
Game::BoardState Game::getBoardStateAt(unsigned int x, unsigned int y)
{
    if (x >= 100 || y >= 100)
        throw "_grid out of bounds!";

    return _grid[x][y];
}


} // namespace states