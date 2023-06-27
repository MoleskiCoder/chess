#pragma once

#include <string>

#include "board_t.h"

class game_t final {
private:
	board_t m_board;

public:
	[[nodiscard]] constexpr const auto& board() const noexcept { return m_board; }
	[[nodiscard]] constexpr auto& board() noexcept { return m_board; }

	void initialise();

	[[nodiscard]] std::string representation() const;
};

