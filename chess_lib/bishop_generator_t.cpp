#include "pch.h"
#include "bishop_generator_t.h"
#include "generator_t.h"

bishop_generator_t::bishop_generator_t(const generator_t& generator) noexcept
: m_generator(generator) {}

std::vector<move_t> bishop_generator_t::generate(int from, piece_t::colour_t colour) const {
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
				generator().maybe_add(moves, from, c_col, c_row_high);
			if (c_row_low-- > 0)
				generator().maybe_add(moves, from, c_col, c_row_low);
		}
	}

	// Left to right
	{
		int c_row_high = row;
		int c_row_low = row;
		for (int c_col = column + 1; c_col < 8; ++c_col) {
			if (c_row_high++ < 8)
				generator().maybe_add(moves, from, c_col, c_row_high);
			if (c_row_low-- > 0)
				generator().maybe_add(moves, from, c_col, c_row_low);
		}
	}

	return moves;
}

std::vector<move_t> bishop_generator_t::generate(const std::string& from, piece_t::colour_t colour) const {
	return generate(notation_t::algebraic_2_index(from), colour);
}
