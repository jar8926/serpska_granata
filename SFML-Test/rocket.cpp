#include "rocket.h"
	rocket::rocket()
	{
		name = "rocket";
	}

	void  rocket::update()
	{

		dx = cos(angle*DEGTORAD) * 12;
		dy = sin(angle*DEGTORAD) * 12;
		// angle+=rand()%7-3;  /*try this*/
		x += dx;
		y += dy;

		//if (x > W || x<0 || y>H || y < 0) life = false;
	}
