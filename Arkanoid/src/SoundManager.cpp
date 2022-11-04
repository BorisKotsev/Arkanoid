#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::init()
{
	fstream stream;

	string tmp, background, deadBall, buff, nurf, win, lose, crack, bounce, spawn;

	stream.open(SOUND_FOLDER + "music.txt");

	stream >> tmp >> background;
	stream >> tmp >> deadBall;
	stream >> tmp >> buff;
	stream >> tmp >> nurf;
	stream >> tmp >> win;
	stream >> tmp >> lose;
	stream >> tmp >> crack;
	stream >> tmp >> bounce;
	stream >> tmp >> spawn;

	stream.close();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}

	m_backgroundMusic = Mix_LoadWAV((SOUND_FOLDER + background).c_str());
	m_deadBall = Mix_LoadWAV((SOUND_FOLDER + deadBall).c_str());
	m_buff = Mix_LoadWAV((SOUND_FOLDER + buff).c_str());
	m_nurf = Mix_LoadWAV((SOUND_FOLDER + nurf).c_str());
	m_win = Mix_LoadWAV((SOUND_FOLDER + win).c_str());
	m_lose = Mix_LoadWAV((SOUND_FOLDER + lose).c_str());
	m_crack = Mix_LoadWAV((SOUND_FOLDER + crack).c_str());
	m_bounce = Mix_LoadWAV((SOUND_FOLDER + bounce).c_str());
	m_spawn = Mix_LoadWAV((SOUND_FOLDER + spawn).c_str());

	playSound(SOUND::BACKGROUND);
}

void SoundManager::playSound(SOUND sound)
{
	Mix_AllocateChannels(15);

	switch (sound)
	{
	case SOUND::BACKGROUND:
		Mix_PlayChannel(1, m_backgroundMusic, -1);
		Mix_Volume(1, 17);
		break;
	case SOUND::DEAD:
		Mix_PlayChannel(2, m_deadBall, 0);
		Mix_Volume(2, 10);
		break;
	case SOUND::BUFF:
		Mix_PlayChannel(3, m_buff, 0);
		Mix_Volume(3, 10);
		break;
	case SOUND::NURF:
		Mix_PlayChannel(4, m_nurf, 0);
		Mix_Volume(4, 10);
		break;
	case SOUND::WIN:
		Mix_PlayChannel(5, m_win, 0);
		Mix_Volume(5, 10);
		break;
	case SOUND::LOSE:
		Mix_PlayChannel(6, m_lose, 0);
		Mix_Volume(6, 10);
		break;
	case SOUND::CRACK:
		Mix_PlayChannel(7, m_crack, 0);
		Mix_Volume(7, 5);
		break;
	case SOUND::BOUNCE:
		Mix_PlayChannel(8, m_bounce, 0);
		Mix_Volume(8, 5);
		break;
	case SOUND::SPAWN:
		Mix_PlayChannel(9, m_spawn, 0);
		Mix_Volume(9, 10);
		break;
	}
}

void SoundManager::destroy()
{
	Mix_FreeChunk(m_backgroundMusic);
	m_backgroundMusic = NULL;

	Mix_FreeChunk(m_deadBall);
	m_deadBall = NULL;

	Mix_FreeChunk(m_buff);
	m_buff = NULL;

	Mix_FreeChunk(m_nurf);
	m_nurf = NULL;

	Mix_FreeChunk(m_win);
	m_win = NULL;

	Mix_FreeChunk(m_lose);
	m_lose = NULL;

	Mix_FreeChunk(m_crack);
	m_crack = NULL;

	Mix_FreeChunk(m_bounce);
	m_bounce = NULL;

	Mix_FreeChunk(m_spawn);
	m_spawn = NULL;
}