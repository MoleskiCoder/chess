#pragma once

#include <string>

class piece_t final {
public:
	enum colour_t { BLACK, WHITE };
	enum type_t { ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN };

	static piece_t BlackRook;
	static piece_t BlackKnight;
	static piece_t BlackBishop;
	static piece_t BlackQueen;
	static piece_t BlackKing;
	static piece_t BlackPawn;

	static piece_t WhiteRook;
	static piece_t WhiteKnight;
	static piece_t WhiteBishop;
	static piece_t WhiteQueen;
	static piece_t WhiteKing;
	static piece_t WhitePawn;

private:
	colour_t m_colour;
	type_t m_type;
	std::string m_representation;

public:
	piece_t(colour_t colour, type_t type);

	auto colour() const { return m_colour; }
	auto piece() const { return m_colour; }
	const auto& representation() const { return m_representation; }
};

