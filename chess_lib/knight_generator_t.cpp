#include "pch.h"
#include "knight_generator_t.h"
#include "generator_t.h"

knight_generator_t::knight_generator_t(const generator_t& generator) noexcept
: m_generator(generator) {}

std::vector<move_t> knight_generator_t::generate(int from, piece_t::colour_t colour) const {
	// two squares horizontal, one vertical
	// two squares vertical, one horizontal
	// may jump over any other piece
	std::vector<move_t> moves;
	const auto [column, row] = notation_t::index_2_numeric(from);
	return moves;
}

std::vector<move_t> knight_generator_t::generate(const std::string& from, piece_t::colour_t colour) const {
	return generate(notation_t::algebraic_2_index(from), colour);
}
