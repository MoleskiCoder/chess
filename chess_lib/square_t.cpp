#include "pch.h"

#include "square_t.h"

square_t square_t::Empty;

std::string square_t::representation() const {
	return contents().has_value() ? contents()->representation() : std::string("    ");
}
