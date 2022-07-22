#include "Menu.h"
#include "World.h"

extern World world;

Menu::Menu()
{
}

Menu::~Menu()
{
	
}

void Menu::init()
{
	fstream stream;

	string tmp, img, exitBtnPath, playBtn, playBtnGlow;

	stream.open(CONFIG_FOLDER + MENU_FOLDER + "menu.txt");

	stream >> tmp >> img;
	stream >> tmp >> exitBtnPath;
	stream >> tmp >> playBtn;
	stream >> tmp >> playBtnGlow;
	stream >> tmp >> m_playBtn.rect.x >> m_playBtn.rect.y >> m_playBtn.rect.w >> m_playBtn.rect.h;
	
	stream.close();

	m_menuTexture = loadTexture(MENU_FOLDER + img);

	m_playBtn.texture = loadTexture(MENU_FOLDER + playBtn);
	m_playBtn.glowTexture = loadTexture(MENU_FOLDER + playBtnGlow);

	m_exitBtn.init(exitBtnPath, MENU_FOLDER);
}

void Menu::run()
{	
	drawObject(m_menuTexture);

	m_exitBtn.update();
	m_exitBtn.draw();

	if (isMouseInRect(m_exitBtn.getRect()) && mouseIsPressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::NONE);
	}

	if (isMouseInRect(m_playBtn.rect))
	{
		SDL_RenderCopy(world.m_presenter.m_main_renderer, m_playBtn.glowTexture, NULL, &m_playBtn.rect);

		if (mouseIsPressed())
		{
			//easy
			world.m_stateManager.changeGameState(GAME_STATE::GAME);
		}
	}
	else
	{
		SDL_RenderCopy(world.m_presenter.m_main_renderer, m_playBtn.texture, NULL, &m_playBtn.rect);
	}
}

void Menu::destroy()
{
	SDL_DestroyTexture(m_menuTexture);

	m_exitBtn.destroy(); 

	SDL_DestroyTexture(m_playBtn.texture);
	SDL_DestroyTexture(m_playBtn.glowTexture);
}