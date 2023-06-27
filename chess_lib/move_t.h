#pragma once

#include <utility>
#include <string>

class move_t final {
private:
	int m_from;
	int m_to;

public:
	move_t(int from, int to) noexcept;
	move_t(const std::pair<char, char>& from, const std::pair<char, char>& to) noexcept;
	move_t(const std::string& from, const std::string& to) noexcept;

	[[nodiscard]] constexpr auto from() const noexcept { return m_from; }
	[[nodiscard]] constexpr auto to() const noexcept { return m_to; }

	[[nodiscard]] constexpr bool operator==(const move_t& rhs) const noexcept {
		return (from() == rhs.from()) && (to() == rhs.to());
	}
};
