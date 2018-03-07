#include "FPSCounter.h"

#include "../ResourceManager/ResourceHolder.h"

#include <iostream>

FPSCounter::FPSCounter()
{
    _text.move(10, 10);
    _text.setOutlineColor(sf::Color::Black);
    _text.setFillColor({255, 255, 255});
    _text.setOutlineThickness(1);
    _text.setFont(ResourceHolder::get().fonts.get("VT323"));
    _text.setCharacterSize(24);
}

void FPSCounter::update()
{
    _frameCount++;

    if (_delayTimer.getElapsedTime().asSeconds() > 0.5)
    {
        float time = _fpsTimer.restart().asSeconds();
        if (time < 0.01f)
            time = 0.01f;

        _fps = _frameCount / time;
        _frameCount = 0;
        _delayTimer.restart();
    }
}

void FPSCounter::draw(sf::RenderTarget &renderer)
{
    _text.setString("FPS: " + std::to_string((int)_fps));
    renderer.draw(_text);
}