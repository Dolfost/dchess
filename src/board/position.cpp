#include <tartan/board.hpp>

#include <iostream>
#include <stdexcept>
#include <algorithm>

using std::out_of_range;
using std::invalid_argument;

#include<string>
using std::string;
using std::to_string;

namespace tt {
using Position = Piece::Position;

Position::Position(int x, int y) {
	setX(x);
	setY(y);
}

Position::Position(char l, int d) {
	setLetter(l);
	setDigit(d);
}

Position::Position(const string& s) {
	if (s.length() != 2)
		throw invalid_argument("Could not get position from string.");
	string str = s;
	std::transform(s.begin(), s.end(), str.begin(), [](unsigned char c) { 
		return std::tolower(c); }
	);

	setLetter(str[0]);
	setDigit(str[1] - '1' + 1);
}

int Position::setX(int x) {
	if (x < 1 or x >  8) {
		throw out_of_range(
			string("Chess piece x position can't be ") + 
			to_string(x) + ".");
	}

	short ret = p_x;
	p_x = x;

	return ret;
}

int Position::setY(int y) {
	if (y < 1 or y >  8) {
		throw out_of_range(
			string("Chess piece y position can't be ") + 
			to_string(y) + ".");
	}

	short ret = p_y;
	p_y = y;

	return ret;
}

Position Position::offset(int ox, int oy) const {
	int k = static_cast<int>(p_mode);
	Position ret = {p_x + k*ox, p_y + k*oy};
	ret.p_mode = p_mode;
	return ret;
}

Position Position::offset(char ol, int od) const {
	return offset(ol - 'a' + 1, od);
}

bool Position::atLeft() const {
	if (p_mode == Mode::Normal)
		return p_x == 1;
	else
		return p_x == 8;
}

bool Position::atRight() const {
	if (p_mode == Mode::Normal)
		return p_x == 8;
	else
		return p_x == 1;
}

bool Position::atTop() const {
	if (p_mode == Mode::Normal)
		return p_y == 8;
	else
		return p_y == 1;
}

bool Position::atBottom() const {
	if (p_mode == Mode::Normal)
		return p_y == 1;
	else
		return p_y == 8;
}

Position::Mode Position::setMode(Position::Mode m) { 
	Position::Mode r = p_mode; 
	p_mode = m; 
	return r; 
};

Position::Position(const Position& other) {
	p_x = other.p_x;
	p_y = other.p_y;
}

std::string Position::str() const {
	std::string s;
	s.push_back(letter());
	s.append(to_string(digit()));
	return s;
}

Position& Position::operator=(const Position& other) {
	p_x = other.p_x;
	p_y = other.p_y;
	return *this;
}

Position Position::operator+(const Position& p) const {
	return Position(p_x + p.p_x, p_y + p.p_y);
}

Position Position::operator-(const Position& p) const {
	return Position(p_x - p.p_x, p_y - p.p_y);
}

Position Position::operator+=(const Position& p) {
	return *this + p;
}

Position Position::operator-=(const Position& p) {
	return *this - p;
}

Position Position::operator()(int x, int y) const {
	return offset(x, y);
}

Position Position::operator()(char l, int d) const {
	return offset(l, d);
}

bool operator==(const Position& lhs, const Position& rhs) {
	return ((lhs.p_x == rhs.p_x) and (lhs.p_y == rhs.p_y));
}

std::ostream& operator<<(std::ostream& os, const Position& p) {
	return os << p.str();
}

}
