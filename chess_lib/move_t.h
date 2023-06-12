#pragma once

class move_t final {
private:
	int m_from;
	int m_to;

public:
	move_t(int from, int to) noexcept;

	constexpr auto from() const noexcept { return m_from; }
	constexpr auto to() const noexcept { return m_to; }
};

