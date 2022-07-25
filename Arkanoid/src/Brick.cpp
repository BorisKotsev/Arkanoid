#include "Brick.h"
#include "Presenter.h"

Brick::Brick()
{
	
}

Brick::~Brick()
{
	
}

void Brick::init()
{
	srand(time(NULL));
	
	fstream stream;

	string tmp, img;

	BrickData _data;

	int2 _offset;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "bricks.txt");

	stream >> tmp >> _data.rect.x >> _data.rect.y >> _data.rect.w >> _data.rect.h;
	stream >> tmp >> img;
	stream >> tmp >> _offset.x >> _offset.y;
	stream >> tmp >> _data.m_hp;

	stream.close();

	int _r1, _r2, _r3;

	_data.texture = loadTexture(GAME_FOLDER + img + ".bmp");
	_data.m_crackedTexture = loadTexture(GAME_FOLDER + img + "_cracked.bmp");

	int _tmp = _data.rect.x;
	
	for (int i = 0; i < m_ROWS; i++)
	{
		for (int j = 0; j < m_COLS; j++)
		{
			_r1 = rand() % 255 + 1;
			_r2 = rand() % 255 + 1;
			_r3 = rand() % 255 + 1;
				
			SDL_SetTextureColorMod(_data.texture, _r1, _r2, _r3);
			SDL_SetTextureColorMod(_data.m_crackedTexture, _r1, _r2, _r3);
			
			_data.texture = loadTexture(GAME_FOLDER + img + ".bmp");
			
			m_allBricks[i][j] = _data;
			
			_data.rect.x += _offset.x;
		}

		_data.rect.x = _tmp;

		_data.rect.y += _offset.y;
	}
}

void Brick::update()
{
	/*for (int i = 0; i < m_ROWS; i++)
	{
		for (int j = 0; j < m_COLS; j++)
		{
			if (collRectRect(m_allBricks[i][j].rect, )
			{
				m_allBricks[i][j].m_hp--;

				if (m_allBricks[i][j].m_hp <= 3)
				{
					m_allBricks[i][j].texture = m_allBricks[i][j].m_crackedTexture;
				}

				if (m_allBricks[i][j].m_hp == 0)
				{
					SDL_DestroyTexture(m_allBricks[i][j].texture);
					m_allBricks[i][j].rect = { 0,0,0,0 };
				}
			}
		}
	}*/
}

void Brick::draw()
{
	for (int i = 0; i < m_ROWS; i++)
	{
		for (int j = 0; j < m_COLS; j++)
		{	
			drawObject(m_allBricks[i][j]);
		}
	}
}