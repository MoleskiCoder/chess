#include "pch.h"

#include "board_t.h"

std::array<int, 8> board_t::_reverse_row = { 7, 6, 5, 4, 3, 2, 1, 0 };

void board_t::clear_squares() noexcept {
	squares() = {
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
	};
}

void board_t::initialise() noexcept {
	// N.B. Reversed row notation!!
	squares() = {
		piece_t::WhiteRook, piece_t::WhiteKnight,   piece_t::WhiteBishop,   piece_t::WhiteQueen,    piece_t::WhiteKing, piece_t::WhiteBishop,   piece_t::WhiteKnight,   piece_t::WhiteRook,
		piece_t::WhitePawn, piece_t::WhitePawn,     piece_t::WhitePawn,     piece_t::WhitePawn,     piece_t::WhitePawn, piece_t::WhitePawn,     piece_t::WhitePawn,     piece_t::WhitePawn,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		piece_t::BlackPawn, piece_t::BlackPawn,     piece_t::BlackPawn,     piece_t::BlackPawn,     piece_t::BlackPawn, piece_t::BlackPawn,     piece_t::BlackPawn,     piece_t::BlackPawn,
		piece_t::BlackRook, piece_t::BlackKnight,   piece_t::BlackBishop,   piece_t::BlackQueen,    piece_t::BlackKing, piece_t::BlackBishop,   piece_t::BlackKnight,   piece_t::BlackRook,
	};
	current_player() = piece_t::WHITE;
}

void board_t::swap_current_player() noexcept {
	current_player() = current_player() == piece_t::WHITE ? piece_t::BLACK : piece_t::WHITE;
}

std::string board_t::representation() const {
	std::ostringstream oss;
	for (int row = 0; row < 8; ++row) {
		oss << std::endl;
		for (int column = 0; column < 8; ++column) {
			oss << square(column, row).representation();
		}
		oss << std::endl;
	}
	return oss.str();
}

std::string board_t::representation(int idx) {
	const auto [column, row] = index_2_algebraic(idx);
	return std::string({ column, row });
}

std::string board_t::representation(int column, int row) {
	const auto [column_char, row_char] = numeric_2_algebraic(column, row);
	return std::string({ column_char, row_char });
}


std::string board_t::representation(piece_t::colour_t colour) {
	return colour == piece_t::WHITE ? "W" : "B";
}

