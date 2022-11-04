#pragma once

#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "Engine.h"
#include "defines.h"

const int m_ROWS = 9; 
const int m_COLS = 17;

class Brick
{
public:
	Brick();
	~Brick();

	void init();
	void draw();
	
	BrickData m_allBricks [m_ROWS][m_COLS];
		
	int m_counter;

private:
	SDL_Texture* m_oneHp;
	SDL_Texture* m_twoHp;
	SDL_Texture* m_threeHp;
};