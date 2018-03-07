#include <iostream>
#include <memory>

#include "Game.h"
#include "States/Game.h"

#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
	std::shared_ptr<Game> game = std::make_shared<Game>();
	game -> pushState<states::Game>(game);
	game -> run();

	return 0;
}