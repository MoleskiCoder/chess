#pragma once

#include <string>

#include "board_t.h"

class game_t {
private:
	board_t m_board;

public:
	const auto& board() const { return m_board; }
	auto& board() { return m_board; }

	void initialise();

	std::string representation() const;
};

