#pragma once

#include <fstream>
#include <ctime>

#include "defines.h"

class Dropable
{
public:
	Dropable();
	~Dropable();

	void initAll();
	void update();
	void draw();

	Dropable createNew();
	
	string m_type;
	
	Drawable m_drop;
	
	vector<Dropable> m_allDropables;	
private:
	int m_speed;
	
};