#include <Bart2d.h>
#include <SdlInput.h>
#include <SDL.h>
#include <Engine.h>

bool bart::SdlInput::Initialize()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
	return true;
}

void bart::SdlInput::Destroy()
{
}
void bart::SdlInput::CheckMouseButton(unsigned char button, bool state)
{
	switch (button)
	{
		case SDL_BUTTON_LEFT:
			m_MouseStates[LEFT] = state;
			break;
		case SDL_BUTTON_RIGHT:
			m_MouseStates[RIGHT] = state;
			break;
		case SDL_BUTTON_MIDDLE:
			m_MouseStates[MIDDLE] = state;
			break;
	}
}

void bart::SdlInput::PoolEvents()
{
	SDL_Event inputEvent;
	while (SDL_PollEvent(&inputEvent))
	{
		switch (inputEvent.type)
		{
		case SDL_QUIT:
			Engine::Get().Stop();
			break;
		case SDL_MOUSEMOTION:
			m_MouseX = inputEvent.motion.x;
			m_MouseY = inputEvent.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			CheckMouseButton(inputEvent.button.button, true);
			break;
		case SDL_MOUSEBUTTONUP:
			CheckMouseButton(inputEvent.button.button, true);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			m_KeyStates = SDL_GetKeyboardState(nullptr);
			break;

		}
	}
}

bool bart::SdlInput::IsKeyDown(EKeys key)
{
	if (m_KeyStates != nullptr)
	{
		if (m_KeyStates[key] == 1)
		{
			return true;
		}
	}
	return false;
}

bool bart::SdlInput::IsMouseButtonDown(EMouseButton button)
{
	return m_MouseStates[button];
}

void bart::SdlInput::GetMousePosition(int * x, int * y)
{
	*x = m_MouseX;
	*y = m_MouseY;
}
