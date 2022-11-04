#include "Dropable.h"
#include "Presenter.h"

Dropable::Dropable()
{
	
}

Dropable::~Dropable()
{
	
}

void Dropable::initAll()
{
	srand(time(NULL));
	
	string tmp;
	
	fstream stream;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "drops.txt");
	
	Dropable _drop;
		
	stream >> tmp >> _drop.m_drop.rect.w >> _drop.m_drop.rect.h;
	stream >> tmp >> _drop.m_speed;
	
	while (!stream.eof())
	{
		stream >> tmp >> _drop.m_type;

		_drop.m_drop.texture = loadTexture(BOOSTS_FOLDER + _drop.m_type + ".bmp");
		
		m_allDropables.push_back(_drop);
	}
	
	stream.close();
}

void Dropable::update()
{
	m_drop.rect.y += m_speed;
}

void Dropable::draw()
{
	drawObject(m_drop);
}

Dropable Dropable::createNew()
{	
	return m_allDropables[rand() % m_allDropables.size()];
}
