#pragma once

#include <string>
#include <utility>
#include <array>

#include "square_t.h"
#include "piece_t.h"
#include "notation_t.h"

class board_t final {
private:
	std::array<square_t, 64> m_squares;
	piece_t::colour_t m_current_player = piece_t::WHITE;

public:
	constexpr board_t() noexcept {}

	// Accessors

	[[nodiscard]] constexpr auto& squares() noexcept { return m_squares; }
	[[nodiscard]] constexpr const auto& squares() const noexcept { return m_squares; }

	[[nodiscard]] constexpr const auto& square(int idx) const noexcept { return squares()[idx]; }
	[[nodiscard]] constexpr auto& square(int idx) noexcept { return squares()[idx]; }

	[[nodiscard]] constexpr const auto& square(int column, int row) const noexcept {
		return square(notation_t::numeric_2_index(column, row));
	}

	[[nodiscard]] constexpr auto& square(int column, int row) noexcept {
		return square(notation_t::numeric_2_index(column, row));
	}

	[[nodiscard]] constexpr const auto& square(const std::pair<char, char>& input) const noexcept {
		return square(notation_t::algebraic_2_index(input));
	}
	
	[[nodiscard]] constexpr auto& square(const std::pair<char, char>& input) noexcept {
		return square(notation_t::algebraic_2_index(input));
	}

	[[nodiscard]] constexpr const auto& square(const std::string& input) const noexcept {
		return square(notation_t::algebraic_2_index(input));
	}
	
	[[nodiscard]] constexpr auto& square(const std::string& input) noexcept {
		return square(notation_t::algebraic_2_index(input));
	}

	[[nodiscard]] constexpr auto& current_player() noexcept { return m_current_player; }
	[[nodiscard]] constexpr auto current_player() const noexcept { return m_current_player; }

	void clear_squares() noexcept;
	void swap_current_player() noexcept;

	[[nodiscard]] std::string representation() const;
	[[nodiscard]] static std::string representation(int idx);
	[[nodiscard]] static std::string representation(int column, int row);

	[[nodiscard]] static std::string representation(piece_t::colour_t colour);

	[[nodiscard]] constexpr bool operator==(const board_t& rhs) const noexcept {
		for (int i = 0; i < 8 * 8; ++i)
			if (square(i) != rhs.square(i))
				return false;
		return current_player() == rhs.current_player();
	}

	[[nodiscard]] constexpr bool operator!=(const board_t& rhs) const noexcept {
		return !(*this == rhs);
	}

	void initialise() noexcept;
};