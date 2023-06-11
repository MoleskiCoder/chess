#include "chess.h"

#include <iostream>

int main() {
	game_t game;
	const auto& board = game.board();

	game.initialise();

	std::cout << game.representation() << std::endl;

	std::cout << board.representation(board.current_player()) << " to play" << std::endl;

	const auto moves = board.generate_moves();
	std::cout << "** Available moves" << std::endl;
	std::cout << game.board().representation(moves);
}
