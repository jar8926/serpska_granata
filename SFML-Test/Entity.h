#pragma once
#include "Animation.h"
class Entity
{
public:
	float DEGTORAD = 0.017453f;
	float x, y, dx, dy, R, angle;
	bool life;
	std::string name;
	Animation anim;

	Entity();

	void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1);
	virtual void update() ;

	void draw(RenderWindow &app);

	virtual ~Entity() ;
};
