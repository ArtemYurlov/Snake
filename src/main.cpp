#include <iostream>
#include <memory>

#include "Game.h"

#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
	std::shared_ptr<Game> game = std::make_shared<Game>();
	game -> run();

	return 0;
}