#include "utils.h"

/*
*	Convert an isometric point to cartesian
**/
Point isoToCart(Point pt) {

	Point tempPt;

	tempPt.x = ((MARGE_LEFT+((pt.x) * cos(3*M_PI /4))) / 30)-3;
	tempPt.y = -(MARGE_TOP-((pt.y) * sin(3*M_PI /4)))/ 30;

	return tempPt;
}


/**
* Convert a catesian point to isometric
* */
Point cartToIso(Point pt) {
	//gx=(isox-isoxy;
	//gy=(isoy+isox)/2
	Point tempPt;

	// tempPt.x=pt.x-pt.y;
	// tempPt.y=(pt.x+pt.y)/2;

	//truc de maxime qui peu marcher mais faut tatoner
	// tempPt.x = MARGE_LEFT-( (pt.x / cos(3*M_PI /4))* 30 + (SPRITE_WIDTH/2)*pt.y);
	// tempPt.y = MARGE_TOP+( (pt.y / sin(3*M_PI /4))* 15 + (SPRITE_HEIGHT/2)*pt.x);

	tempPt.x = MARGE_LEFT + (pt.x+pt.y) * HIT_BOX_WIDTH;
	tempPt.y = MARGE_TOP - (pt.y-pt.x) * HIT_BOX_HEIGHT;




	//tempPt.x = MARGE_LEFT-(SPRITE_HEIGHT* pt.y /1.18- SPRITE_HEIGHT* pt.x /1.3 );
	//tempPt.y = MARGE_TOP+(SPRITE_WIDTH* pt.x /2.5 + pt.y*SPRITE_WIDTH/2.9);

	return tempPt;
}
