#include "point.h"

Point::Point(const Point& p) {
	this->col = p.col;
	this->row = p.row;
}

Point::Point(int _row, int _col) {
	this->row = _row;
	this->col = _col;
}

Point::Point() {}

bool Point::operator<(const Point& p) const {
	return this->row < p.row || (!(this->row < p.row) && this->col < p.col);
}