#pragma once

#include <SDL_mixer.h>
#include <fstream>

#include "defines.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	
	void init();
	void playSound(SOUND sound);
	void destroy();
	
private:
	Mix_Chunk* m_backgroundMusic;
	Mix_Chunk* m_deadBall;
	Mix_Chunk* m_buff;
	Mix_Chunk* m_nurf;
	Mix_Chunk* m_win;
	Mix_Chunk* m_lose;
	Mix_Chunk* m_crack;
	Mix_Chunk* m_bounce;
	Mix_Chunk* m_spawn;
};