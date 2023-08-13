#include "pch.h"

#include "move_t.h"
#include "board_t.h"

move_t::move_t(int from, int to) noexcept
: m_from(from), m_to(to) {}

move_t::move_t(const std::pair<char, char>& from, const std::pair<char, char>& to) noexcept
: m_from(board_t::algebraic_2_index(from)),
  m_to(board_t::algebraic_2_index(to)) {}

move_t::move_t(const std::string& from, const std::string& to) noexcept
: m_from(board_t::algebraic_2_index(from)),
  m_to(board_t::algebraic_2_index(to)) {}

std::string move_t::representation() const {
	std::ostringstream oss;
	oss << "From: " << board_t::representation(from()) << ", To: " << board_t::representation(to());
	return oss.str();
}

std::string move_t::representation(const std::vector<move_t>& moves) {
	std::ostringstream oss;
	for (const auto& move : moves)
		oss << move.representation() << std::endl;
	return oss.str();
}
