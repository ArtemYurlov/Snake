#pragma once

#include <SFML/Graphics.hpp>

class FPSCounter
{
  public:
    FPSCounter();

    void update();

    void draw(sf::RenderTarget &renderer);

  private:
    sf::Text _text;
    sf::Font _font;

    sf::Clock _delayTimer;
    sf::Clock _fpsTimer;

    float _fps = 0;

    int _frameCount = 0;
};
