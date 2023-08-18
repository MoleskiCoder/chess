#include "pch.h"
#include "queen_generator_t.h"
#include "generator_t.h"

queen_generator_t::queen_generator_t(const generator_t& generator) noexcept
: m_generator(generator) {}

std::vector<move_t> queen_generator_t::generate(int from, piece_t::colour_t colour) const {
	// Moves in any direction
	// cannot jump over other pieces
	auto moves = generator().rook_generator().generate(from, colour);
	const auto bishop_moves = generator().bishop_generator().generate(from, colour);
	moves.insert(moves.begin(), bishop_moves.begin(), bishop_moves.end());
	return moves;
}

std::vector<move_t> queen_generator_t::generate(const std::string& from, piece_t::colour_t colour) const {
	return generate(notation_t::algebraic_2_index(from), colour);
}
