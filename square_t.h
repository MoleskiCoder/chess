#pragma once

#include <optional>

#include "piece_t.h"

class square_t final {
public:
	static square_t Empty;

private:
	std::optional<piece_t> m_contents;

public:
	square_t();
	square_t(piece_t piece);

	auto& contents() { return m_contents; }
	const auto& contents() const { return m_contents; }

	std::string representation() const;
};

