#include "include/dchess.hpp"

namespace dchess {
using Turn = Piece::Turn;
using TurnMap = Piece::TurnMap;

TurnMap::~TurnMap() {
	std::for_each(begin(), end(), [](Turn* t) {
		delete t;
	});
}

TurnMap::TurnMap(const TurnMap& t) : list(t) {
}

TurnMap::TurnMap(TurnMap&& t) : list(std::move(t)) {
	t.clear();
}

TurnMap& TurnMap::operator=(const TurnMap& t) {
	static_cast<list<Turn*>&>(*this) = 
		list<Turn*>(t);
	return *this;
}

TurnMap& TurnMap::operator=(TurnMap&& t) {
	static_cast<list<Turn*>&>(*this) = std::move(t);
	t.clear();
	return *this;
}
	

bool operator==(const TurnMap& lhs, const TurnMap& rhs) {
	auto lit = lhs.begin();
	auto rit = rhs.begin();

	while (lit != lhs.end() and rit != rhs.end()) {
		if (!(*lit)->isEqual(**rit))
			return false;
		lit++, rit++;
	}

	if (lit != lhs.end() or rit != rhs.end())
		return false;

	return true;
}

}
