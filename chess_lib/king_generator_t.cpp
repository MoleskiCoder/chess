#include "pch.h"
#include "king_generator_t.h"
#include "generator_t.h"

king_generator_t::king_generator_t(const generator_t& generator) noexcept
: m_generator(generator) {}

std::vector<move_t> king_generator_t::generate(int from, piece_t::colour_t colour) const {
	// Moves in any direction, only one square
	std::vector<move_t> moves;
	const auto [column, row] = notation_t::index_2_numeric(from);
	return moves;
}

std::vector<move_t> king_generator_t::generate(const std::string& from, piece_t::colour_t colour) const {
	return generate(notation_t::algebraic_2_index(from), colour);
}
