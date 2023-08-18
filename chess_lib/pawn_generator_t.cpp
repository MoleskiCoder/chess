#include "pch.h"
#include "pawn_generator_t.h"
#include "generator_t.h"

pawn_generator_t::pawn_generator_t(const generator_t& generator) noexcept
: m_generator(generator) {}

std::vector<move_t> pawn_generator_t::generate(int from, piece_t::colour_t colour) const {
	// needs colour for direction
	// Moves down the board only
	// Moves one or two squares first move, then one thereafter
	// cannot jump over other pieces
	std::vector<move_t> moves;
	const auto [column, row] = notation_t::index_2_numeric(from);
	switch (colour) {
	case piece_t::WHITE:
		if (generator().maybe_add(moves, from, column, row + 1))
			if (row == 1)
				generator().maybe_add(moves, from, column, row + 2);
		break;
	case piece_t::BLACK:
		if (generator().maybe_add(moves, from, column, row - 1))
			if (row == 6)
				generator().maybe_add(moves, from, column, row - 2);
		break;
	default:
		assert(false && "Unknown piece colour");
	}
	return moves;
}

std::vector<move_t> pawn_generator_t::generate(const std::string& from, piece_t::colour_t colour) const {
	return generate(notation_t::algebraic_2_index(from), colour);
}
