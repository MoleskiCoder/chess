#include "board_t.h"

#include <sstream>
#include <iostream>

board_t::board_t()
: m_squares(64) {}

void board_t::initialise() {
	squares() = {
		piece_t::BlackRook,	piece_t::BlackKnight,	piece_t::BlackBishop,	piece_t::BlackQueen,	piece_t::BlackKing,	piece_t::BlackBishop,	piece_t::BlackKnight,	piece_t::BlackRook,
		piece_t::BlackPawn, piece_t::BlackPawn,		piece_t::BlackPawn,		piece_t::BlackPawn,		piece_t::BlackPawn,	piece_t::BlackPawn,		piece_t::BlackPawn,		piece_t::BlackPawn,
		square_t::Empty,	square_t::Empty,		square_t::Empty,		square_t::Empty,		square_t::Empty,	square_t::Empty,		square_t::Empty,		square_t::Empty,
		square_t::Empty,	square_t::Empty,		square_t::Empty,		square_t::Empty,		square_t::Empty,	square_t::Empty,		square_t::Empty,		square_t::Empty,
		square_t::Empty,	square_t::Empty,		square_t::Empty,		square_t::Empty,		square_t::Empty,	square_t::Empty,		square_t::Empty,		square_t::Empty,
		square_t::Empty,	square_t::Empty,		square_t::Empty,		square_t::Empty,		square_t::Empty,	square_t::Empty,		square_t::Empty,		square_t::Empty,
		piece_t::WhitePawn, piece_t::WhitePawn,		piece_t::WhitePawn,		piece_t::WhitePawn,		piece_t::WhitePawn,	piece_t::WhitePawn,		piece_t::WhitePawn,		piece_t::WhitePawn,
		piece_t::WhiteRook,	piece_t::WhiteKnight,	piece_t::WhiteBishop,	piece_t::WhiteQueen,	piece_t::WhiteKing,	piece_t::WhiteBishop,	piece_t::WhiteKnight,	piece_t::WhiteRook,
	};
}

std::string board_t::representaton() const {
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

void board_t::show() const {
	std::cout << representaton();
}
