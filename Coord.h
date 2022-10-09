#pragma once

#include <iostream>
#include <ostream>

struct Coord {
	public:
		/**
		* Construct the Coord object
		*
		* @param x x coordinates.
		* @param y x coordinates.
		*/
		Coord(int x, int y);
		int x;
		int y;
};
