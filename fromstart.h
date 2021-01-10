#pragma once
#include <set>
#include "point.h"

struct FromStart
{
	// in the set we save path from source to the points
	std::set<Point> points;
	int distance = INT_MAX;
};