#pragma once

#include <cassert>
#include <utility>
#include <string>
#include <array>

class notation_t {
private:
	static std::array<int, 8> _reverse_row;

public:

	// X/Y to/from index

	[[nodiscard]] static constexpr auto xy_2_index(int x, int y) noexcept {
		assert(x >= 0 && x <= 7 && "x is out of range");
		assert(y >= 0 && y <= 7 && "y is out of range");
		return y * 8 + x;
	}

	[[nodiscard]] static constexpr std::pair<int, int> index_2_xy(int i) noexcept {
		assert(i >= 0 && i <= 63 && "i is out of range");
		return { i % 8, i / 8 };
	}

	// numeric to/from index

	[[nodiscard]] static constexpr std::pair<int, int> index_2_numeric(int i) noexcept {
		const auto [x, y] = index_2_xy(i);
		return { x, _reverse_row[y] };
	}

	[[nodiscard]] static constexpr auto numeric_2_index(int column, int row) noexcept {
		assert(row >= 0 && row <= 7 && "row is out of range");
		return xy_2_index(column, _reverse_row[row]);
	}

	[[nodiscard]] static constexpr auto numeric_2_index(const std::pair<int, int>& input) noexcept {
		return numeric_2_index(input.first, input.second);
	}

	// numeric to/from algebraic

	[[nodiscard]] static constexpr std::pair<char, char> numeric_2_algebraic(int column, int row) noexcept {
		assert(column >= 0 && column <= 7);
		assert(row >= 0 && row <= 7);
		return { static_cast<char>('A' + column), static_cast<char>('1' + row) };
	}

	[[nodiscard]] static constexpr auto numeric_2_algebraic(const std::pair<int, int>& input) noexcept {
		return numeric_2_algebraic(input.first, input.second);
	}

	[[nodiscard]] static constexpr std::pair<int, int> algebraic_2_numeric(char column, char row) noexcept {
		assert(column >= 'A' && column <= 'H');
		assert(row >= '1' && row <= '8');
		return { column - 'A', row - '1' };
	}

	[[nodiscard]] static auto algebraic_2_numeric(const std::string& input) noexcept {
		assert(input.length() <= 2);
		return algebraic_2_numeric(input.c_str()[0], input.c_str()[1]);
	}

	[[nodiscard]] static constexpr auto algebraic_2_numeric(const std::pair<char, char>& input) noexcept {
		return algebraic_2_numeric(input.first, input.second);
	}

	// index to/from algebraic

	[[nodiscard]] static constexpr auto algebraic_2_index(const std::pair<char, char>& input) noexcept {
		return numeric_2_index(algebraic_2_numeric(input));
	}

	[[nodiscard]] static constexpr auto algebraic_2_index(char column, char row) noexcept {
		return algebraic_2_index(std::pair<char, char>(column, row));
	}

	[[nodiscard]] static constexpr auto algebraic_2_index(const std::string& input) noexcept {
		return algebraic_2_index(input.c_str()[0], input.c_str()[1]);
	}

	[[nodiscard]] static constexpr auto index_2_algebraic(int index) noexcept {
		return numeric_2_algebraic(index_2_numeric(index));
	}
};

