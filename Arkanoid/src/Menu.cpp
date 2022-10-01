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

	string tmp, img, exitBtnPath, playBtnPath;

	stream.open(CONFIG_FOLDER + MENU_FOLDER + "menu.txt");

	stream >> tmp >> img;
	stream >> tmp >> exitBtnPath;
	stream >> tmp >> playBtnPath;
	
	stream.close();

	m_menuTexture = loadTexture(MENU_FOLDER + img);

	m_exitBtn.init(exitBtnPath, MENU_FOLDER);
	m_playBtn.init(playBtnPath, MENU_FOLDER);
}

void Menu::run()
{	
	drawObject(m_menuTexture);

	m_exitBtn.update();
	m_exitBtn.draw();

	m_playBtn.update();
	m_playBtn.draw();

	if (isMouseInRect(m_exitBtn.getRect()) && mouseIsPressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::NONE);
	}

	if (isMouseInRect(m_playBtn.getRect()) && mouseIsPressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::GAME);
	}	
}

void Menu::destroy()
{
	SDL_DestroyTexture(m_menuTexture);

	m_exitBtn.destroy(); 

	m_playBtn.destroy();
}