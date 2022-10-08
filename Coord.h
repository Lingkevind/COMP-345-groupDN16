#pragma once

#include <iostream>
#include <ostream>

struct Coord {
	public:
		Coord(int x, int y);
		int x;
		int y;
};

// free operator declaration
ostream& operator<<(ostream& os, const Coord& coord);
