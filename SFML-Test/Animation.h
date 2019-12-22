#pragma once
#include <SFML\Graphics.hpp>
#include <time.h>
#include "windows.h"
#include <list>
using namespace sf;
class Animation
{
public:
	const int W = 640;
	const int H = 480;
	float Frame, speed;
	Sprite sprite;
	std::vector<IntRect> frames;

	Animation();

	Animation(Texture &t, int x, int y, int w, int h, int count, float Speed);


	void update();

	bool isEnd();

};