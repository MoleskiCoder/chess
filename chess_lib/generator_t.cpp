#include "pch.h"
#include "generator_t.h"

void generator_t::add(std::vector<move_t>& moves, int from, int to) {
	const move_t move = { from, to };
	moves.push_back(move);
}

void generator_t::add(std::vector<move_t>& moves, int from, int column, int row) {
	add(moves, from, notation_t::numeric_2_index(column, row));
}

bool generator_t::maybe_add(std::vector<move_t>& moves, int from, int column, int row) const {
	const auto to = notation_t::numeric_2_index(column, row);
	return maybe_add(moves, from, to);
}

bool generator_t::maybe_add(std::vector<move_t>& moves, int from, int to) const {
	const auto& source = board().square(from).contents();
	const auto& destination = board().square(to).contents();
	assert(source.has_value() && "Impossible move from an empty square");
	const bool allowed = !destination.has_value() || (source->colour() != destination->colour());
	if (allowed)
		add(moves, from, to);
	return allowed;
}

//

std::vector<move_t> generator_t::generate_rook_moves(int from, piece_t::colour_t colour) const {
	// moves vertically and horizontally
	// cannot jump over other pieces
	std::vector<move_t> moves;
	const auto [column, row] = notation_t::index_2_numeric(from);

	// Horizontal moves
	// Right to left
	for (int candidate = column - 1; candidate >= 0; --candidate)
		if (!maybe_add(moves, from, candidate, row))
			break;
	// Left to right
	for (int candidate = column + 1; candidate < 8; ++candidate)
		if (!maybe_add(moves, from, candidate, row))
			break;

	// Vertical moves
	// Bottom to top
	for (int candidate = row - 1; candidate >= 0; --candidate)
		if (!maybe_add(moves, from, column, candidate))
			break;
	// Top to bottom
	for (int candidate = row + 1; candidate < 8; ++candidate)
		if (!maybe_add(moves, from, column, candidate))
			break;

	return moves;
}

std::vector<move_t> generator_t::generate_knight_moves(int from, piece_t::colour_t colour) const {
	// two squares horizontal, one vertical
	// two squares vertical, one horizontal
	// may jump over any other piece
	std::vector<move_t> moves;
	const auto [column, row] = notation_t::index_2_numeric(from);
	return moves;
}

std::vector<move_t> generator_t::generate_bishop_moves(int from, piece_t::colour_t colour) const {
	// moves diagonally
	// cannot jump over other pieces
	std::vector<move_t> moves;
	const auto [column, row] = notation_t::index_2_numeric(from);

	// Right to left
	{
		int c_row_high = row;
		int c_row_low = row;
		for (int c_col = column - 1; c_col >= 0; --c_col) {
			if (c_row_high++ < 8)
				maybe_add(moves, from, c_col, c_row_high);
			if (c_row_low-- > 0)
				maybe_add(moves, from, c_col, c_row_low);
		}
	}

	// Left to right
	{
		int c_row_high = row;
		int c_row_low = row;
		for (int c_col = column + 1; c_col < 8; ++c_col) {
			if (c_row_high++ < 8)
				maybe_add(moves, from, c_col, c_row_high);
			if (c_row_low-- > 0)
				maybe_add(moves, from, c_col, c_row_low);
		}
	}

	return moves;
}

std::vector<move_t> generator_t::generate_queen_moves(int from, piece_t::colour_t colour) const {
	// Moves in any direction
	// cannot jump over other pieces
	auto moves = generate_rook_moves(from, colour);
	const auto bishop_moves = generate_bishop_moves(from, colour);
	moves.insert(moves.begin(), bishop_moves.begin(), bishop_moves.end());
	return moves;
}

std::vector<move_t> generator_t::generate_king_moves(int from, piece_t::colour_t colour) const {
	// Moves in any direction, only one square
	std::vector<move_t> moves;
	const auto [column, row] = notation_t::index_2_numeric(from);
	return moves;
}

std::vector<move_t> generator_t::generate_pawn_moves(int from, piece_t::colour_t colour) const {
	// needs colour for direction
	// Moves down the board only
	// Moves one or two squares first move, then one thereafter
	// cannot jump over other pieces
	std::vector<move_t> moves;
	const auto [column, row] = notation_t::index_2_numeric(from);
	switch (colour) {
	case piece_t::WHITE:
		if (maybe_add(moves, from, column, row + 1))
			if (row == 1)
				maybe_add(moves, from, column, row + 2);
		break;
	case piece_t::BLACK:
		if (maybe_add(moves, from, column, row - 1))
			if (row == 6)
				maybe_add(moves, from, column, row - 2);
		break;
	default:
		assert(false && "Unknown piece colour");
	}
	return moves;
}

std::vector<move_t> generator_t::generate_moves(int idx, piece_t piece) const {
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

std::vector<move_t> generator_t::generate_moves(int idx, piece_t::colour_t colour) const {
	const auto& contents = board().square(idx).contents();
	const auto empty = !contents.has_value();
	std::vector<move_t> moves;
	if (empty || (contents->colour() != colour)) return moves;
	return generate_moves(idx, *contents);
}

std::vector<move_t> generator_t::generate_moves(piece_t::colour_t colour) const {
	std::vector<move_t> moves;
	for (int i = 0; i < 64; ++i) {
		const auto square_moves = generate_moves(i, colour);
		moves.insert(moves.begin(), square_moves.begin(), square_moves.end());
	}
	return moves;
}

std::vector<move_t> generator_t::generate_moves() const {
	return generate_moves(board().current_player());
}
