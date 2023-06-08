#include "game_t.h"

#include <iostream>

int main() {
	game_t game;
	game.initialise();
	std::cout << game.representation();

	const auto moves = game.board().generate_moves();
	std::cout << "** Available moves" << std::endl;
	std::cout << game.board().representation(moves);
}
