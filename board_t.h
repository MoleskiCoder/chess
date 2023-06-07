#pragma once

#include <vector>
#include <string>

#include "square_t.h"

class board_t final {
private:
	std::vector<square_t> m_squares;

public:
	board_t();

	auto& squares() { return m_squares; }
	const auto& squares() const { return m_squares; }

	const auto& square(size_t idx) const { return squares().at(idx); }
	auto& square(size_t idx) { return squares().at(idx); }

	const auto& square(int x, int y) const { return square(y * 8 + x); }
	auto& square(int x, int y) { return square(y * 8 + x); }

	std::string representaton() const;

	void initialise();
	void show() const;
};