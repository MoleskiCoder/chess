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
	
	constexpr square_t(piece_t piece) noexcept
	: m_contents(piece) {}

	[[nodiscard]] constexpr auto& contents() noexcept { return m_contents; }
	[[nodiscard]] constexpr const auto& contents() const noexcept { return m_contents; }

	[[nodiscard]] constexpr bool operator==(const square_t& rhs) const noexcept {

		const auto& lhs_contents = contents();
		const auto& rhs_contents = rhs.contents();

		const auto lhs_has_value = lhs_contents.has_value();
		const auto rhs_has_value = rhs_contents.has_value();

		if (!lhs_has_value && !rhs_has_value)
			return true;

		if (lhs_has_value != rhs_has_value)
			return false;

		return lhs_contents.value() == rhs_contents.value();
	}

	[[nodiscard]] constexpr bool operator!=(const square_t& rhs) const noexcept {
		return !(*this == rhs);
	}

	[[nodiscard]] std::string representation() const;
};

