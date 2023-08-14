#pragma once

#include <utility>
#include <string>
#include <vector>

#include "notation_t.h"

class move_t final {
private:
	int m_from;
	int m_to;

public:
	[[nodiscard]] static auto find_move(const std::vector<move_t>& moves, const move_t& move) {
		return std::find(moves.begin(), moves.end(), move);
	}

	[[nodiscard]] static auto has_move(const std::vector<move_t>& moves, const move_t& move) {
		return find_move(moves, move) != moves.end();
	}

	constexpr move_t(int from, int to) noexcept
	: m_from(from), m_to(to) {}

	constexpr move_t(const std::pair<char, char>& from, const std::pair<char, char>& to) noexcept
	: m_from(notation_t::algebraic_2_index(from)),
	  m_to(notation_t::algebraic_2_index(to)) {}

	constexpr move_t(const std::string& from, const std::string& to) noexcept
	: m_from(notation_t::algebraic_2_index(from)),
	  m_to(notation_t::algebraic_2_index(to)) {}

	[[nodiscard]] constexpr auto from() const noexcept { return m_from; }
	[[nodiscard]] constexpr auto to() const noexcept { return m_to; }

	[[nodiscard]] constexpr bool operator==(const move_t& rhs) const noexcept {
		return (from() == rhs.from()) && (to() == rhs.to());
	}

	[[nodiscard]] auto find_move(const std::vector<move_t>& moves) {
		return find_move(moves, *this);
	}

	[[nodiscard]] auto has_move(const std::vector<move_t>& moves) {
		return has_move(moves, *this);
	}

	[[nodiscard]] std::string representation() const;
	[[nodiscard]] static std::string representation(const std::vector<move_t>& moves);
};
