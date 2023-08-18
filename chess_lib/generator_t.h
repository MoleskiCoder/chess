#pragma once

#include <algorithm>
#include <vector>
#include <string>

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
	constexpr generator_t(const board_t& board) noexcept
	: m_board(board) {}

	[[nodiscard]] std::vector<move_t> generate_rook_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_rook_moves(const std::string& from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_knight_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_knight_moves(const std::string& from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_bishop_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_bishop_moves(const std::string& from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_queen_moves(int idfromx, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_queen_moves(const std::string& from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_king_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_king_moves(const std::string& from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_pawn_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_pawn_moves(const std::string& from, piece_t::colour_t colour) const;

	[[nodiscard]] std::vector<move_t> generate_moves(int from, piece_t piece) const;
	[[nodiscard]] std::vector<move_t> generate_moves(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_moves(piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate_moves() const;
};
