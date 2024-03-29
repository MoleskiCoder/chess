#include "pch.h"

#include "game_t.h"

void game_t::initialise() {
	board().initialise();
}

std::string game_t::representation() const {
	std::ostringstream oss;
	oss << board().representation() << std::endl;
	return oss.str();
}
