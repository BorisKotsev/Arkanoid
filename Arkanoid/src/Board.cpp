#include "Board.h"
#include "Presenter.h"
#include "InputManager.h"

Board::Board()
{
}

Board::~Board()
{
}

void Board::load()
{
	fstream stream;

	string tmp, background, img, ballImg;

	int2 dir;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "board.txt");

	stream >> tmp >> background;
	stream >> tmp >> dir.x >> dir.y;
	stream >> tmp >> m_space.rect.x >> m_space.rect.y >> m_space.rect.w >> m_space.rect.h;
	stream >> tmp >> img;
	stream >> tmp >> m_speed;
	stream >> tmp >> m_ball.rect.x >> m_ball.rect.y >> m_ball.rect.w >> m_ball.rect.h;
	stream >> tmp >> ballImg;

	stream.close();
	
	m_background = loadTexture(GAME_FOLDER + background);

	m_direction.first = (SDL_Scancode)dir.x; // Right
	m_direction.second = (SDL_Scancode)dir.y; // Left

	m_space.texture = loadTexture(GAME_FOLDER + img);
	m_ball.texture = loadTexture(GAME_FOLDER + ballImg);

	m_brick.init();
}

void Board::update()
{
	m_brick.update(m_ball.rect);

	if (isKeyPressed(m_direction.first))
	{
		m_space.rect.x += m_speed;
		
		if (m_space.rect.x + m_space.rect.w >= Presenter::m_SCREEN_WIDTH)
		{
			m_space.rect.x = Presenter::m_SCREEN_WIDTH - m_space.rect.w;
		}	
	}
	else if(isKeyPressed(m_direction.second))
	{
		m_space.rect.x -= m_speed;

		if (m_space.rect.x <= 0)
		{
			m_space.rect.x = 0;
		}
	}
}

void Board::draw()
{
	drawObject(m_background);

	drawObject(m_space);

	drawObject(m_ball);

	m_brick.draw();
}

void Board::destroy()
{
	
}
