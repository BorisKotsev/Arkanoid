#pragma once

#include <map>
#include <fstream>
#include <math.h>

#include "Presenter.h"
#include "defines.h"
#include "Brick.h"
#include "Ball.h"
#include "Dropable.h"

class Board
{
public:
	Board();
	~Board();

	int m_lives;

	Brick m_brick;

	vector<Drawable> m_hearts;
	
	void load();

	void update();
	
	void draw();
	
	void collUpDown(SDL_Rect rect1, SDL_Rect rect2, int index);
	void collLeftRight(SDL_Rect rect1, SDL_Rect rect2, int index);
	
private:
	SDL_Texture* m_background;
	SDL_Texture* m_deadTexture;
	//SDL_Texture* m_hearthTmp;

	vector<Ball> m_balls;

	Dropable m_drops;
	Drawable m_space;
	Drawable m_spacePressed;

	vector<Dropable> m_allDrops;

	int m_speed;
	int m_offset;
	int m_mouseCounter;
	
	int2 dir;

	pair<SDL_Scancode, SDL_Scancode> m_direction;

	void loadHearts();
	void drawHearts();

	void removeHeart();
	void addHeart();
	void moveSpace();
	void updateDrops();
	void updateBricks();
	void removeBrick(int i, int j);

	bool m_isSpacePressed = false;
};