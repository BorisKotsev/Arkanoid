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

	void collisionX();
	void collisionY();
		
	Drawable m_ball;

	SDL_Texture* m_megaTxt;

	float2 m_direction;

	int m_dmg;

	bool m_moveDown;
};