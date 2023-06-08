#pragma once

#include <vector>
#include <string>
#include <utility>

#include "square_t.h"
#include "move_t.h"

class board_t final {
private:
	std::vector<square_t> m_squares;
	piece_t::colour_t m_current_player = piece_t::WHITE;

public:
	board_t();

	static auto xy2index(int x, int y) { return y * 8 + x; }
	static std::pair<int, int> index2xy(int i) { return { i % 8, i / 8 }; }

	auto& squares() { return m_squares; }
	const auto& squares() const { return m_squares; }

	const auto& square(int idx) const { return squares().at(idx); }
	auto& square(int idx) { return squares().at(idx); }

	const auto& square(int x, int y) const { return square(xy2index(x, y)); }
	auto& square(int x, int y) { return square(xy2index(x, y)); }

	auto& current_player() { return m_current_player; }
	auto current_player() const { return m_current_player; }

	void swap_current_player();

	std::string representaton() const;
	static std::string representation(int idx);
	static std::string representation(int x, int y);

	static std::string representation(move_t move);
	static std::string representation(std::vector<move_t> moves);

	void initialise();

	std::vector<move_t> generate_moves(int idx, piece_t piece) const;
	std::vector<move_t> generate_moves(int idx, piece_t::colour_t colour) const;
	std::vector<move_t> generate_moves(piece_t::colour_t colour) const;
	std::vector<move_t> generate_moves() const;
};