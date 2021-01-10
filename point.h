#pragma once
struct Point
{
	int row = 0;
	int col = 0;
	Point(const Point& p);
	Point(int _row, int _col);
	Point();
	bool operator<(const Point& p) const;
};