#include "Board.h"
#include "World.h"

extern World world;

Board::Board()
{
}

Board::~Board()
{
}

void Board::load()
{
	srand(time(0));
	
	fstream stream;

	string tmp, background, img, img2;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "board.txt");

	stream >> tmp >> background;
	stream >> tmp >> dir.x >> dir.y;
	stream >> tmp >> m_space.rect.x >> m_space.rect.y >> m_space.rect.w >> m_space.rect.h;
	stream >> tmp >> img;
	stream >> tmp >> m_speed;
	stream >> tmp >> m_spacePressed.rect.x >> m_spacePressed.rect.y >> m_spacePressed.rect.w >> m_spacePressed.rect.h;
	stream >> tmp >> img2;

	stream.close();

	m_background = loadTexture(GAME_FOLDER + background);
	m_spacePressed.texture = loadTexture(GAME_FOLDER + img2);
	m_space.texture = loadTexture(GAME_FOLDER + img);

	m_direction.first = (SDL_Scancode)dir.x; // Right
	m_direction.second = (SDL_Scancode)dir.y; // Left

	m_brick.init();

	Ball _ball;
	
	_ball.init();

	m_balls.push_back(_ball);

	m_drops.initAll();

	m_allDrops.clear();

	loadHearts();
}

void Board::loadHearts()
{
	fstream stream;

	string tmp, heartImg, brokenHeartImg;

	Drawable _heart;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "hearts.txt");

	stream >> tmp >> _heart.rect.x >> _heart.rect.y >> _heart.rect.w >> _heart.rect.h;
	stream >> tmp >> heartImg >> brokenHeartImg;
	stream >> tmp >> m_offset;

	stream.close();

	m_lives = 3;

	_heart.texture = loadTexture(GAME_FOLDER + heartImg);

	m_deadTexture = loadTexture(GAME_FOLDER + brokenHeartImg);

	m_hearts.push_back(_heart);

	for (int i = 1; i < m_lives; i++)
	{
		_heart.rect.x += m_offset;

		m_hearts.push_back(_heart);
	}
}

void Board::update()
{
	if (isKeyPressed(SDL_SCANCODE_SPACE))
	{
		m_isSpacePressed = true;
	}

	if (m_isSpacePressed)
	{
		for (int i = 0; i < m_balls.size(); i++)
		{
			m_balls[i].update();
		}
	}

	if (m_balls.size() == 1 && m_balls[0].m_ball.rect.y > Presenter::m_SCREEN_HEIGHT)
	{
		removeHeart();

		return;
	}
	
	updateDrops();

	for (int i = 0; i < m_balls.size(); i++)
	{
		if (m_balls[i].m_ball.rect.y > Presenter::m_SCREEN_HEIGHT)
		{
			world.m_soundManager.playSound(SOUND::DEAD);

			m_balls.erase(m_balls.begin() + i);
		}
	}

	for (int i = 0; i < m_balls.size(); i++)
	{
		if (collRectRect(m_balls[i].m_ball.rect, m_space.rect))
		{
			world.m_soundManager.playSound(SOUND::BOUNCE);

			m_balls[i].m_moveDown = false;

			collUpDown(m_balls[i].m_ball.rect, m_space.rect, i);
			collLeftRight(m_balls[i].m_ball.rect, m_space.rect, i);
		}
	}

	updateBricks();

	moveSpace();
}

void Board::draw()
{
	drawObject(m_background);

	drawObject(m_space);

	for (int i = 0; i < m_balls.size(); i++)
	{
		m_balls[i].draw();
	}

	m_brick.draw();

	if (!m_isSpacePressed)
	{
		drawObject(m_spacePressed);
	}

	for (int i = 0; i < m_allDrops.size(); i++)
	{
		m_allDrops[i].draw();
	}

	drawHearts();
}

void Board::drawHearts()
{
	for (int i = 0; i < m_hearts.size(); i++)
	{
		drawObject(m_hearts[i]);
	}
}

void Board::removeHeart()
{
	m_isSpacePressed = false;

	m_allDrops.clear();
	m_balls.clear();
	
	m_lives--;

	world.m_soundManager.playSound(SOUND::DEAD);

	m_hearts[m_lives].texture = m_deadTexture;
	
	m_direction.first = (SDL_Scancode)dir.x; // Right
	m_direction.second = (SDL_Scancode)dir.y; // Left

	m_space.rect.w = 200;
	m_speed = 10;

	Ball _ball;

	_ball.m_moveDown = true;
	
	_ball.init();

	m_balls.push_back(_ball);
	
	//m_brick.init();

	if (m_lives == 0)
	{
		world.m_soundManager.playSound(SOUND::LOSE);

		world.m_stateManager.changeGameState(GAME_STATE::WIN_SCREEN);

		return;
	}
}

void Board::addHeart()
{	
	if (m_lives >= 3)
	{
		Drawable _heart = m_hearts[0];
		
		_heart.rect.x += m_offset * m_lives;

		m_hearts.push_back(_heart);
	}
	
	m_lives++;
	
	m_hearts[m_lives - 1].texture = m_hearts[0].texture;
}

void Board::moveSpace()
{
	if (isKeyPressed(m_direction.first))
	{
		m_space.rect.x += m_speed;

		if (m_space.rect.x + m_space.rect.w >= Presenter::m_SCREEN_WIDTH)
		{
			m_space.rect.x = Presenter::m_SCREEN_WIDTH - m_space.rect.w;
		}
	}
	else if (isKeyPressed(m_direction.second))
	{
		m_space.rect.x -= m_speed;

		if (m_space.rect.x <= 0)
		{
			m_space.rect.x = 0;
		}
	}
}

void Board::updateDrops()
{
	for (int i = 0; i < m_allDrops.size(); i++)
	{
		m_allDrops[i].update();

		if (collRectRect(m_space.rect, m_allDrops[i].m_drop.rect))
		{
			if (m_allDrops[i].m_type == "BigBall")
			{
				world.m_soundManager.playSound(SOUND::BUFF);
				
				m_allDrops.erase(m_allDrops.begin() + i);
				
				int randBall = rand() % m_balls.size();

				m_balls[randBall].m_ball.rect.w += 20;
				m_balls[randBall].m_ball.rect.h += 20;

				return;
			}
			else if (m_allDrops[i].m_type == "Reverse")
			{
				world.m_soundManager.playSound(SOUND::NURF);

				m_allDrops.erase(m_allDrops.begin() + i);

				SDL_Scancode _tmp = m_direction.first;

				m_direction.first = m_direction.second;
				m_direction.second = _tmp;

				return;
			}
			else if (m_allDrops[i].m_type == "BiggerSpace")
			{
				world.m_soundManager.playSound(SOUND::BUFF);

				m_allDrops.erase(m_allDrops.begin() + i);

				m_space.rect.w += 30;

				return;
			}
			else if (m_allDrops[i].m_type == "SmallerSpace")
			{
				world.m_soundManager.playSound(SOUND::NURF);

				m_allDrops.erase(m_allDrops.begin() + i);

				m_space.rect.w -= 30;

				if (m_space.rect.w <= 10)
				{
					m_space.rect.w = 10;
				}

				return;
			}
			else if (m_allDrops[i].m_type == "AddBall")
			{
				world.m_soundManager.playSound(SOUND::BUFF);

				m_allDrops.erase(m_allDrops.begin() + i);

				Ball _ball;

				_ball.init();

				_ball.m_ball.rect = m_balls[0].m_ball.rect;

				_ball.m_moveDown = false;

				int r = rand() % 11;

				if (r < 6)
				{
					_ball.m_ball.rect.x -= r * 2;
				}
				else
				{
					_ball.m_ball.rect.y -= r * 2;
				}

				m_balls.push_back(_ball);

				return;
			}
			else if (m_allDrops[i].m_type == "AddLive")
			{
				world.m_soundManager.playSound(SOUND::BUFF);

				m_allDrops.erase(m_allDrops.begin() + i);

				addHeart();

				return;
			}
			else if (m_allDrops[i].m_type == "SpeedIncreaseBall")
			{
				world.m_soundManager.playSound(SOUND::BUFF);

				m_allDrops.erase(m_allDrops.begin() + i);

				int randBall = rand() % m_balls.size();
				
				m_balls[randBall].m_speed.x += 3;
				m_balls[randBall].m_speed.y += 3;

				return;
			}
			else if (m_allDrops[i].m_type == "SpeedDecreaseBall")
			{
				world.m_soundManager.playSound(SOUND::NURF);

				m_allDrops.erase(m_allDrops.begin() + i);

				int randBall = rand() % m_balls.size();
				
				m_balls[randBall].m_speed.x -= 2;
				m_balls[randBall].m_speed.y -= 2;

				if (m_balls[randBall].m_speed.x <= 0)
				{
					m_balls[randBall].m_speed.x = 1;
				}

				if (m_balls[randBall].m_speed.y <= 0)
				{
					m_balls[randBall].m_speed.y = 1;
				}

				return;
			}
			else if (m_allDrops[i].m_type == "MegaBall")
			{
				world.m_soundManager.playSound(SOUND::BUFF);

				m_allDrops.erase(m_allDrops.begin() + i);

				int randBall = rand() % m_balls.size();
				
				m_balls[randBall].m_dmg += 3;

				return;
			}
			else if (m_allDrops[i].m_type == "SpeedIncreaseSpace")
			{
				world.m_soundManager.playSound(SOUND::BUFF);

				m_allDrops.erase(m_allDrops.begin() + i);

				m_speed += 2;

				return;
			}
			else if (m_allDrops[i].m_type == "SpeedDecreaseSpace")
			{
				world.m_soundManager.playSound(SOUND::NURF);

				m_allDrops.erase(m_allDrops.begin() + i);

				m_speed -= 2;

				if (m_speed <= 0)
				{
					m_speed = 1;
				}

				return;
			}
			else if (m_allDrops[i].m_type == "MultiplyBalls")
			{
				world.m_soundManager.playSound(SOUND::BUFF);

				m_allDrops.erase(m_allDrops.begin() + i);

				int _size = m_balls.size();

				for (int i = 0; i < _size; i ++)
				{
					Ball _ball;

					_ball.init();

					_ball.m_ball.rect = m_balls[0].m_ball.rect;

					_ball.m_moveDown = false;

					int r = rand() % 11;

					if (r < 6)
					{
						_ball.m_ball.rect.x -= r * 2;
					}
					else
					{
						_ball.m_ball.rect.y -= r * 2;
					}
										 
					m_balls.push_back(_ball);
				}

				return;
			}
			else if (m_allDrops[i].m_type == "SmallBall")
			{
				world.m_soundManager.playSound(SOUND::NURF);

				m_allDrops.erase(m_allDrops.begin() + i);

				int randBall = rand() % m_balls.size();
				
				m_balls[randBall].m_ball.rect.w -= 20;
				m_balls[randBall].m_ball.rect.h -= 20;

				if (m_balls[randBall].m_ball.rect.w <= 20)
				{
					m_balls[randBall].m_ball.rect.w = 20;
					m_balls[randBall].m_ball.rect.h = 20;
				}

				return;
			}
		}

		if (m_allDrops[i].m_drop.rect.y >= Presenter::m_SCREEN_HEIGHT)
		{
			m_allDrops.erase(m_allDrops.begin() + i);

			return;
		}
	}
}

void Board::updateBricks()
{
	for (int p = 0; p < m_balls.size(); p++)
	{
		for (int i = 0; i < m_ROWS; i++)
		{
			for (int j = 0; j < m_COLS; j++)
			{
				if (collRectRect(m_brick.m_allBricks[i][j].rect, m_balls[p].m_ball.rect))
				{
					world.m_soundManager.playSound(SOUND::BOUNCE);

					collLeftRight(m_balls[p].m_ball.rect, m_brick.m_allBricks[i][j].rect, p);
					collUpDown(m_balls[p].m_ball.rect, m_brick.m_allBricks[i][j].rect, p);
					
					m_brick.m_allBricks[i][j].m_hp -= m_balls[p].m_dmg;

					if (m_brick.m_allBricks[i][j].m_hp <= 0)
					{
						int r = rand() % 4;

						if (r == 1) 
						{
							label: 
							Dropable _drop = m_drops.createNew();

							/*if (_drop.m_type != "AddBall")
							{
								goto label;
							}*/
							
							world.m_soundManager.playSound(SOUND::SPAWN);

							_drop.m_drop.rect.x = m_brick.m_allBricks[i][j].rect.x;
							_drop.m_drop.rect.y = m_brick.m_allBricks[i][j].rect.y;

							m_allDrops.push_back(_drop);
						}

						SDL_DestroyTexture(m_brick.m_allBricks[i][j].texture);

						m_brick.m_allBricks[i][j].rect = { 0, 0, 0, 0 };

						m_brick.m_counter++;
					}

					if (m_brick.m_counter >= m_ROWS * m_COLS)
					{
						world.m_soundManager.playSound(SOUND::WIN);

						world.m_stateManager.changeGameState(GAME_STATE::WIN_SCREEN);

						return;
					}
				}
			}
		}
	}
}

void Board::collUpDown(SDL_Rect rect1, SDL_Rect rect2, int index)
{
	if (rect1.y < rect2.y)
	{
		m_balls[index].collisionY();
		rect1.y = rect2.y + rect2.h;
		return;	
	}
	
	if (rect1.y + rect1.h > rect2.y + rect2.h)
	{
		m_balls[index].collisionY();
		rect1.y = rect2.y + rect2.h - rect1.h;
	}
}

void Board::collLeftRight(SDL_Rect rect1, SDL_Rect rect2, int index)
{
	if (rect1.x < rect2.x)
	{
		m_balls[index].collisionX();
		rect1.x = rect2.x + rect2.w;
		return;
	}
	
	if (rect1.x + rect1.w > rect2.x + rect2.w)
	{
		m_balls[index].collisionX();
		rect1.x = rect2.x + rect2.w - rect1.w;
	}
}