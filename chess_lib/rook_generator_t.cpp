#include "pch.h"
#include "rook_generator_t.h"
#include "generator_t.h"

rook_generator_t::rook_generator_t(const generator_t& generator) noexcept
: m_generator(generator) {}

std::vector<move_t> rook_generator_t::generate(int from, piece_t::colour_t colour) const {
	// moves vertically and horizontally
	// cannot jump over other pieces
	std::vector<move_t> moves;
	const auto [column, row] = notation_t::index_2_numeric(from);

	// Horizontal moves
	// Right to left
	for (int candidate = column - 1; candidate >= 0; --candidate)
		if (!generator().maybe_add(moves, from, candidate, row))
			break;
	// Left to right
	for (int candidate = column + 1; candidate < 8; ++candidate)
		if (!generator().maybe_add(moves, from, candidate, row))
			break;

	// Vertical moves
	// Bottom to top
	for (int candidate = row - 1; candidate >= 0; --candidate)
		if (!generator().maybe_add(moves, from, column, candidate))
			break;
	// Top to bottom
	for (int candidate = row + 1; candidate < 8; ++candidate)
		if (!generator().maybe_add(moves, from, column, candidate))
			break;

	return moves;
}

std::vector<move_t> rook_generator_t::generate(const std::string& from, piece_t::colour_t colour) const {
	return generate(notation_t::algebraic_2_index(from), colour);
}
