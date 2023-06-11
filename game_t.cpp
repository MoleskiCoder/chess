#include "game_t.h"

#include <sstream>

void game_t::initialise() {
	board().initialise();
}

std::string game_t::representation() const {
	std::ostringstream oss;
	oss << board().representaton() << std::endl;
	return oss.str();
}
