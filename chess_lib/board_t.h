#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <array>

#include "square_t.h"
#include "move_t.h"
#include "piece_t.h"

class board_t final {
private:
	std::array<square_t, 64> m_squares;
	piece_t::colour_t m_current_player = piece_t::WHITE;

	static std::array<int, 8> _reverse_row;

public:
	constexpr board_t() noexcept {}

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
		return algebraic_2_index(std::pair<char, char>(column, row));
	}

	static constexpr auto algebraic_2_index(const std::string& input) noexcept {
		return algebraic_2_index(input.c_str()[0], input.c_str()[1]);
	}

	static constexpr auto index_2_algebraic(int index) noexcept {
		return numeric_2_algebraic(index_2_numeric(index));
	}

	// Accessors

	constexpr auto& squares() noexcept { return m_squares; }
	constexpr const auto& squares() const noexcept { return m_squares; }

	constexpr const auto& square(int idx) const noexcept { return squares()[idx]; }
	constexpr auto& square(int idx) noexcept { return squares()[idx]; }

	constexpr const auto& square(int column, int row) const noexcept { return square(numeric_2_index(column, row)); }
	constexpr auto& square(int column, int row) noexcept { return square(numeric_2_index(column, row)); }

	constexpr auto& current_player() noexcept { return m_current_player; }
	constexpr auto current_player() const noexcept { return m_current_player; }

	void clear_squares() noexcept;
	void swap_current_player() noexcept;

	std::string representaton() const;
	static std::string representation(int idx);
	static std::string representation(int column, int row);

	static std::string representation(move_t move);
	static std::string representation(std::vector<move_t> moves);

	static std::string representation(piece_t::colour_t colour);

	void initialise() noexcept;

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

	static auto find_move(const std::vector<move_t>& moves, const move_t& move) {
		return std::find(moves.begin(), moves.end(), move);
	}

	static auto has_move(const std::vector<move_t>& moves, const move_t& move) {
		return find_move(moves, move) != moves.end();
	}
};