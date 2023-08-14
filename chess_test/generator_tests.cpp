#include "pch.h"

#include "chess.h"

TEST_CASE("Test pawn move generation", "[generate_pawn_moves]") {

	board_t board;
	board.clear_squares();
	generator_t generator(board);

	SECTION("White pawn, first move") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "A2";
		board.square(from) = piece_t::WhitePawn;
		const auto moves = generator.generate_moves();
		REQUIRE(move_t::has_move(moves, { from, "A3" }));
		REQUIRE(move_t::has_move(moves, { from, "A4" }));
		REQUIRE(moves.size() == 2);
	}

	SECTION("White pawn, second move") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "A3";
		board.square(from) = piece_t::WhitePawn;
		const auto moves = generator.generate_moves();
		REQUIRE(move_t::has_move(moves, { from, "A4" }));
		REQUIRE(moves.size() == 1);
	}

	SECTION("Black pawn, first move") {
		board.current_player() = piece_t::BLACK;
		const std::string from = "A7";
		board.square(from) = piece_t::BlackPawn;
		const auto moves = generator.generate_moves();
		REQUIRE(move_t::has_move(moves, { from, "A6" }));
		REQUIRE(move_t::has_move(moves, { from, "A5" }));
		REQUIRE(moves.size() == 2);
	}

	SECTION("Black pawn, second move") {
		board.current_player() = piece_t::BLACK;
		const std::string from = "A6";
		board.square(from) = piece_t::BlackPawn;
		const auto moves = generator.generate_moves();
		REQUIRE(move_t::has_move(moves, { from, "A5" }));
		REQUIRE(moves.size() == 1);
	}
}

TEST_CASE("Test rook move generation", "[generate_rook_moves]") {

	board_t board;
	board.clear_squares();
	generator_t generator(board);

	SECTION("White rook, bottom left corner") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "A1";
		board.square(from) = piece_t::WhiteRook;
		const auto moves = generator.generate_moves();

		// Horizontal moves
		REQUIRE(move_t::has_move(moves, { from, "A2" }));
		REQUIRE(move_t::has_move(moves, { from, "A3" }));
		REQUIRE(move_t::has_move(moves, { from, "A4" }));
		REQUIRE(move_t::has_move(moves, { from, "A5" }));
		REQUIRE(move_t::has_move(moves, { from, "A6" }));
		REQUIRE(move_t::has_move(moves, { from, "A7" }));
		REQUIRE(move_t::has_move(moves, { from, "A8" }));

		// Vertical moves
		REQUIRE(move_t::has_move(moves, { from, "B1" }));
		REQUIRE(move_t::has_move(moves, { from, "C1" }));
		REQUIRE(move_t::has_move(moves, { from, "D1" }));
		REQUIRE(move_t::has_move(moves, { from, "E1" }));
		REQUIRE(move_t::has_move(moves, { from, "F1" }));
		REQUIRE(move_t::has_move(moves, { from, "G1" }));
		REQUIRE(move_t::has_move(moves, { from, "H1" }));

		REQUIRE(moves.size() == 14);
	}

	SECTION("White rook, centre") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "D4";
		board.square(from) = piece_t::WhiteRook;
		const auto moves = generator.generate_moves();

		// Horizontal moves
		REQUIRE(move_t::has_move(moves, { from, "A4" }));
		REQUIRE(move_t::has_move(moves, { from, "B4" }));
		REQUIRE(move_t::has_move(moves, { from, "C4" }));
		REQUIRE(move_t::has_move(moves, { from, "E4" }));
		REQUIRE(move_t::has_move(moves, { from, "F4" }));
		REQUIRE(move_t::has_move(moves, { from, "G4" }));
		REQUIRE(move_t::has_move(moves, { from, "H4" }));

		// Vertical moves
		REQUIRE(move_t::has_move(moves, { from, "D1" }));
		REQUIRE(move_t::has_move(moves, { from, "D2" }));
		REQUIRE(move_t::has_move(moves, { from, "D3" }));
		REQUIRE(move_t::has_move(moves, { from, "D5" }));
		REQUIRE(move_t::has_move(moves, { from, "D6" }));
		REQUIRE(move_t::has_move(moves, { from, "D7" }));
		REQUIRE(move_t::has_move(moves, { from, "D8" }));

		REQUIRE(moves.size() == 14);
	}
}

TEST_CASE("Test bishop move generation", "[generate_bishop_moves]") {

	board_t board;
	board.clear_squares();
	generator_t generator(board);

	SECTION("White bishop, bottom left corner") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "A1";
		board.square(from) = piece_t::WhiteBishop;
		const auto moves = generator.generate_moves();

		// Diagonal moves
		REQUIRE(move_t::has_move(moves, { from, "B2" }));
		REQUIRE(move_t::has_move(moves, { from, "C3" }));
		REQUIRE(move_t::has_move(moves, { from, "D4" }));
		REQUIRE(move_t::has_move(moves, { from, "E5" }));
		REQUIRE(move_t::has_move(moves, { from, "F6" }));
		REQUIRE(move_t::has_move(moves, { from, "G7" }));
		REQUIRE(move_t::has_move(moves, { from, "H8" }));

		REQUIRE(moves.size() == 7);
	}

	SECTION("White bishop, centre") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "D4";
		board.square(from) = piece_t::WhiteBishop;
		const auto moves = generator.generate_moves();

		// Right to left
		REQUIRE(move_t::has_move(moves, { from, "C5" }));
		REQUIRE(move_t::has_move(moves, { from, "C3" }));
		REQUIRE(move_t::has_move(moves, { from, "B6" }));
		REQUIRE(move_t::has_move(moves, { from, "B2" }));
		REQUIRE(move_t::has_move(moves, { from, "A7" }));
		REQUIRE(move_t::has_move(moves, { from, "A1" }));

		// Left to right
		REQUIRE(move_t::has_move(moves, { from, "E5" }));
		REQUIRE(move_t::has_move(moves, { from, "E3" }));
		REQUIRE(move_t::has_move(moves, { from, "F6" }));
		REQUIRE(move_t::has_move(moves, { from, "F2" }));
		REQUIRE(move_t::has_move(moves, { from, "G7" }));
		REQUIRE(move_t::has_move(moves, { from, "G1" }));
		REQUIRE(move_t::has_move(moves, { from, "H8" }));

		REQUIRE(moves.size() == 13);
	}
}

TEST_CASE("Test queen move generation", "[generate_queen_moves]") {

	board_t board;
	board.clear_squares();
	generator_t generator(board);

	SECTION("White queen, bottom left corner") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "A1";
		board.square(from) = piece_t::WhiteQueen;
		const auto moves = generator.generate_moves();

		// Bishop moves
		// Diagonal moves
		REQUIRE(move_t::has_move(moves, { from, "B2" }));
		REQUIRE(move_t::has_move(moves, { from, "C3" }));
		REQUIRE(move_t::has_move(moves, { from, "D4" }));
		REQUIRE(move_t::has_move(moves, { from, "E5" }));
		REQUIRE(move_t::has_move(moves, { from, "F6" }));
		REQUIRE(move_t::has_move(moves, { from, "G7" }));
		REQUIRE(move_t::has_move(moves, { from, "H8" }));

		// Rook moves
		// Horizontal moves
		REQUIRE(move_t::has_move(moves, { from, "A2" }));
		REQUIRE(move_t::has_move(moves, { from, "A3" }));
		REQUIRE(move_t::has_move(moves, { from, "A4" }));
		REQUIRE(move_t::has_move(moves, { from, "A5" }));
		REQUIRE(move_t::has_move(moves, { from, "A6" }));
		REQUIRE(move_t::has_move(moves, { from, "A7" }));
		REQUIRE(move_t::has_move(moves, { from, "A8" }));
		// Vertical moves
		REQUIRE(move_t::has_move(moves, { from, "B1" }));
		REQUIRE(move_t::has_move(moves, { from, "C1" }));
		REQUIRE(move_t::has_move(moves, { from, "D1" }));
		REQUIRE(move_t::has_move(moves, { from, "E1" }));
		REQUIRE(move_t::has_move(moves, { from, "F1" }));
		REQUIRE(move_t::has_move(moves, { from, "G1" }));
		REQUIRE(move_t::has_move(moves, { from, "H1" }));

		REQUIRE(moves.size() == 21);
	}

	SECTION("White queen, centre") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "D4";
		board.square(from) = piece_t::WhiteQueen;
		const auto moves = generator.generate_moves();

		// Bishop moves
		// Right to left
		REQUIRE(move_t::has_move(moves, { from, "C5" }));
		REQUIRE(move_t::has_move(moves, { from, "C3" }));
		REQUIRE(move_t::has_move(moves, { from, "B6" }));
		REQUIRE(move_t::has_move(moves, { from, "B2" }));
		REQUIRE(move_t::has_move(moves, { from, "A7" }));
		REQUIRE(move_t::has_move(moves, { from, "A1" }));
		// Left to right
		REQUIRE(move_t::has_move(moves, { from, "E5" }));
		REQUIRE(move_t::has_move(moves, { from, "E3" }));
		REQUIRE(move_t::has_move(moves, { from, "F6" }));
		REQUIRE(move_t::has_move(moves, { from, "F2" }));
		REQUIRE(move_t::has_move(moves, { from, "G7" }));
		REQUIRE(move_t::has_move(moves, { from, "G1" }));
		REQUIRE(move_t::has_move(moves, { from, "H8" }));

		// Rook moves
		// Horizontal moves
		REQUIRE(move_t::has_move(moves, { from, "A4" }));
		REQUIRE(move_t::has_move(moves, { from, "B4" }));
		REQUIRE(move_t::has_move(moves, { from, "C4" }));
		REQUIRE(move_t::has_move(moves, { from, "E4" }));
		REQUIRE(move_t::has_move(moves, { from, "F4" }));
		REQUIRE(move_t::has_move(moves, { from, "G4" }));
		REQUIRE(move_t::has_move(moves, { from, "H4" }));
		// Vertical moves
		REQUIRE(move_t::has_move(moves, { from, "D1" }));
		REQUIRE(move_t::has_move(moves, { from, "D2" }));
		REQUIRE(move_t::has_move(moves, { from, "D3" }));
		REQUIRE(move_t::has_move(moves, { from, "D5" }));
		REQUIRE(move_t::has_move(moves, { from, "D6" }));
		REQUIRE(move_t::has_move(moves, { from, "D7" }));
		REQUIRE(move_t::has_move(moves, { from, "D8" }));

		REQUIRE(moves.size() == 27);
	}
}
