#pragma once

#include <fstream>

#include "defines.h"

class Ball
{
public:
	Ball();
	~Ball();

	int2 m_speed;
	
	void init();
	void update();
	void draw();

	void collisionX(int2 percent);
	void collisionY(int2 percent);
		
	Drawable m_ball;

	float2 m_direction;

	int m_dmg;
};