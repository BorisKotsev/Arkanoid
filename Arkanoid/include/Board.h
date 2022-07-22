#pragma once

#include <map>
#include <fstream>

#include "Presenter.h"
#include "defines.h"

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
	
};