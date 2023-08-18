#pragma once

#include <vector>

#include "move_t.h"
#include "piece_t.h"

class generator_t;

class queen_generator_t final {
private:
	const generator_t& m_generator;

public:
	queen_generator_t(const generator_t& generator) noexcept;

	[[nodiscard]] constexpr const auto& generator() const noexcept { return m_generator; }

	[[nodiscard]] std::vector<move_t> generate(int from, piece_t::colour_t colour) const;
	[[nodiscard]] std::vector<move_t> generate(const std::string& from, piece_t::colour_t colour) const;
};
