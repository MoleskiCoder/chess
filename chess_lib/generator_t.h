#pragma once

#include <algorithm>
#include <vector>

#include "piece_t.h"
#include "move_t.h"
#include "board_t.h"

class generator_t final {
private:
	const board_t& m_board;

	[[nodiscard]] constexpr const auto& board() const noexcept { return m_board; }

	static void add(std::vector<move_t>& moves, int from, int to);
	static void add(std::vector<move_t>& moves, int from, int column, int row);

	bool maybe_add(std::vector<move_t>& moves, int from, int column, int row) const;
	bool maybe_add(std::vector<move_t>& moves, int from, int to) const;

public:
	generator_t(const board_t& board);

	[[nodiscard]] std::vector<move_t> generate_rook_moves(int idx, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_knight_moves(int idx, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_bishop_moves(int idx, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_queen_moves(int idx, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_king_moves(int idx, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_pawn_moves(int idx, piece_t::colour_t colour) const;

	[[nodiscard]] std::vector<move_t> generate_moves(int idx, piece_t piece) const;
	[[nodiscard]] std::vector<move_t> generate_moves(int idx, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_moves(piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_moves() const;

	[[nodiscard]] static auto find_move(const std::vector<move_t>& moves, const move_t& move) {
		return std::find(moves.begin(), moves.end(), move);
	}

	[[nodiscard]] static auto has_move(const std::vector<move_t>& moves, const move_t& move) {
		return find_move(moves, move) != moves.end();
	}

};

