#include "pch.h"

#include <sstream>

#include "board_t.h"

void board_t::clear_squares() noexcept {
	squares() = board_t().squares();
}

void board_t::initialise() noexcept {

	clear_squares();

	square("A1") = square("H1") = piece_t::WhiteRook;
	square("B1") = square("G1") = piece_t::WhiteKnight;
	square("C1") = square("F1") = piece_t::WhiteBishop;
	square("D1") = piece_t::WhiteQueen;
	square("E1") = piece_t::WhiteKing;
	square("A2")
		= square("B2")
		= square("C2")
		= square("D2")
		= square("E2")
		= square("F2")
		= square("G2")
		= square("H2")
		= piece_t::WhitePawn;

	square("A8") = square("H8") = piece_t::BlackRook;
	square("B8") = square("G8") = piece_t::BlackKnight;
	square("C8") = square("F8") = piece_t::BlackBishop;
	square("D8") = piece_t::BlackQueen;
	square("E8") = piece_t::BlackKing;
	square("A7")
		= square("B7")
		= square("C7")
		= square("D7")
		= square("E7")
		= square("F7")
		= square("G7")
		= square("H7")
		= piece_t::BlackPawn;

	current_player() = piece_t::WHITE;
}

void board_t::swap_current_player() noexcept {
	current_player() = current_player() == piece_t::WHITE ? piece_t::BLACK : piece_t::WHITE;
}

std::string board_t::representation() const {
	std::ostringstream oss;
	oss << std::endl << "      A   B   C   D   E   F   G   H" << std::endl;
	for (int row = 7; row >= 0; row--) {
		oss << std::endl;
		oss << "  " << row + 1 << "  ";
		for (int column = 0; column < 8; ++column)
			oss << square(column, row).representation();
		oss << "  " << row + 1 << "  ";
		oss << std::endl;
	}
	oss << std::endl << "      A   B   C   D   E   F   G   H" << std::endl;
	return oss.str();
}

std::string board_t::representation(int idx) {
	const auto [column, row] = notation_t::index_2_algebraic(idx);
	return std::string({ column, row });
}

std::string board_t::representation(int column, int row) {
	const auto [column_char, row_char] = notation_t::numeric_2_algebraic(column, row);
	return std::string({ column_char, row_char });
}


std::string board_t::representation(piece_t::colour_t colour) {
	return colour == piece_t::WHITE ? "W" : "B";
}

void board_t::execute(const move_t& move) {
	auto& from_square = square(move.from());
	assert(from_square.contents().has_value() && "Nothing to move, from square is empty");
	square(move.to()) = from_square;
	from_square = square_t::Empty;
}
