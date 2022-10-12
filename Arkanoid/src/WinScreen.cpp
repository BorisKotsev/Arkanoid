#include "WinScreen.h"
#include "World.h"

extern World world;

WinScreen::WinScreen()
{

}

WinScreen::~WinScreen()
{
	
}

void WinScreen::init()
{
	fstream stream;

	string tmp, background, exitBtnPath, playAgainBtnPath;

	stream.open(CONFIG_FOLDER + WIN_SCREEN_FOLDER + "winScreen.txt");

	stream >> tmp >> background;
	stream >> tmp >> exitBtnPath;
	stream >> tmp >> playAgainBtnPath;

	stream.close();

	m_background = loadTexture(WIN_SCREEN_FOLDER + background);

	m_playAgainBtn.init(playAgainBtnPath, MENU_FOLDER);
	m_exitBtn.init(exitBtnPath, MENU_FOLDER);
}

void WinScreen::run()
{	
	drawObject(m_background);

	m_exitBtn.update();
	m_exitBtn.draw();

	m_playAgainBtn.update();
	m_playAgainBtn.draw();

	auto score = getText(to_string(world.m_stateManager.m_game->m_board.m_brick.m_counter),
		FONT::CINZEL, COLOR::LIGHT, 128);

	m_score.texture = score.second;

	m_score.rect = { 1130, 226, score.first.x, score.first.y };

	drawObject(m_score);
	
	if (mouseIsPressed())
	{
		if (isMouseInRect(m_exitBtn.getRect()))
		{
			world.m_stateManager.changeGameState(GAME_STATE::NONE);

			return;
		}

		if (isMouseInRect(m_playAgainBtn.getRect()))
		{
			world.m_stateManager.changeGameState(GAME_STATE::MENU);

			return;
		}
	}
}

void WinScreen::destroy()
{
	m_exitBtn.destroy();
}
