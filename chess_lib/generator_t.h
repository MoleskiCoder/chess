#pragma once

#include <algorithm>
#include <vector>
#include <string>

#include "piece_t.h"
#include "move_t.h"
#include "board_t.h"

#include "pawn_generator_t.h"
#include "rook_generator_t.h"
#include "knight_generator_t.h"
#include "bishop_generator_t.h"
#include "queen_generator_t.h"
#include "king_generator_t.h"

class generator_t final {
private:
	const board_t& m_board;

	const pawn_generator_t m_pawn_generator = { *this };
	const rook_generator_t m_rook_generator = { *this };
	const knight_generator_t m_knight_generator = { *this };
	const bishop_generator_t m_bishop_generator = { *this };
	const queen_generator_t m_queen_generator = { *this };
	const king_generator_t m_king_generator = { *this };

	[[nodiscard]] constexpr const auto& board() const noexcept { return m_board; }

	static void add(std::vector<move_t>& moves, int from, int to);
	static void add(std::vector<move_t>& moves, int from, int column, int row);

public:
	generator_t(const board_t& board) noexcept;

	[[nodiscard]] constexpr const auto& pawn_generator() const noexcept { return m_pawn_generator; }
	[[nodiscard]] constexpr const auto& rook_generator() const noexcept { return m_rook_generator; }
	[[nodiscard]] constexpr const auto& knight_generator() const noexcept { return m_knight_generator; }
	[[nodiscard]] constexpr const auto& bishop_generator() const noexcept { return m_bishop_generator; }
	[[nodiscard]] constexpr const auto& queen_generator() const noexcept { return m_queen_generator; }
	[[nodiscard]] constexpr const auto& king_generator() const noexcept { return m_king_generator; }

	bool maybe_add(std::vector<move_t>& moves, int from, int column, int row) const;
	bool maybe_add(std::vector<move_t>& moves, int from, int to) const;

	[[nodiscard]] std::vector<move_t> generate_moves(int from, piece_t piece) const;
	[[nodiscard]] std::vector<move_t> generate_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_moves(piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_moves() const;
};
