#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cassert>
#include <Engine.h>
#include <Square.h>
#include <Transform.h>
#include <PlayerController.h>
#include <Sprite.h>
#include <Atlas.h>
#include <Animation.h>
#include <HeliControl.h>
#include <Music.h>

/**
 * \param: hInstance is something called a "handle to an instance" or "handle to a module." The operating system uses this value to
 * identify the executable (EXE) when it is loaded in memory. The instance handle is needed for certain Windows functions—for example,
 * to load icons or bitmaps.
 * \param: hPrevInstance has no meaning. It was used in 16-bit Windows, but is now always zero.
 * \param: pCmdLine contains the command-line arguments as a Unicode string.
 * \param: nCmdShow is a flag that says whether the main application window will be minimized, maximized, or shown normally.
 */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nShowCmd)
{
	if (bart::Engine::Get().Initialize())
	{
		//bart::Entity* bob = bart::Engine::Get().Scene().AddEntity("Bob");
		//bart::Transform* transform = bob->AddComponent<bart::Transform>();
		//transform->Set(200.0f, 200.0f, 200.0f, 300.0f);
		//bart::Square* square = bob->AddComponent<bart::Square>();
		//PlayerController* control = bob->AddComponent<PlayerController>();

		//bart::Sprite* sprite = bob->AddComponent<bart::Sprite>();
		//sprite->Load("Assets/dog.png");

		//bart::Atlas* atlas = bob->AddComponent<bart::Atlas>();
		//atlas->Load("Assets/env.png");
		//atlas->AddFrame("water", 0, 0, 32, 32);
		//atlas->AddFrame("brick", 160, 256, 32, 32);
		//
		//atlas->SetFrame("water");

		//bart::Animation* animation = bob->AddComponent<bart::Animation>();
		//animation->Load("Assets/bandit.png");
		//animation->InitAnimation(2, 32, 32);
		//animation->Play(0, 2, 0.01f, true);
		//transform->hflip = true;

		bart::Entity* Choppa = bart::Engine::Get().Scene().AddEntity("Choppa");
		bart::Transform* transform = Choppa->AddComponent<bart::Transform>();
		transform->Set(200.0f, 200.0f, 200.0f, 300.0f);
		bart::Animation* animation = Choppa->AddComponent<bart::Animation>();

		HeliControl* helicontrol = Choppa->AddComponent<HeliControl>();

		bart::Music* m_Music = Choppa->AddComponent<bart::Music>();
		m_Music->Load("assets/Soundtrack1.mp3");
		m_Music->Play();
		bart::Engine::Get().Start();		
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}