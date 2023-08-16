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
		auto moves = generator.generate_moves();
		REQUIRE(move_t::remove_move(moves, { from, "A3" }));
		REQUIRE(move_t::remove_move(moves, { from, "A4" }));
		REQUIRE(moves.empty());
	}

	SECTION("White pawn, second move") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "A3";
		board.square(from) = piece_t::WhitePawn;
		auto moves = generator.generate_moves();
		REQUIRE(move_t::remove_move(moves, { from, "A4" }));
		REQUIRE(moves.empty());
	}

	SECTION("Black pawn, first move") {
		board.current_player() = piece_t::BLACK;
		const std::string from = "A7";
		board.square(from) = piece_t::BlackPawn;
		auto moves = generator.generate_moves();
		REQUIRE(move_t::remove_move(moves, { from, "A6" }));
		REQUIRE(move_t::remove_move(moves, { from, "A5" }));
		REQUIRE(moves.empty());
	}

	SECTION("Black pawn, second move") {
		board.current_player() = piece_t::BLACK;
		const std::string from = "A6";
		board.square(from) = piece_t::BlackPawn;
		auto moves = generator.generate_moves();
		REQUIRE(move_t::remove_move(moves, { from, "A5" }));
		REQUIRE(moves.empty());
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
		auto moves = generator.generate_moves();

		// Horizontal moves
		REQUIRE(move_t::remove_move(moves, { from, "A2" }));
		REQUIRE(move_t::remove_move(moves, { from, "A3" }));
		REQUIRE(move_t::remove_move(moves, { from, "A4" }));
		REQUIRE(move_t::remove_move(moves, { from, "A5" }));
		REQUIRE(move_t::remove_move(moves, { from, "A6" }));
		REQUIRE(move_t::remove_move(moves, { from, "A7" }));
		REQUIRE(move_t::remove_move(moves, { from, "A8" }));

		// Vertical moves
		REQUIRE(move_t::remove_move(moves, { from, "B1" }));
		REQUIRE(move_t::remove_move(moves, { from, "C1" }));
		REQUIRE(move_t::remove_move(moves, { from, "D1" }));
		REQUIRE(move_t::remove_move(moves, { from, "E1" }));
		REQUIRE(move_t::remove_move(moves, { from, "F1" }));
		REQUIRE(move_t::remove_move(moves, { from, "G1" }));
		REQUIRE(move_t::remove_move(moves, { from, "H1" }));

		REQUIRE(moves.empty());
	}

	SECTION("White rook, centre") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "D4";
		board.square(from) = piece_t::WhiteRook;
		auto moves = generator.generate_moves();

		// Horizontal moves
		REQUIRE(move_t::remove_move(moves, { from, "A4" }));
		REQUIRE(move_t::remove_move(moves, { from, "B4" }));
		REQUIRE(move_t::remove_move(moves, { from, "C4" }));
		REQUIRE(move_t::remove_move(moves, { from, "E4" }));
		REQUIRE(move_t::remove_move(moves, { from, "F4" }));
		REQUIRE(move_t::remove_move(moves, { from, "G4" }));
		REQUIRE(move_t::remove_move(moves, { from, "H4" }));

		// Vertical moves
		REQUIRE(move_t::remove_move(moves, { from, "D1" }));
		REQUIRE(move_t::remove_move(moves, { from, "D2" }));
		REQUIRE(move_t::remove_move(moves, { from, "D3" }));
		REQUIRE(move_t::remove_move(moves, { from, "D5" }));
		REQUIRE(move_t::remove_move(moves, { from, "D6" }));
		REQUIRE(move_t::remove_move(moves, { from, "D7" }));
		REQUIRE(move_t::remove_move(moves, { from, "D8" }));

		REQUIRE(moves.empty());
	}

	SECTION("White rook, centre, blocked right") {

		board.current_player() = piece_t::WHITE;

		const std::string from = "D4";
		const auto from_idx = notation_t::algebraic_2_index(from);
		const auto from_piece = piece_t::WhiteRook;
		board.square(from_idx) = from_piece;

		board.square("F4") = piece_t::WhitePawn;

		auto moves = generator.generate_moves(from_idx, from_piece);

		// Horizontal moves
		REQUIRE(move_t::remove_move(moves, { from, "A4" }));
		REQUIRE(move_t::remove_move(moves, { from, "B4" }));
		REQUIRE(move_t::remove_move(moves, { from, "C4" }));
		REQUIRE(move_t::remove_move(moves, { from, "E4" }));

		// Vertical moves
		REQUIRE(move_t::remove_move(moves, { from, "D1" }));
		REQUIRE(move_t::remove_move(moves, { from, "D2" }));
		REQUIRE(move_t::remove_move(moves, { from, "D3" }));
		REQUIRE(move_t::remove_move(moves, { from, "D5" }));
		REQUIRE(move_t::remove_move(moves, { from, "D6" }));
		REQUIRE(move_t::remove_move(moves, { from, "D7" }));
		REQUIRE(move_t::remove_move(moves, { from, "D8" }));

		REQUIRE(moves.empty());
	}

	SECTION("White rook, centre, blocked left") {

		board.current_player() = piece_t::WHITE;

		const std::string from = "D4";
		const auto from_idx = notation_t::algebraic_2_index(from);
		const auto from_piece = piece_t::WhiteRook;
		board.square(from_idx) = from_piece;

		board.square("B4") = piece_t::WhitePawn;

		auto moves = generator.generate_moves(from_idx, from_piece);

		// Horizontal moves
		REQUIRE(move_t::remove_move(moves, { from, "C4" }));
		REQUIRE(move_t::remove_move(moves, { from, "E4" }));
		REQUIRE(move_t::remove_move(moves, { from, "F4" }));
		REQUIRE(move_t::remove_move(moves, { from, "G4" }));
		REQUIRE(move_t::remove_move(moves, { from, "H4" }));

		// Vertical moves
		REQUIRE(move_t::remove_move(moves, { from, "D1" }));
		REQUIRE(move_t::remove_move(moves, { from, "D2" }));
		REQUIRE(move_t::remove_move(moves, { from, "D3" }));
		REQUIRE(move_t::remove_move(moves, { from, "D5" }));
		REQUIRE(move_t::remove_move(moves, { from, "D6" }));
		REQUIRE(move_t::remove_move(moves, { from, "D7" }));
		REQUIRE(move_t::remove_move(moves, { from, "D8" }));

		REQUIRE(moves.empty());
	}

	SECTION("White rook, centre, blocked above") {

		board.current_player() = piece_t::WHITE;

		const std::string from = "D4";
		const auto from_idx = notation_t::algebraic_2_index(from);
		const auto from_piece = piece_t::WhiteRook;
		board.square(from_idx) = from_piece;

		board.square("D6") = piece_t::WhitePawn;

		auto moves = generator.generate_moves(from_idx, from_piece);

		// Horizontal moves
		REQUIRE(move_t::remove_move(moves, { from, "A4" }));
		REQUIRE(move_t::remove_move(moves, { from, "B4" }));
		REQUIRE(move_t::remove_move(moves, { from, "C4" }));
		REQUIRE(move_t::remove_move(moves, { from, "E4" }));
		REQUIRE(move_t::remove_move(moves, { from, "F4" }));
		REQUIRE(move_t::remove_move(moves, { from, "G4" }));
		REQUIRE(move_t::remove_move(moves, { from, "H4" }));

		// Vertical moves
		REQUIRE(move_t::remove_move(moves, { from, "D1" }));
		REQUIRE(move_t::remove_move(moves, { from, "D2" }));
		REQUIRE(move_t::remove_move(moves, { from, "D3" }));
		REQUIRE(move_t::remove_move(moves, { from, "D5" }));

		REQUIRE(moves.empty());
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
		auto moves = generator.generate_moves();

		// Diagonal moves
		REQUIRE(move_t::remove_move(moves, { from, "B2" }));
		REQUIRE(move_t::remove_move(moves, { from, "C3" }));
		REQUIRE(move_t::remove_move(moves, { from, "D4" }));
		REQUIRE(move_t::remove_move(moves, { from, "E5" }));
		REQUIRE(move_t::remove_move(moves, { from, "F6" }));
		REQUIRE(move_t::remove_move(moves, { from, "G7" }));
		REQUIRE(move_t::remove_move(moves, { from, "H8" }));

		REQUIRE(moves.empty());
	}

	SECTION("White bishop, centre") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "D4";
		board.square(from) = piece_t::WhiteBishop;
		auto moves = generator.generate_moves();

		// Right to left
		REQUIRE(move_t::remove_move(moves, { from, "C5" }));
		REQUIRE(move_t::remove_move(moves, { from, "C3" }));
		REQUIRE(move_t::remove_move(moves, { from, "B6" }));
		REQUIRE(move_t::remove_move(moves, { from, "B2" }));
		REQUIRE(move_t::remove_move(moves, { from, "A7" }));
		REQUIRE(move_t::remove_move(moves, { from, "A1" }));

		// Left to right
		REQUIRE(move_t::remove_move(moves, { from, "E5" }));
		REQUIRE(move_t::remove_move(moves, { from, "E3" }));
		REQUIRE(move_t::remove_move(moves, { from, "F6" }));
		REQUIRE(move_t::remove_move(moves, { from, "F2" }));
		REQUIRE(move_t::remove_move(moves, { from, "G7" }));
		REQUIRE(move_t::remove_move(moves, { from, "G1" }));
		REQUIRE(move_t::remove_move(moves, { from, "H8" }));

		REQUIRE(moves.empty());
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
		auto moves = generator.generate_moves();

		// Bishop moves
		// Diagonal moves
		REQUIRE(move_t::remove_move(moves, { from, "B2" }));
		REQUIRE(move_t::remove_move(moves, { from, "C3" }));
		REQUIRE(move_t::remove_move(moves, { from, "D4" }));
		REQUIRE(move_t::remove_move(moves, { from, "E5" }));
		REQUIRE(move_t::remove_move(moves, { from, "F6" }));
		REQUIRE(move_t::remove_move(moves, { from, "G7" }));
		REQUIRE(move_t::remove_move(moves, { from, "H8" }));

		// Rook moves
		// Horizontal moves
		REQUIRE(move_t::remove_move(moves, { from, "A2" }));
		REQUIRE(move_t::remove_move(moves, { from, "A3" }));
		REQUIRE(move_t::remove_move(moves, { from, "A4" }));
		REQUIRE(move_t::remove_move(moves, { from, "A5" }));
		REQUIRE(move_t::remove_move(moves, { from, "A6" }));
		REQUIRE(move_t::remove_move(moves, { from, "A7" }));
		REQUIRE(move_t::remove_move(moves, { from, "A8" }));
		// Vertical moves
		REQUIRE(move_t::remove_move(moves, { from, "B1" }));
		REQUIRE(move_t::remove_move(moves, { from, "C1" }));
		REQUIRE(move_t::remove_move(moves, { from, "D1" }));
		REQUIRE(move_t::remove_move(moves, { from, "E1" }));
		REQUIRE(move_t::remove_move(moves, { from, "F1" }));
		REQUIRE(move_t::remove_move(moves, { from, "G1" }));
		REQUIRE(move_t::remove_move(moves, { from, "H1" }));

		REQUIRE(moves.empty());
	}

	SECTION("White queen, centre") {
		board.current_player() = piece_t::WHITE;
		const std::string from = "D4";
		board.square(from) = piece_t::WhiteQueen;
		auto moves = generator.generate_moves();

		// Bishop moves
		// Right to left
		REQUIRE(move_t::remove_move(moves, { from, "C5" }));
		REQUIRE(move_t::remove_move(moves, { from, "C3" }));
		REQUIRE(move_t::remove_move(moves, { from, "B6" }));
		REQUIRE(move_t::remove_move(moves, { from, "B2" }));
		REQUIRE(move_t::remove_move(moves, { from, "A7" }));
		REQUIRE(move_t::remove_move(moves, { from, "A1" }));
		// Left to right
		REQUIRE(move_t::remove_move(moves, { from, "E5" }));
		REQUIRE(move_t::remove_move(moves, { from, "E3" }));
		REQUIRE(move_t::remove_move(moves, { from, "F6" }));
		REQUIRE(move_t::remove_move(moves, { from, "F2" }));
		REQUIRE(move_t::remove_move(moves, { from, "G7" }));
		REQUIRE(move_t::remove_move(moves, { from, "G1" }));
		REQUIRE(move_t::remove_move(moves, { from, "H8" }));

		// Rook moves
		// Horizontal moves
		REQUIRE(move_t::remove_move(moves, { from, "A4" }));
		REQUIRE(move_t::remove_move(moves, { from, "B4" }));
		REQUIRE(move_t::remove_move(moves, { from, "C4" }));
		REQUIRE(move_t::remove_move(moves, { from, "E4" }));
		REQUIRE(move_t::remove_move(moves, { from, "F4" }));
		REQUIRE(move_t::remove_move(moves, { from, "G4" }));
		REQUIRE(move_t::remove_move(moves, { from, "H4" }));
		// Vertical moves
		REQUIRE(move_t::remove_move(moves, { from, "D1" }));
		REQUIRE(move_t::remove_move(moves, { from, "D2" }));
		REQUIRE(move_t::remove_move(moves, { from, "D3" }));
		REQUIRE(move_t::remove_move(moves, { from, "D5" }));
		REQUIRE(move_t::remove_move(moves, { from, "D6" }));
		REQUIRE(move_t::remove_move(moves, { from, "D7" }));
		REQUIRE(move_t::remove_move(moves, { from, "D8" }));

		REQUIRE(moves.empty());
	}
}
