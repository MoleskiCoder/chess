#include "pch.h"

#include "move_t.h"
#include "board_t.h"

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
