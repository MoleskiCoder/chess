#include "pch.h"

#include "move_t.h"
#include "board_t.h"

move_t::move_t(int from, int to) noexcept
: m_from(from), m_to(to) {}

move_t::move_t(const std::pair<char, char>& from, const std::pair<char, char>& to) noexcept
: m_from(board_t::algebraic_2_index(from)),
  m_to(board_t::algebraic_2_index(to)) {}
