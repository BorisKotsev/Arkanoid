#pragma once

#include <map>
#include <fstream>

#include "Presenter.h"
#include "defines.h"
#include "Brick.h"

class Board
{
public:
	Board();
	~Board();
	
	void load();

	void update();
	
	void draw();
	
	void destroy();
	
private:
	SDL_Texture* m_background;

	Brick m_brick;

	Drawable m_space;

	Drawable m_ball;

	int m_speed;

	pair<SDL_Scancode, SDL_Scancode> m_direction;
};