#include <SdlInput.h>
#include <SDL.h>
#include <Engine.h>

bool SdlInput::Initialize()
{
	m_KeyDownState = SDL_GetKeyboardState(nullptr);
	return true;
}

void SdlInput::Destroy()
{
}

void SdlInput::CheckMouseButton(const unsigned char button, const bool state)
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

void SdlInput::PoolEvents()
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
			CheckMouseButton(inputEvent.button.button, false);
			break;

		case SDL_KEYUP:
		case SDL_KEYDOWN:
			m_KeyDownState = SDL_GetKeyboardState(nullptr);
			break;
		}
	}
}

bool SdlInput::IsKeyDown(const EKeys key)
{
	if (m_KeyDownState != nullptr)
	{
		if (m_KeyDownState[key] == 1)
		{
			return true;
		}
	}

	return false;
}

bool SdlInput::IsMouseButtonDown(const EMouseButton button)
{
	return m_MouseStates[button];
}

void SdlInput::GetMousePosition(int* x, int* y)
{
	*x = m_MouseX;
	*y = m_MouseY;
}
