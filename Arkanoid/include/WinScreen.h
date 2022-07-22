#pragma once

#include <fstream>

#include "defines.h"
#include "State.h"
#include "Button.h"

class WinScreen : public State
{
public:
	WinScreen();
	~WinScreen();

	void init();
	void run();
	void destroy();
	
private:
	SDL_Texture* m_background;
	
	Button m_exitBtn;

	DrawableForMenu m_playAgain;
};