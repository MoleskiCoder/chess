#include "pch.h"

#include "board_t.h"

TEST_CASE("XY position to vector index", "[xy_2_index]") {

	SECTION("Top/left corner of board") {
		auto index = board_t::xy_2_index(0, 0);
		REQUIRE(index == 0);
	}

	SECTION("Top/right corner of board") {
		auto index = board_t::xy_2_index(7, 0);
		REQUIRE(index == 7);
	}

	SECTION("Bottom/left corner of board") {
		auto index = board_t::xy_2_index(0, 7);
		REQUIRE(index == 7 * 8);
	}

	SECTION("Bottom/right corner of board") {
		auto index = board_t::xy_2_index(7, 7);
		REQUIRE(index == 8 * 8 - 1);
	}
}

TEST_CASE("Vector index to XY position", "[index_2_xy]") {

	SECTION("Top/left corner of board") {
		auto [x, y] = board_t::index_2_xy(0);
		REQUIRE(x == 0);
		REQUIRE(y == 0);
	}

	SECTION("Top/right corner of board") {
		auto [x, y] = board_t::index_2_xy(7);
		REQUIRE(x == 7);
		REQUIRE(y == 0);
	}

	SECTION("Bottom/left corner of board") {
		auto [x, y] = board_t::index_2_xy(7 * 8);
		REQUIRE(x == 0);
		REQUIRE(y == 7);
	}

	SECTION("Bottom/right corner of board") {
		auto [x, y] = board_t::index_2_xy(8 * 8 - 1);
		REQUIRE(x == 7);
		REQUIRE(y == 7);
	}
}
