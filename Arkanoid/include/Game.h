#pragma once

#include <fstream>

#include "State.h"
#include "Board.h"
#include "ConfigManager.h"

class Game : public State
{
public:

	Game();
	~Game();

	Board m_board;
		
	void init();
	void destroy();
	void run();
};