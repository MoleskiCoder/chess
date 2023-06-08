#include "board_t.h"

#include <cassert>
#include <sstream>

board_t::board_t()
: m_squares(64) {}

void board_t::initialise() {
		squares() = {
		piece_t::BlackRook, piece_t::BlackKnight,   piece_t::BlackBishop,   piece_t::BlackQueen,    piece_t::BlackKing, piece_t::BlackBishop,   piece_t::BlackKnight,   piece_t::BlackRook,
		piece_t::BlackPawn, piece_t::BlackPawn,     piece_t::BlackPawn,     piece_t::BlackPawn,     piece_t::BlackPawn, piece_t::BlackPawn,     piece_t::BlackPawn,     piece_t::BlackPawn,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,        square_t::Empty,    square_t::Empty,        square_t::Empty,        square_t::Empty,
		piece_t::WhitePawn, piece_t::WhitePawn,     piece_t::WhitePawn,     piece_t::WhitePawn,     piece_t::WhitePawn, piece_t::WhitePawn,     piece_t::WhitePawn,     piece_t::WhitePawn,
		piece_t::WhiteRook, piece_t::WhiteKnight,   piece_t::WhiteBishop,   piece_t::WhiteQueen,    piece_t::WhiteKing, piece_t::WhiteBishop,   piece_t::WhiteKnight,   piece_t::WhiteRook,
	};
	current_player() = piece_t::WHITE;
}

void board_t::swap_current_player() {
	current_player() = current_player() == piece_t::WHITE ? piece_t::BLACK : piece_t::WHITE;
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

std::string board_t::representation(int idx) {
	const auto [column, row] = index_2_numeric(idx);
	return representation(column, row);
}

std::string board_t::representation(int column, int row) {
	return std::string({ (char)('A' + column), (char)('1' + row) });
}

std::string board_t::representation(move_t move) {
	std::ostringstream oss;
	oss << "From: " << representation(move.from()) << ", To: " << representation(move.to());
	return oss.str();
}

std::string board_t::representation(std::vector<move_t> moves) {
	std::ostringstream oss;
	for (const auto& move : moves)
		oss << representation(move) << std::endl;
	return oss.str();
}

std::vector<move_t> board_t::generate_moves(int idx, piece_t piece) const {
	std::vector<move_t> moves;
	const auto [column, row] = index_2_numeric(idx);
	const auto colour = piece.colour();
	const auto type = piece.type();
	switch (type) {
	case piece_t::ROOK:
		// moves vertically and horizontally
		// cannot jump over other pieces
		break;
	case piece_t::KNIGHT:
		// two squares horizontal, one vertical
		// two squares vertical, one horizontal
		// may jump over any other piece
		break;
	case piece_t::BISHOP:
		// moves diagonally
		// cannot jump over other pieces
		break;
	case piece_t::QUEEN:
		// Moves in any direction
		// cannot jump over other pieces
		break;
	case piece_t::KING:
		// Moves in any direction, only one square
		break;
	case piece_t::PAWN:
		// needs colour for direction
		// Moves down the board only
		// Moves one or two squares first move, then one thereafter
		// cannot jump over other pieces
		switch (colour) {
		case piece_t::WHITE:
			break;
		case piece_t::BLACK:
			break;
		default:
			assert(false && "Unknown piece colour");
		}
		break;
	}
	return moves;
}

std::vector<move_t> board_t::generate_moves(int idx, piece_t::colour_t colour) const {
	const auto& contents = square(idx).contents();
	const auto empty = !contents.has_value();
	std::vector<move_t> moves;
	if (empty || (contents->colour() != colour)) return moves;
	return generate_moves(idx, *contents);
}

std::vector<move_t> board_t::generate_moves(piece_t::colour_t colour) const {
	std::vector<move_t> moves;
	for (int i = 0; i < 64; ++i) {
		const auto square_moves = generate_moves(i, colour);
		moves.insert(moves.begin(), square_moves.begin(), square_moves.end());
	}
	return moves;
}

std::vector<move_t> board_t::generate_moves() const {
	return generate_moves(current_player());
}
