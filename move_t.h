#pragma once

class move_t {
private:
	size_t m_from;
	size_t m_to;

public:
	move_t(size_t from, size_t to);

	auto from() const { return m_from; }
	auto to() const { return m_to; }
};

