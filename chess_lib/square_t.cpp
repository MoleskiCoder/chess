#include "pch.h"

#include "square_t.h"

square_t square_t::Empty;

square_t::square_t(piece_t piece) noexcept
: m_contents(piece) {}

std::string square_t::representation() const {
	return contents().has_value() ? contents()->representation() : std::string("    ");
}
