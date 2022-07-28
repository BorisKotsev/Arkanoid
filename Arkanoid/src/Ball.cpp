#include "Ball.h"
#include "World.h"

extern World world;

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::init()
{
	fstream stream;

	string tmp, img;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "ball.txt");

	stream >> tmp >> m_ball.rect.x >> m_ball.rect.y >> m_ball.rect.w >> m_ball.rect.h;
	stream >> tmp >> img;
	stream >> tmp >> m_speed.x >> m_speed.y;

	stream.close();

	m_ball.texture = loadTexture(GAME_FOLDER + img);
}

void Ball::update()
{
	m_ball.rect.x += m_speed.x;
	m_ball.rect.y += m_speed.y;

	if (m_ball.rect.y > Presenter::m_SCREEN_HEIGHT)
	{
		world.m_stateManager.changeGameState(GAME_STATE::WIN_SCREEN);
	}
}

void Ball::draw()
{	
	drawObject(m_ball);
}

SDL_Rect Ball::getRect()
{
	return m_ball.rect;
}

void Ball::collisionX(int2 percent)
{
	m_speed.x *= -1;
	m_speed.y = m_speed.y * (percent.y * 0.75 + percent.x * 0.25) / percent.y;
}

void Ball::collisionY(int2 percent)
{
	m_speed.y *= -1;
	m_speed.x = m_speed.x * (percent.y * 0.75 + percent.x * 0.25) / percent.y;
}
