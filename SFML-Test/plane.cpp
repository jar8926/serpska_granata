#include "plane.h"
	plane::plane()
	{
		dx = rand() % 2 + 4;
		name = "plane";
	}
	void plane::update()
	{
		x -= dx;

		if (x > W) x = 0;  if (x < 0) x = W;
	}
