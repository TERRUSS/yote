#include "utils.h"

/*
*	Convert an isometric point to cartesian
**/
Point isoToCart (Point pt) {
	//gx=(2*isoy+isox)/2;
	//gy=(2*isoy-isox)/2
	Point tempPt;

	tempPt.x=(2*pt.y+pt.x)/2;
	tempPt.y=(2*pt.y-pt.x)/2;

	return tempPt;
}


/**
* Convert a catesian point to isometric
* */
Point cartToIso (Point pt) {
	//gx=(isox-isoxy;
	//gy=(isoy+isox)/2
	Point tempPt;

	tempPt.x=pt.x-pt.y;
	tempPt.y=(pt.x+pt.y)/2;
	return tempPt;
}


/**
* Convert a cartesian point to specific tile row/column
* */
Point getTileCoordinates(Point pt, int cellHeight) {

	Point tempPt;

	tempPt.x = pt.x/cellHeight;
	tempPt.y = pt.y/cellWidth;

	return tempPt;
}
