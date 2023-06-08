#include "game_t.h"

#include <iostream>

int main() {
	game_t game;
	game.initialise();
	std::cout << game.representation();
}
