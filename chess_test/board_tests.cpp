#include "pch.h"

#include <algorithm>

#include "chess.h"

TEST_CASE("Construction") {

	board_t board;

	SECTION("Construction gives correctly sized board") {
		REQUIRE(board.squares().size() == 8 * 8);
	}

	SECTION("Construction gives an empty board") {
		REQUIRE(std::all_of(board.squares().cbegin(), board.squares().cend(), [](const square_t& square) { return square == square_t::Empty; }));
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

TEST_CASE("Executing move", "[execute]") {

	board_t board;
	board.initialise();

	SECTION("Moving a piece corrects the board state") {

		const std::string from = "E2";
		const std::string to = "E4";

		board.execute({ from, to });

		REQUIRE(board.square(from) == square_t::Empty);
		REQUIRE(board.square(to).contents().has_value());
		REQUIRE(board.square(to) == piece_t::WhitePawn);
	}
}
