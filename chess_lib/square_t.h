#pragma once

#include <optional>

#include "piece_t.h"

class square_t final {
public:
	static square_t Empty;

private:
	std::optional<piece_t> m_contents;

public:
	constexpr square_t() noexcept {}
	square_t(piece_t piece) noexcept;

	[[nodiscard]] constexpr auto& contents() noexcept { return m_contents; }
	[[nodiscard]] constexpr const auto& contents() const noexcept { return m_contents; }

	[[nodiscard]] std::string representation() const;
};

