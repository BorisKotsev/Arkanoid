#include "Board.h"
#include "World.h"
#include "InputManager.h"
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
	fstream stream;

	string tmp, background;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "board.txt");

	stream >> tmp >> background;
	
	stream.close();
	
	m_background = loadTexture(GAME_FOLDER + background);

	m_brick.init();
}

void Board::update()
{
	m_brick.update();
}

void Board::draw()
{
	drawObject(m_background);

	m_brick.draw();
}

void Board::destroy()
{
	
}
