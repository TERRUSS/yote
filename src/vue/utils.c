#include "utils.h"

/*
*	Convert an isometric point to cartesian
**/
Point isoToCart(Point pt) {

	Point tempPt;
	
	//changement de plan -3pi/4
	int x  = pt.x*cos(3*M_PI /4)-pt.y* sin(3*M_PI /4);
	int y = pt.x* sin(3*M_PI /4)+pt.y*cos(3*M_PI /4);

	//calcul des cases
	tempPt.x = (-(x + MARGE_TOP)/ (HIT_BOX_WIDTH+2))-6;
	tempPt.y = ((y  + MARGE_LEFT)/ (HIT_BOX_HEIGHT))-5;

	return tempPt;
}


/**
* Convert a catesian point to isometric
* */
Point cartToIso(Point pt) {
	Point tempPt;

	//calcul des coordonnées
  int x = -((pt.x * (HIT_BOX_WIDTH)) + MARGE_TOP);
	int y = -((pt.y * (HIT_BOX_HEIGHT)) + MARGE_LEFT);

	//changement de plan -3pi/4
	tempPt.x = x*cos(-3*M_PI /4)+y* sin(-3*M_PI /4);
	tempPt.y = -x* sin(-3*M_PI /4)+y*cos(-3*M_PI /4);

	return tempPt;
}
