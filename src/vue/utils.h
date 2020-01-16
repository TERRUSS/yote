#pragma once

typedef struct {
	int x;
	int y;
} Point;


#include <math.h>
#include "graphics.h"


Point cartToIso (Point pt);
Point isoToCart (Point pt);
Point getCellCoordinates(Point pt);
