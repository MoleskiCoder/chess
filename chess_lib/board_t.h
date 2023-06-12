#pragma once

#include <vector>
#include <string>
#include <utility>
#include <array>

#include "square_t.h"
#include "move_t.h"
#include "piece_t.h"

class board_t final {
private:
	std::vector<square_t> m_squares;
	piece_t::colour_t m_current_player = piece_t::WHITE;

	static std::array<int, 8> _reverse_row;

public:
	board_t();

	// X/Y to/from index

	static constexpr auto xy_2_index(int x, int y) noexcept { return y * 8 + x; }
	static constexpr std::pair<int, int> index_2_xy(int i) noexcept { return { i % 8, i / 8 }; }

	// X/Y to/from numeric

	static constexpr std::pair<int, int> index_2_numeric(int i) noexcept {
		const auto [x, y] = index_2_xy(i);
		return { x, _reverse_row[y] };
	}

	static constexpr int numeric_2_index(int column, int row) noexcept {
		return xy_2_index(column, _reverse_row[row]);
	}

	static constexpr int numeric_2_index(std::pair<int, int> input) noexcept { return numeric_2_index(input.first, input.second); }

	// numeric to/from algebraic

	static constexpr std::pair<char, char> numeric_2_algebraic(int column, int row) noexcept {
		return { static_cast<char>('A' + column), static_cast<char>('1' + row) };
	}

	static constexpr auto numeric_2_algebraic(std::pair<int, int> input) noexcept { return numeric_2_algebraic(input.first, input.second); }

	static constexpr std::pair<int, int> algebraic_2_numeric(char column, char row) noexcept {
		return { column - 'A', row - '1' };
	}

	static constexpr auto algebraic_2_numeric(std::pair<char, char> input) noexcept { return algebraic_2_numeric(input.first, input.second); }

	// index to/from algebraic

	static constexpr auto algebraic_2_index(std::pair<char, char> input) noexcept {
		return numeric_2_index(algebraic_2_numeric(input));
	}

	static constexpr auto algebraic_2_index(char column, char row) noexcept {
		return algebraic_2_index({ column, row });
	}

	static constexpr auto index_2_algebraic(int index) noexcept {
		return numeric_2_algebraic(index_2_numeric(index));
	}

	// Accessors

	auto& squares() { return m_squares; }
	const auto& squares() const { return m_squares; }

	const auto& square(int idx) const { return squares().at(idx); }
	auto& square(int idx) { return squares().at(idx); }

	const auto& square(int column, int row) const { return square(numeric_2_index(column, row)); }
	auto& square(int column, int row) { return square(numeric_2_index(column, row)); }

	auto& current_player() { return m_current_player; }
	auto current_player() const { return m_current_player; }

	void swap_current_player();

	std::string representaton() const;
	static std::string representation(int idx);
	static std::string representation(int column, int row);

	static std::string representation(move_t move);
	static std::string representation(std::vector<move_t> moves);

	static std::string representation(piece_t::colour_t colour);

	void initialise();

	std::vector<move_t> generate_rook_moves(int idx, piece_t::colour_t colour) const;
	std::vector<move_t> generate_knight_moves(int idx, piece_t::colour_t colour) const;
	std::vector<move_t> generate_bishop_moves(int idx, piece_t::colour_t colour) const;
	std::vector<move_t> generate_queen_moves(int idx, piece_t::colour_t colour) const;
	std::vector<move_t> generate_king_moves(int idx, piece_t::colour_t colour) const;
	std::vector<move_t> generate_pawn_moves(int idx, piece_t::colour_t colour) const;

	std::vector<move_t> generate_moves(int idx, piece_t piece) const;
	std::vector<move_t> generate_moves(int idx, piece_t::colour_t colour) const;
	std::vector<move_t> generate_moves(piece_t::colour_t colour) const;
	std::vector<move_t> generate_moves() const;
};