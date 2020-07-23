#include <Bart2d.h>
#include <Music.h>
#include <Engine.h>

void bart::Music::Load(const string& filename)
{
	m_MusicId = Engine::Get().Audio().LoadMusic(filename);
}

void bart::Music::Play()
{
	IsPlaying = true;
	Engine::Get().Audio().PlayMusic(m_MusicId);
}

void bart::Music::Stop()
{
	Engine::Get().Audio().StopMusic();
}

void bart::Music::Restart()
{
	Engine::Get().Audio().RestartMusic();
}

void bart::Music::Update(float deltatime)
{
	if(Engine::Get().Input().IsKeyDown(EKeys::KEY_SPACE) && IsPlaying != false && IsPress == false)
	{
		Stop();
		IsPlaying = false;
		IsPress = true;
	}
	else if (Engine::Get().Input().IsKeyDown(EKeys::KEY_SPACE)&& IsPlaying != true && IsPress == false)
	{
		Restart();
		IsPlaying = true;
		IsPress = true;
	}
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_SPACE) == false)
	{
		IsPress = false;
	}
}
