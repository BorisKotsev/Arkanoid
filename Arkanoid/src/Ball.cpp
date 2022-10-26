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

	string tmp, img, img2;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "ball.txt");

	stream >> tmp >> m_ball.rect.x >> m_ball.rect.y >> m_ball.rect.w >> m_ball.rect.h;
	stream >> tmp >> img >> img2;
	stream >> tmp >> m_speed.x >> m_speed.y;
	stream >> tmp >> m_dmg;

	stream.close();

	m_ball.texture = loadTexture(GAME_FOLDER + img);
	m_megaTxt = loadTexture(GAME_FOLDER + img2);

	m_moveDown = true;
}

void Ball::update()
{
	if (m_ball.rect.x > Presenter::m_SCREEN_WIDTH - m_ball.rect.w)
	{
		m_speed.x *= -1;
	}
	
	if (m_ball.rect.y < 0)
	{
		m_speed.y *= -1;
	}

	if (m_ball.rect.x < 0)
	{
		m_speed.x *= -1;
	}
	
	if (!m_moveDown)
	{
		m_ball.rect.x += m_speed.x;
	}

	m_ball.rect.y += m_speed.y;
}

void Ball::draw()
{	
	drawObject(m_ball);
}

void Ball::collisionX()
{
	m_speed.x *= -1.0f;
}

void Ball::collisionY()
{
	m_speed.y *= -1.0f;
}