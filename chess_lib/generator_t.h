#pragma once

#include <algorithm>
#include <vector>
#include <string>

#include "piece_t.h"
#include "move_t.h"
#include "board_t.h"

#include "pawn_generator_t.h"

class generator_t final {
private:
	const board_t& m_board;

	const pawn_generator_t m_pawn_generator = { *this };

	[[nodiscard]] constexpr const auto& board() const noexcept { return m_board; }

	static void add(std::vector<move_t>& moves, int from, int to);
	static void add(std::vector<move_t>& moves, int from, int column, int row);

public:
	generator_t(const board_t& board) noexcept;

	[[nodiscard]] constexpr const auto& pawn_generator() const noexcept { return m_pawn_generator; }

	bool maybe_add(std::vector<move_t>& moves, int from, int column, int row) const;
	bool maybe_add(std::vector<move_t>& moves, int from, int to) const;

	[[nodiscard]] std::vector<move_t> generate_rook_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_rook_moves(const std::string& from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_knight_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_knight_moves(const std::string& from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_bishop_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_bishop_moves(const std::string& from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_queen_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_queen_moves(const std::string& from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_king_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_king_moves(const std::string& from, piece_t::colour_t colour) const;

	[[nodiscard]] std::vector<move_t> generate_moves(int from, piece_t piece) const;
	[[nodiscard]] std::vector<move_t> generate_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_moves(piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_moves() const;
};
