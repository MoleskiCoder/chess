#include "pch.h"

#include "piece_t.h"

piece_t piece_t::BlackRook = { BLACK, ROOK };
piece_t piece_t::BlackKnight = { BLACK, KNIGHT };
piece_t piece_t::BlackBishop = { BLACK, BISHOP };
piece_t piece_t::BlackQueen = { BLACK, QUEEN };
piece_t piece_t::BlackKing = { BLACK, KING };
piece_t piece_t::BlackPawn = { BLACK, PAWN };

piece_t piece_t::WhiteRook = { WHITE, ROOK };
piece_t piece_t::WhiteKnight = { WHITE, KNIGHT };
piece_t piece_t::WhiteBishop = { WHITE, BISHOP };
piece_t piece_t::WhiteQueen = { WHITE, QUEEN };
piece_t piece_t::WhiteKing = { WHITE, KING };
piece_t piece_t::WhitePawn = { WHITE, PAWN };

piece_t::piece_t(colour_t colour, type_t type)
: m_colour(colour),
  m_type(type) {
	m_representation = " ";
	m_representation += m_colour == piece_t::WHITE ? "W" : "B";
	switch (type) {
	case piece_t::ROOK:
		m_representation += "R";
		break;
	case piece_t::KNIGHT:
		m_representation += "N";
		break;
	case piece_t::BISHOP:
		m_representation += "B";
		break;
	case piece_t::QUEEN:
		m_representation += "Q";
		break;
	case piece_t::KING:
		m_representation += "K";
		break;
	case piece_t::PAWN:
		m_representation += "P";
		break;
	}
	m_representation += " ";
}

