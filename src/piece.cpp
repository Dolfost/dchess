#include "include/dchess.hpp"

namespace dchess {
	using Position = Piece::Position;

	inline Piece::Piece(const Position&  p, const Color& c, Chessboard& cb) : p_chessboard(cb) { 
		p_position = p; 
		p_color = c; 
	};

	inline Position Piece::move(const Position& p) {
		Position ret = p_position;
		p_position = p;
		p_moveHistory.push_back(p);
		return ret;
	}

}