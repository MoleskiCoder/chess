#pragma once

#include <string>

#include "board_t.h"
#include "generator_t.h"

class game_t final {
private:
	board_t m_board;
	generator_t m_generator{ m_board };

public:
	[[nodiscard]] constexpr const auto& board() const noexcept { return m_board; }
	[[nodiscard]] constexpr auto& board() noexcept { return m_board; }

	[[nodiscard]] constexpr const auto& generator() const noexcept { return m_generator; }

	void initialise();

	[[nodiscard]] std::string representation() const;
};

