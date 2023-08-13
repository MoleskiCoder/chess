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

	[[nodiscard]] static constexpr auto xy_2_index(int x, int y) noexcept {
		assert(x >= 0 && x <= 7 && "x is out of range");
		assert(y >= 0 && y <= 7 && "y is out of range");
		return y * 8 + x;
	}
	
	[[nodiscard]] static constexpr std::pair<int, int> index_2_xy(int i) noexcept {
		assert(i >= 0 && i <= 63 && "i is out of range");
		return { i % 8, i / 8 };
	}

	// X/Y to/from numeric

	[[nodiscard]] static constexpr std::pair<int, int> index_2_numeric(int i) noexcept {
		const auto [x, y] = index_2_xy(i);
		return { x, _reverse_row[y] };
	}

	[[nodiscard]] static constexpr auto numeric_2_index(int column, int row) noexcept {
		return xy_2_index(column, _reverse_row[row]);
	}

	[[nodiscard]] static constexpr auto numeric_2_index(std::pair<int, int> input) noexcept {
		return numeric_2_index(input.first, input.second);
	}

	// numeric to/from algebraic

	[[nodiscard]] static constexpr std::pair<char, char> numeric_2_algebraic(int column, int row) noexcept {
		assert(column >= 0 && column <= 7);
		assert(row >= 0 && row <= 7);
		return { static_cast<char>('A' + column), static_cast<char>('1' + row) };
	}
	
	[[nodiscard]] static constexpr auto numeric_2_algebraic(std::pair<int, int> input) noexcept {
		return numeric_2_algebraic(input.first, input.second);
	}
	
	[[nodiscard]] static constexpr std::pair<int, int> algebraic_2_numeric(char column, char row) noexcept {
		assert(column >= 'A' && column <= 'H');
		assert(row >= '1' && row <= '8');
		return { column - 'A', row - '1' };
	}

	[[nodiscard]] static auto algebraic_2_numeric(const std::string& input) noexcept {
		assert(input.length() <= 2);
		return algebraic_2_numeric(input.c_str()[0], input.c_str()[1]);
	}

	[[nodiscard]] static constexpr auto algebraic_2_numeric(std::pair<char, char> input) noexcept {
		return algebraic_2_numeric(input.first, input.second);
	}

	// index to/from algebraic

	[[nodiscard]] static constexpr auto algebraic_2_index(std::pair<char, char> input) noexcept {
		return numeric_2_index(algebraic_2_numeric(input));
	}
	
	[[nodiscard]] static constexpr auto algebraic_2_index(char column, char row) noexcept {
		return algebraic_2_index(std::pair<char, char>(column, row));
	}

	[[nodiscard]] static auto algebraic_2_index(const std::string& input) noexcept {
		assert(input.length() <= 2);
		return algebraic_2_index(input.c_str()[0], input.c_str()[1]);
	}

	[[nodiscard]] static constexpr auto index_2_algebraic(int index) noexcept {
		return numeric_2_algebraic(index_2_numeric(index));
	}

	// Accessors

	[[nodiscard]] constexpr auto& squares() noexcept { return m_squares; }
	[[nodiscard]] constexpr const auto& squares() const noexcept { return m_squares; }

	[[nodiscard]] constexpr const auto& square(int idx) const noexcept { return squares()[idx]; }
	[[nodiscard]] constexpr auto& square(int idx) noexcept { return squares()[idx]; }

	[[nodiscard]] constexpr const auto& square(int column, int row) const noexcept {
		return square(numeric_2_index(column, row));
	}

	[[nodiscard]] constexpr auto& square(int column, int row) noexcept {
		return square(numeric_2_index(column, row));
	}

	[[nodiscard]] constexpr const auto& square(std::pair<char, char> input) const noexcept {
		return square(algebraic_2_index(input));
	}
	
	[[nodiscard]] constexpr auto& square(std::pair<char, char> input) noexcept {
		return square(algebraic_2_index(input));
	}

	[[nodiscard]] constexpr const auto& square(const std::string& input) const noexcept {
		return square(algebraic_2_index(input));
	}
	
	[[nodiscard]] constexpr auto& square(const std::string& input) noexcept {
		return square(algebraic_2_index(input));
	}

	[[nodiscard]] constexpr auto& current_player() noexcept { return m_current_player; }
	[[nodiscard]] constexpr auto current_player() const noexcept { return m_current_player; }

	void clear_squares() noexcept;
	void swap_current_player() noexcept;

	[[nodiscard]] std::string representation() const;
	[[nodiscard]] static std::string representation(int idx);
	[[nodiscard]] static std::string representation(int column, int row);

	[[nodiscard]] static std::string representation(move_t move);
	[[nodiscard]] static std::string representation(const std::vector<move_t>& moves);

	[[nodiscard]] static std::string representation(piece_t::colour_t colour);

	void initialise() noexcept;

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

private:
	static void add(std::vector<move_t>& moves, int from, int to);
	static void add(std::vector<move_t>& moves, int from, int column, int row);

	bool maybe_add(std::vector<move_t>& moves, int from, int column, int row) const;
	bool maybe_add(std::vector<move_t>& moves, int from, int to) const;
};