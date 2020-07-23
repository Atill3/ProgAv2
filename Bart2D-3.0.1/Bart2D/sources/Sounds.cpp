#include <Bart2d.h>
#include <Sounds.h>
#include <Engine.h>


void bart::Sound::Load(const string& filename)
{
	m_SoundId = Engine::Get().Audio().LoadSound(filename);
}

void bart::Sound::Play()
{
	Engine::Get().Audio().PlaySound(m_SoundId);
}


