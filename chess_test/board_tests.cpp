#include "pch.h"

#include "chess.h"

// XY positions

TEST_CASE("XY position to vector index", "[xy_2_index]") {

	SECTION("Top/left corner of board") {
		constexpr auto index = board_t::xy_2_index(0, 0);
		REQUIRE(index == 0);
	}

	SECTION("Top/right corner of board") {
		constexpr auto index = board_t::xy_2_index(7, 0);
		REQUIRE(index == 7);
	}

	SECTION("Bottom/left corner of board") {
		constexpr auto index = board_t::xy_2_index(0, 7);
		REQUIRE(index == 7 * 8);
	}

	SECTION("Bottom/right corner of board") {
		constexpr auto index = board_t::xy_2_index(7, 7);
		REQUIRE(index == 8 * 8 - 1);
	}
}

TEST_CASE("Vector index to XY position", "[index_2_xy]") {

	SECTION("Top/left corner of board") {
		const auto [x, y] = board_t::index_2_xy(0);
		REQUIRE(x == 0);
		REQUIRE(y == 0);
	}

	SECTION("Top/right corner of board") {
		const auto [x, y] = board_t::index_2_xy(7);
		REQUIRE(x == 7);
		REQUIRE(y == 0);
	}

	SECTION("Bottom/left corner of board") {
		const auto [x, y] = board_t::index_2_xy(7 * 8);
		REQUIRE(x == 0);
		REQUIRE(y == 7);
	}

	SECTION("Bottom/right corner of board") {
		const auto [x, y] = board_t::index_2_xy(8 * 8 - 1);
		REQUIRE(x == 7);
		REQUIRE(y == 7);
	}
}

// Numeric positions (reversed row)

TEST_CASE("Numeric position to vector index", "[numeric_2_index]") {

	SECTION("Bottom/left corner of board") {
		const auto index = board_t::numeric_2_index(0, 0);
		REQUIRE(index == board_t::xy_2_index(0, 7));
	}

	SECTION("Bottom/right corner of board") {
		const auto index = board_t::numeric_2_index(7, 0);
		REQUIRE(index == board_t::xy_2_index(7, 7));
	}

	SECTION("Top/left corner of board") {
		const auto index = board_t::numeric_2_index(0, 7);
		REQUIRE(index == board_t::xy_2_index(0, 0));
	}

	SECTION("Top/right corner of board") {
		const auto index = board_t::numeric_2_index(7, 7);
		REQUIRE(index == board_t::xy_2_index(7, 0));
	}
}

TEST_CASE("Vector index to Numeric position", "[index_2_numeric]") {

	SECTION("Top/left corner of board") {
		const auto [column, row] = board_t::index_2_numeric(0);
		REQUIRE(column == 0);
		REQUIRE(row == 7);
	}

	SECTION("Top/right corner of board") {
		const auto [column, row] = board_t::index_2_numeric(7);
		REQUIRE(column == 7);
		REQUIRE(row == 7);
	}

	SECTION("Bottom/left corner of board") {
		const auto [column, row] = board_t::index_2_numeric(7 * 8);
		REQUIRE(column == 0);
		REQUIRE(row == 0);
	}

	SECTION("Bottom/right corner of board") {
		const auto [column, row] = board_t::index_2_numeric(8 * 8 - 1);
		REQUIRE(column == 7);
		REQUIRE(row == 0);
	}
}

// Algebraic positions ('char' versions of numeric)

TEST_CASE("Algebraic position to vector index", "[algebraic_2_index]") {

	SECTION("Bottom/left corner of board") {
		const auto index = board_t::algebraic_2_index('A', '1');
		REQUIRE(index == board_t::numeric_2_index(0, 0));
	}

	SECTION("Bottom/right corner of board") {
		const auto index = board_t::algebraic_2_index('H', '1');
		REQUIRE(index == 7 * 8 + 7);
	}

	SECTION("Top/left corner of board") {
		const auto index = board_t::numeric_2_index(0, 7);
		REQUIRE(index == board_t::xy_2_index(0, 0));
	}

	SECTION("Top/right corner of board") {
		const auto index = board_t::numeric_2_index(7, 7);
		REQUIRE(index == board_t::xy_2_index(7, 0));
	}
}

TEST_CASE("Vector index to algebraic position", "[index_2_algebraic]") {

	SECTION("Top/left corner of board") {
		const auto [column, row] = board_t::index_2_numeric(0);
		REQUIRE(column == 0);
		REQUIRE(row == 7);
	}

	SECTION("Top/right corner of board") {
		const auto [column, row] = board_t::index_2_numeric(7);
		REQUIRE(column == 7);
		REQUIRE(row == 7);
	}

	SECTION("Bottom/left corner of board") {
		const auto [column, row] = board_t::index_2_numeric(7 * 8);
		REQUIRE(column == 0);
		REQUIRE(row == 0);
	}

	SECTION("Bottom/right corner of board") {
		const auto [column, row] = board_t::index_2_numeric(8 * 8 - 1);
		REQUIRE(column == 7);
		REQUIRE(row == 0);
	}
}

TEST_CASE("Test pawn move generation", "[generate_pawn_moves]") {

	board_t board;
	board.clear_squares();

	//std::cout << board_t::representation(moves);

	SECTION("White pawn, first move") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "A2";
		board.square(board_t::algebraic_2_index(from)) = piece_t::WhitePawn;
		const auto moves = board.generate_moves();
		REQUIRE(moves.size() == 2);
		REQUIRE(board_t::has_move(moves, { from, "A3" }));
		REQUIRE(board_t::has_move(moves, { from, "A4" }));
	}

	SECTION("White pawn, second move") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "A3";
		board.square(board_t::algebraic_2_index(from)) = piece_t::WhitePawn;
		const auto moves = board.generate_moves();
		REQUIRE(moves.size() == 1);
		REQUIRE(board_t::has_move(moves, { from, "A4" }));
	}

	SECTION("Black pawn, first move") {
		board.current_player() = piece_t::BLACK;
		const std::string from = "A7";
		board.square(board_t::algebraic_2_index(from)) = piece_t::BlackPawn;
		const auto moves = board.generate_moves();
		REQUIRE(moves.size() == 2);
	}

	SECTION("Black pawn, second move") {
		board.current_player() = piece_t::BLACK;
		const std::string from = "A6";
		board.square(board_t::algebraic_2_index(from)) = piece_t::BlackPawn;
		const auto moves = board.generate_moves();
		REQUIRE(moves.size() == 1);
	}
}
