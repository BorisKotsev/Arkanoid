#include "Brick.h"
#include "World.h"

extern World world;

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

	m_counter = 0;

	int _tmp = _data.rect.x;

	for (int i = 0; i < m_ROWS; i++)
	{
		if (i % 3 == 0)
		{
			_data.m_hp--;
		}

		for (int j = 0; j < m_COLS; j++)
		{			
			_data.texture = loadTexture(GAME_FOLDER + img + ".bmp");

			m_allBricks[i][j] = _data;
			
			_data.rect.x += _offset.x;
		}
				
		_data.rect.x = _tmp;

		_data.rect.y += _offset.y;
	}

	m_oneHp = loadTexture(GAME_FOLDER + "one.bmp");
	m_twoHp = loadTexture(GAME_FOLDER + "two.bmp");
	m_threeHp = loadTexture(GAME_FOLDER + "three.bmp");
}

void Brick::draw()
{
	for (int i = 0; i < m_ROWS; i++)
	{
		for (int j = 0; j < m_COLS; j++)
		{	
			drawObject(m_allBricks[i][j]);

			SDL_Rect rect = m_allBricks[i][j].rect;

			rect.x += 44;
			rect.y += 13;
			rect.w = 9; 
			rect.h = 21;

			if (m_allBricks[i][j].m_hp == 1)
			{
				SDL_RenderCopy(Presenter::m_main_renderer, m_oneHp, NULL, &rect);
			}
			else if (m_allBricks[i][j].m_hp == 2)
			{
				SDL_RenderCopy(Presenter::m_main_renderer, m_twoHp, NULL, &rect);
			}
			else if (m_allBricks[i][j].m_hp == 3)
			{
				SDL_RenderCopy(Presenter::m_main_renderer, m_threeHp, NULL, &rect);
			}
		}
	}
}