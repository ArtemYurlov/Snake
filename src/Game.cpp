#include "Game.h"

#include <iostream>

#include "States/Game.h"

Game::Game()
    : _window({1280, 720}, "Game") //Init game window
{
    _window.setFramerateLimit(100);
}

void Game::run()
{
    //Initializations

    //Parameters
    constexpr unsigned TPS = 5;                                    //ticks per seconds
    const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS)); //seconds for a tick

    //Counters
    unsigned ticks = 0;
    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag = sf::Time::Zero;

    while (_window.isOpen() && !_states.empty())
    { //Main game loop
        auto &state = getCurrentState();

        auto time = timer.getElapsedTime(); //Get times
        auto elapsed = time - lastTime;     //Time since last update

        lastTime = time;
        lag += elapsed; //- how far we are behind on FTU

        //Real time update
        state.handleInput();
        state.update(elapsed);
        fpsCounter.update();

        //Fixed time update
        while (lag >= timePerUpdate) // -> we need next tick
        {
            ticks++;
            lag -= timePerUpdate;
            state.fixedUpdate(elapsed);
        }

        //Render
        _window.clear();
        state.render(_window);
        fpsCounter.draw(_window);
        _window.display();

        //Handle window events
        handleEvent();
        tryPop();
    }
}

void Game::tryPop()
{
    if (_shouldPop)
    {
        _states.pop_back();
        _shouldPop = false;
    }
}

void Game::handleEvent()
{
    sf::Event e;

    while (_window.pollEvent(e))
    {
        getCurrentState().handleEvent(e);
        switch (e.type)
        {
        case sf::Event::Closed:
            _window.close();
            break;

        default:
            break;
        }
    }
}

states::State &Game::getCurrentState()
{
    return *_states.back().get(); //return dereferenced pointer
}

void Game::popState()
{
    _shouldPop = true;
}

const sf::RenderWindow &Game::getWindow() const
{
    return _window;
}