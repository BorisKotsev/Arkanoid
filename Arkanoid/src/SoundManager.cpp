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
	Mix_AllocateChannels(10);

	switch (sound)
	{
	case SOUND::BACKGROUND:
		Mix_PlayChannel((int)SOUND::BACKGROUND, m_backgroundMusic, -1);
		Mix_Volume((int)SOUND::BACKGROUND, 10);
		break;
	case SOUND::DEAD:
		Mix_PlayChannel((int)SOUND::DEAD, m_deadBall, 1);
		Mix_Volume((int)SOUND::DEAD, 10);
		break;
	case SOUND::BUFF:
		Mix_PlayChannel((int)SOUND::BUFF, m_buff, 1);
		Mix_Volume(3, 10);
		break;
	case SOUND::NURF:
		Mix_PlayChannel((int)SOUND::NURF, m_nurf, 1);
		Mix_Volume((int)SOUND::NURF, 10);
		break;
	case SOUND::WIN:
		Mix_PlayChannel((int)SOUND::WIN, m_win, 1);
		Mix_Volume((int)SOUND::WIN, 10);
		break;
	case SOUND::LOSE:
		Mix_PlayChannel((int)SOUND::LOSE, m_lose, 1);
		Mix_Volume((int)SOUND::LOSE, 10);
		break;
	case SOUND::CRACK:
		Mix_PlayChannel((int)SOUND::CRACK, m_crack, 1);
		Mix_Volume((int)SOUND::CRACK, 10);
		break;
	case SOUND::BOUNCE:
		Mix_PlayChannel((int)SOUND::BOUNCE, m_bounce, 1);
		Mix_Volume((int)SOUND::BOUNCE, 10);
		break;
	case SOUND::SPAWN:
		Mix_PlayChannel((int)SOUND::SPAWN, m_spawn, 1);
		Mix_Volume((int)SOUND::SPAWN, 10);
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