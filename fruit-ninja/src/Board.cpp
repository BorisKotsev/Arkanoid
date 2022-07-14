#include "Board.h"
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

	string tmp, background, trail, fruitImg;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "board.txt");

	stream >> tmp >> background;
	stream >> tmp >> m_trail.rect.w >> m_trail.rect.h;
	stream >> tmp >> trail;
	stream >> tmp >> m_fruitScore.rect.x >> m_fruitScore.rect.y >> m_fruitScore.rect.w >> m_fruitScore.rect.h;
	stream >> tmp >> fruitImg;

	stream.close();
	
	m_background = loadTexture(GAME_FOLDER + background);

	m_trail.texture = loadTexture(GAME_FOLDER + trail);
	
	m_fruitScore.texture = loadTexture(GAME_FOLDER + fruitImg);

	loadHearts();
	
	Fruit fruit;
	SDL_Texture* text = loadTexture(GAME_FOLDER + FRUIT_FOLDER + "passionFruit.bmp");
	fruit.init(100, 100, text);
	fruit.load(100, 1000);
	m_fruits.push_back(fruit);
}

void Board::loadHearts()
{
	fstream stream;

	string tmp, heartImg, brokenHeartImg;

	int _offset, _lives;

	Drawable _heart;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "hearts.txt");

	stream >> tmp >> _heart.rect.x >> _heart.rect.y >> _heart.rect.w >> _heart.rect.h;
	stream >> tmp >> heartImg >> brokenHeartImg;
	stream >> tmp >> _offset;
	stream >> tmp >> _lives;

	stream.close();

	_heart.texture = loadTexture(GAME_FOLDER + heartImg);

	m_deadTexture = loadTexture(GAME_FOLDER + brokenHeartImg);

	m_hearts.push_back(_heart);
	
	for (int i = 1; i < _lives; i++)
	{
		_heart.rect.x -= _offset;
		
		m_hearts.push_back(_heart);
	}
}

void Board::update()
{
	if(m_frameId == 0) { updateFruits(); }
	m_frameId++;
	m_frameId %= m_speed;
	
}

void Board::draw()
{
	drawObject(m_background);

	drawObject(m_fruitScore);

	drawFruits();

	drawHearts();
}

void Board::drawFruits()
{
	for (int i = 0; i < m_fruits.size(); i++)
	{
		m_fruits.at(i).draw();
	}
	
	if (InputManager::m_drag)
	{
		m_trail.rect.x = InputManager::m_mouseCoor.x - 15;
		m_trail.rect.y = InputManager::m_mouseCoor.y - 15;
		
		drawObject(m_trail);
	}
}

void Board::drawHearts()
{
	for (int i = 0; i < m_hearts.size(); i++)
	{
		drawObject(m_hearts[i]);
	}
}

void Board::updateFruits()
{
	for (int i = 0; i < m_fruits.size(); i++)
	{
		m_fruits.at(i).update();
		
		switch (m_fruits[i].m_hitBoxType)
		{
		case 1: // rect
			if (isMouseInRect(m_fruits[i].m_rectHitBox))
			{
				
			}
			break;
		case 2: // triangle 
			if (MouseIsInTriangle(InputManager::m_mouseCoor, m_fruits[i].m_triangleHitBox.a, 
				m_fruits[i].m_triangleHitBox.b ,m_fruits[i].m_triangleHitBox.c))
			{
				
			}
			break;
		case 3: // circle
			if (MouseIsInCircle(InputManager::m_mouseCoor, m_fruits[i].m_circleHitBox.center, 
				m_fruits[i].m_circleHitBox.radius))
			{

			}
			break;
		case 4: // ellipse
			if (MouseIsInEllipse(InputManager::m_mouseCoor, m_fruits[i].m_circleHitBox.center,
				m_fruits[i].m_ovalHitBox.radius))
			{

			}
			break;
		default:
			break;
		}
	}
}

void Board::destroy()
{
	
}
