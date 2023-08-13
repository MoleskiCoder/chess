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

std::string board_t::representation(move_t move) {
	std::ostringstream oss;
	oss << "From: " << representation(move.from()) << ", To: " << representation(move.to());
	return oss.str();
}

std::string board_t::representation(const std::vector<move_t>& moves) {
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

	// Horizontal moves
	for (int candidate = 0; candidate < column; ++candidate)
		maybe_add(moves, from, candidate, row);
	for (int candidate = column + 1; candidate < 8; ++candidate)
		maybe_add(moves, from, candidate, row);

	// Vertical moves
	for (int candidate = 0; candidate < row; ++candidate)
		maybe_add(moves, from, column, candidate);
	for (int candidate = row + 1; candidate < 8; ++candidate)
		maybe_add(moves, from, column, candidate);

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

	// Right to left
	{
		int c_row_high = row;
		int c_row_low = row;
		for (int c_col = column - 1; c_col > 0; --c_col) {
			if (c_row_high++ < 8)
				maybe_add(moves, from, c_col, c_row_high);
			if (c_row_low-- > 1)
				maybe_add(moves, from, c_col, c_row_low);
		}
	}

	// Left to right
	{
		int c_row_high = row;
		int c_row_low = row;
		for (int c_col = column + 1; c_col < 9; ++c_col) {
			if (c_row_high++ < 8)
				maybe_add(moves, from, c_col, c_row_high);
			if (c_row_low-- > 1)
				maybe_add(moves, from, c_col, c_row_low);
		}
	}

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
		maybe_add(moves, from, column, row + 1);
		if (row == 1)
			maybe_add(moves, from, column, row + 2);
		break;
	case piece_t::BLACK:
		maybe_add(moves, from, column, row - 1);
		if (row == 6)
			maybe_add(moves, from, column, row - 2);
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

//

void board_t::add(std::vector<move_t>& moves, int from, int to) {
	const move_t move = { from, to };
	moves.push_back(move);
}

void board_t::add(std::vector<move_t>& moves, int from, int column, int row) {
	add(moves, from, numeric_2_index(column, row));
}

bool board_t::maybe_add(std::vector<move_t>& moves, int from, int column, int row) const {
	const auto to = numeric_2_index(column, row);
	return maybe_add(moves, from, to);
}

bool board_t::maybe_add(std::vector<move_t>& moves, int from, int to) const {
	const auto& source = square(from).contents();
	const auto& destination = square(to).contents();
	assert(source.has_value() && "Impossible move from an empty square");
	const bool allowed = !destination.has_value() || (source->colour() != destination->colour());
	if (allowed)
		add(moves, from, to);
	return allowed;
}
