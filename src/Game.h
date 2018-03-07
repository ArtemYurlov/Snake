#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Misc/FPSCounter.h"
#include "States/State.h"

class Game : public std::enable_shared_from_this<::Game>
{
  public:
    Game();

    void run();

    template <typename T, typename... Args>
    void pushState(Args &&... args);

    void popState();

    const sf::RenderWindow &getWindow() const;

  private:
    void handleEvent();
    void tryPop();

    states::State &getCurrentState();

    sf::RenderWindow _window;
    std::vector<std::unique_ptr<states::State>> _states;

    FPSCounter fpsCounter;

    bool _shouldPop = false;
};

template <typename T, typename... Args>
void Game::pushState(Args &&... args)
{
    _states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}