#pragma once

#include <map>
#include <fstream>
#include <math.h>

#include "Presenter.h"
#include "defines.h"
#include "Brick.h"
#include "Ball.h"

class Board
{
public:
	Board();
	~Board();
	
	void load();

	void update();
	
	void draw();
	
	void destroy();

	void collUpDown(SDL_Rect rect1, SDL_Rect rect2);
	void collLeftRight(SDL_Rect rect1, SDL_Rect rect2);
	
private:
	SDL_Texture* m_background;

	Brick m_brick;

	Ball m_ball;

	Drawable m_space;

	int m_speed;

	pair<SDL_Scancode, SDL_Scancode> m_direction;
};