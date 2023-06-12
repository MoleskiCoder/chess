#pragma once

#include <vector>
#include <string>
#include <utility>

#include "square_t.h"
#include "move_t.h"
#include "piece_t.h"

class board_t final {
private:
	std::vector<square_t> m_squares;
	piece_t::colour_t m_current_player = piece_t::WHITE;


public:
	board_t();

	static auto xy_2_index(int x, int y) { return y * 8 + x; }
	static std::pair<int, int> index_2_xy(int i) { return { i % 8, i / 8 }; }

	static std::pair<int, int> index_2_numeric(int i) {
		const auto [x, y] = index_2_xy(i);
		static std::vector<int> y_translation = { 7, 6, 5, 4, 3, 2, 1, 0 };
		return { x, y_translation[y] };
	}

	static int numeric_2_index(int column, int row) {
		static std::vector<int> row_translation = { 7, 6, 5, 4, 3, 2, 1, 0 };
		return xy_2_index(column, row_translation[row]);
	}

	static auto numeric_2_index(std::pair<int, int> input) { return numeric_2_index(input.first, input.second); }

	static std::pair<char, char> numeric_2_algebraic(int column, int row) {
	}

	static auto numeric_2_algebraic(std::pair<int, int> input) { return numeric_2_algebraic(input.first, input.second); }

	static std::pair<int, int> algebraic_2_numeric(char column, char row) {
	}

	static auto algebraic_2_numeric(std::pair<char, char> input) { return algebraic_2_numeric(input.first, input.second); }

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