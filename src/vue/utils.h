#pragma once

#include <math.h>

typedef struct {
	int x;
	int y;
} Point;

Point cartToIso (Point pt);
Point isoToCart (Point pt);
Point getCellCoordinates(Point pt, int tileHeight);
