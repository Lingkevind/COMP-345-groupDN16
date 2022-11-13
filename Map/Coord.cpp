
#include "Coord.h"

Coord::Coord(int x, int y) :x(x), y(y) {}

Coord::Coord(const Coord& c) {
	x = c.x;
	y = c.y;
}

