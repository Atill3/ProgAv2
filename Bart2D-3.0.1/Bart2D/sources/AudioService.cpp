#include <Bart2d.h>
#include <SDL.h>
#include "Engine.h"
#include  <AudioService.h>


bool bart::AudioService::Initialize()
{
	
	if(Mix_OpenAudio(22050, AUDIO_S16, 2, 2048) != 0)
	{
		return false;
	}
	return true;
}

void bart::AudioService::Destroy()
{
	Mix_CloseAudio();
}

size_t bart::AudioService::LoadMusic(const string& filename)
{
	const size_t musicId = std::hash<std::string>()(filename);
	if (m_MusicCache.count(musicId) > 0)
	{
		return musicId;
	}

	_Mix_Music* music = Mix_LoadMUS(filename.c_str());
	if (music)
	{
		m_MusicCache.emplace(musicId, music);
		return musicId;
	}
	Engine::Get().LogFile().WriteFile("Missing Music");
	return 0;
}

size_t bart::AudioService::LoadSound(const string& filename)
{
	const size_t soundID = std::hash<std::string>()(filename);
	if (m_SoundCache.count(soundID) > 0)
	{
		return soundID;
	}

	Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
	if (sound)
	{
		m_SoundCache.emplace(soundID, sound);
		return soundID;
	}
	Engine::Get().LogFile().WriteFile("Missing Sound");
	return 0;
}

void bart::AudioService::UnloadMusic(size_t id)
{
	if (m_MusicCache.count(id) > 0)
	{
		Mix_FreeMusic(m_MusicCache[id]);
		m_MusicCache.erase(id);
	}
}

void bart::AudioService::UnloadSound(size_t id)
{
	if (m_SoundCache.count(id) > 0)
	{
		Mix_FreeChunk(m_SoundCache[id]);
		m_SoundCache.erase(id);
	}
}

void bart::AudioService::PlayMusic(size_t id)
{
	_Mix_Music* playMusic = m_MusicCache[id];
	Mix_PlayMusic(playMusic, 0);
}

void bart::AudioService::PlaySound(size_t id)
{
	Mix_Chunk* playSound = m_SoundCache[id];
	Mix_PlayChannel(-1, playSound, 0);
}

void bart::AudioService::RestartMusic()
{
	Mix_ResumeMusic();
}

void bart::AudioService::StopMusic()
{
	Mix_PauseMusic();
}



