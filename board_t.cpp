#include "board_t.h"

#include <cassert>
#include <sstream>
#include <exception>

board_t::board_t()
: m_squares(64) {}

void board_t::initialise() {
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

std::string board_t::representation(piece_t::colour_t colour) {
	return colour == piece_t::WHITE ? "W" : "B";
}

std::vector<move_t> board_t::generate_rook_moves(int from, piece_t::colour_t colour) const {
	// moves vertically and horizontally
	// cannot jump over other pieces
	std::vector<move_t> moves;
	const auto [column, row] = index_2_numeric(from);
	return moves;
}

std::vector<move_t> board_t::generate_knight_moves(int from, piece_t::colour_t colour) const {
	// two squares horizontal, one vertical
	// two squares vertical, one horizontal
	// may jump over any other piece
	std::vector<move_t> moves;
	const auto [column, row] = index_2_numeric(from);
	return moves;
}

std::vector<move_t> board_t::generate_bishop_moves(int from, piece_t::colour_t colour) const {
	// moves diagonally
	// cannot jump over other pieces
	std::vector<move_t> moves;
	const auto [column, row] = index_2_numeric(from);
	return moves;
}

std::vector<move_t> board_t::generate_queen_moves(int from, piece_t::colour_t colour) const {
	// Moves in any direction
	// cannot jump over other pieces
	std::vector<move_t> moves;
	const auto [column, row] = index_2_numeric(from);
	return moves;
}

std::vector<move_t> board_t::generate_king_moves(int from, piece_t::colour_t colour) const {
	// Moves in any direction, only one square
	std::vector<move_t> moves;
	const auto [column, row] = index_2_numeric(from);
	return moves;
}

std::vector<move_t> board_t::generate_pawn_moves(int from, piece_t::colour_t colour) const {
	// needs colour for direction
	// Moves down the board only
	// Moves one or two squares first move, then one thereafter
	// cannot jump over other pieces
	std::vector<move_t> moves;
	const auto [column, row] = index_2_numeric(from);
	switch (colour) {
	case piece_t::WHITE:
		moves.push_back(move_t(from, numeric_2_index(column, row + 1)));
		if (row == 1)
			moves.push_back(move_t(from, numeric_2_index(column, row + 2)));
		break;
	case piece_t::BLACK:
		moves.push_back(move_t(from, numeric_2_index(column, row - 1)));
		if (row == 1)
			moves.push_back(move_t(from, numeric_2_index(column, row - 2)));
		break;
	default:
		assert(false && "Unknown piece colour");
	}
	return moves;
}

std::vector<move_t> board_t::generate_moves(int idx, piece_t piece) const {
	const auto colour = piece.colour();
	const auto type = piece.type();
	switch (type) {
	case piece_t::ROOK:
		return generate_rook_moves(idx, colour);
		break;
	case piece_t::KNIGHT:
		return generate_knight_moves(idx, colour);
		break;
	case piece_t::BISHOP:
		return generate_bishop_moves(idx, colour);
		break;
	case piece_t::QUEEN:
		return generate_queen_moves(idx, colour);
		break;
	case piece_t::KING:
		return generate_king_moves(idx, colour);
		break;
	case piece_t::PAWN:
		return generate_pawn_moves(idx, colour);
	}
	throw std::logic_error("Unknown piece type");
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
