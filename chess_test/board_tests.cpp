#include "pch.h"

#include "chess.h"

TEST_CASE("Construction") {

	board_t board;

	SECTION("Construction gives correctly sized board") {
		REQUIRE(board.squares().size() == 8 * 8);
	}

	SECTION("Construction gives an empty board") {
		for (const auto& square : board.squares()) {
			REQUIRE(square == square_t::Empty);
		}
	}

	SECTION("Construction sets the current player to white") {
		REQUIRE(board.current_player() == piece_t::WHITE);
	}
}

TEST_CASE("Clearing the board", "[clear_squares]") {

	board_t board;

	SECTION("Clearing sets the board to a constructed state") {

		board.initialise();
		REQUIRE(board != board_t());

		board.clear_squares();
		REQUIRE(board == board_t());
	}

	SECTION("Clearing does not affect the current player") {
		board.current_player() = piece_t::BLACK;
		board.clear_squares();
		REQUIRE(board.current_player() == piece_t::BLACK);
	}
}
