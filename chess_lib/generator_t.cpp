#include "pch.h"
#include "generator_t.h"
#include "notation_t.h"

generator_t::generator_t(const board_t& board) noexcept
: m_board(board) {}

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

std::vector<move_t> generator_t::generate_moves(int from, piece_t piece) const {
	const auto colour = piece.colour();
	const auto type = piece.type();
	switch (type) {
	case piece_t::ROOK:
		return rook_generator().generate(from, colour);
		break;
	case piece_t::KNIGHT:
		return knight_generator().generate(from, colour);
		break;
	case piece_t::BISHOP:
		return bishop_generator().generate(from, colour);
		break;
	case piece_t::QUEEN:
		return queen_generator().generate(from, colour);
		break;
	case piece_t::KING:
		return king_generator().generate(from, colour);
		break;
	case piece_t::PAWN:
		return pawn_generator().generate(from, colour);
	}
	throw std::logic_error("Unknown piece type");
}

std::vector<move_t> generator_t::generate_moves(int from, piece_t::colour_t colour) const {
	const auto& contents = board().square(from).contents();
	const auto empty = !contents.has_value();
	std::vector<move_t> moves;
	if (empty || (contents->colour() != colour)) return moves;
	return generate_moves(from, *contents);
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
