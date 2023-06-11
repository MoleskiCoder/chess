#pragma once

class move_t {
private:
	int m_from;
	int m_to;

public:
	move_t(int from, int to);

	auto from() const { return m_from; }
	auto to() const { return m_to; }
};

