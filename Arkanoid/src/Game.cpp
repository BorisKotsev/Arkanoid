#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
	m_board.load();
}

void Game::destroy()
{

}

void Game::run()
{
	m_board.update();
	m_board.draw();
}