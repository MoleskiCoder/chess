#include "pch.h"

#include "chess.h"

// XY positions

TEST_CASE("XY position to vector index", "[xy_2_index]") {

	SECTION("Top/left corner of board") {
		constexpr auto index = notation_t::xy_2_index(0, 0);
		REQUIRE(index == 0);
	}

	SECTION("Top/right corner of board") {
		constexpr auto index = notation_t::xy_2_index(7, 0);
		REQUIRE(index == 7);
	}

	SECTION("Bottom/left corner of board") {
		constexpr auto index = notation_t::xy_2_index(0, 7);
		REQUIRE(index == 7 * 8);
	}

	SECTION("Bottom/right corner of board") {
		constexpr auto index = notation_t::xy_2_index(7, 7);
		REQUIRE(index == 8 * 8 - 1);
	}
}

TEST_CASE("Vector index to XY position", "[index_2_xy]") {

	SECTION("Top/left corner of board") {
		const auto [x, y] = notation_t::index_2_xy(0);
		REQUIRE(x == 0);
		REQUIRE(y == 0);
	}

	SECTION("Top/right corner of board") {
		const auto [x, y] = notation_t::index_2_xy(7);
		REQUIRE(x == 7);
		REQUIRE(y == 0);
	}

	SECTION("Bottom/left corner of board") {
		const auto [x, y] = notation_t::index_2_xy(7 * 8);
		REQUIRE(x == 0);
		REQUIRE(y == 7);
	}

	SECTION("Bottom/right corner of board") {
		const auto [x, y] = notation_t::index_2_xy(8 * 8 - 1);
		REQUIRE(x == 7);
		REQUIRE(y == 7);
	}
}

// Numeric positions (reversed row)

TEST_CASE("Numeric position to vector index", "[numeric_2_index]") {

	SECTION("Bottom/left corner of board") {
		const auto index = notation_t::numeric_2_index({ 0, 0 });
		REQUIRE(index == notation_t::xy_2_index(0, 7));
	}

	SECTION("Bottom/right corner of board") {
		const auto index = notation_t::numeric_2_index({ 7, 0 });
		REQUIRE(index == notation_t::xy_2_index(7, 7));
	}

	SECTION("Top/left corner of board") {
		const auto index = notation_t::numeric_2_index({ 0, 7 });
		REQUIRE(index == notation_t::xy_2_index(0, 0));
	}

	SECTION("Top/right corner of board") {
		const auto index = notation_t::numeric_2_index({ 7, 7 });
		REQUIRE(index == notation_t::xy_2_index(7, 0));
	}
}

TEST_CASE("Vector index to Numeric position", "[index_2_numeric]") {

	SECTION("Top/left corner of board") {
		const auto [column, row] = notation_t::index_2_numeric(0);
		REQUIRE(column == 0);
		REQUIRE(row == 7);
	}

	SECTION("Top/right corner of board") {
		const auto [column, row] = notation_t::index_2_numeric(7);
		REQUIRE(column == 7);
		REQUIRE(row == 7);
	}

	SECTION("Bottom/left corner of board") {
		const auto [column, row] = notation_t::index_2_numeric(7 * 8);
		REQUIRE(column == 0);
		REQUIRE(row == 0);
	}

	SECTION("Bottom/right corner of board") {
		const auto [column, row] = notation_t::index_2_numeric(8 * 8 - 1);
		REQUIRE(column == 7);
		REQUIRE(row == 0);
	}
}

// Algebraic positions ('char' versions of numeric)

TEST_CASE("Algebraic position to vector index", "[algebraic_2_index]") {

	SECTION("Bottom/left corner of board") {
		const auto index = notation_t::algebraic_2_index("A1");
		REQUIRE(index == notation_t::xy_2_index(0, 7));
	}

	SECTION("Bottom/right corner of board") {
		const auto index = notation_t::algebraic_2_index("H1");
		REQUIRE(index == notation_t::xy_2_index(7, 7));
	}

	SECTION("Top/left corner of board") {
		const auto index = notation_t::algebraic_2_index("A8");
		REQUIRE(index == notation_t::xy_2_index(0, 0));
	}

	SECTION("Top/right corner of board") {
		const auto index = notation_t::algebraic_2_index("H8");
		REQUIRE(index == notation_t::xy_2_index(7, 0));
	}
}

TEST_CASE("Vector index to algebraic position", "[index_2_algebraic]") {

	SECTION("Top/left corner of board") {
		const auto [column, row] = notation_t::index_2_algebraic(0);
		REQUIRE(column == 'A');
		REQUIRE(row == '8');
	}

	SECTION("Top/right corner of board") {
		const auto [column, row] = notation_t::index_2_algebraic(7);
		REQUIRE(column == 'H');
		REQUIRE(row == '8');
	}

	SECTION("Bottom/left corner of board") {
		const auto [column, row] = notation_t::index_2_algebraic(7 * 8);
		REQUIRE(column == 'A');
		REQUIRE(row == '1');
	}

	SECTION("Bottom/right corner of board") {
		const auto [column, row] = notation_t::index_2_algebraic(8 * 8 - 1);
		REQUIRE(column == 'H');
		REQUIRE(row == '1');
	}
}
