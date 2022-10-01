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

	string tmp, background, exitBtnPath, playAgain, playAgainGlow;

	stream.open(CONFIG_FOLDER + WIN_SCREEN_FOLDER + "winScreen.txt");

	stream >> tmp >> background;
	stream >> tmp >> exitBtnPath;
	stream >> tmp >> playAgain >> playAgainGlow;
	stream >> tmp >> m_playAgain.rect.x >> m_playAgain.rect.y >> m_playAgain.rect.w >> m_playAgain.rect.h;
	
	stream.close();

	m_background = loadTexture(WIN_SCREEN_FOLDER + background);

	m_playAgain.texture = loadTexture(WIN_SCREEN_FOLDER + playAgain);
	//m_playAgain.glowTexture = loadTexture(WIN_SCREEN_FOLDER + playAgainGlow);

	m_exitBtn.init(exitBtnPath, MENU_FOLDER);
}

void WinScreen::run()
{	
	drawObject(m_background);

	m_exitBtn.update();
	m_exitBtn.draw();
	
	if (isMouseInRect(m_playAgain.rect))
	{
		//SDL_RenderCopy(world.m_presenter.m_main_renderer, m_playAgain.glowTexture, NULL, &m_playAgain.rect);

		if (mouseIsPressed())
		{			
			world.m_stateManager.changeGameState(GAME_STATE::MENU);

			return;
		}
	}
	else
	{
		SDL_RenderCopy(world.m_presenter.m_main_renderer, m_playAgain.texture, NULL, &m_playAgain.rect);
	}
	
	if (mouseIsPressed())
	{
		if (isMouseInRect(m_exitBtn.getRect()))
		{
			world.m_stateManager.changeGameState(GAME_STATE::NONE);

			return;
		}
	}
}

void WinScreen::destroy()
{
	m_exitBtn.destroy();
}
