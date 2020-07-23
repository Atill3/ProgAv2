#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cassert>
#include <Engine.h>
#include <Square.h>
#include <Transform.h>
#include "Game.h"
#include "Controler.h"

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
    if(bart::Engine::Get().Initialize())
    {
        bart::Engine::Get().ILogger().Log("Starting Game");

        bart::Entity* bob = bart::Engine::Get().Scene().AddEntity("Bob");
        bart::Transform* transform = bob->AddComponent<bart::Transform>();
        transform->Set(200.0f, 200.0f, 200.0f, 200.0f);

        bart::Square* square = bob->AddComponent<bart::Square>();
        square->SetColor(255, 255, 0);

        Controler* controler = bob->AddComponent < Controler>();

        bart::Engine::Get().Start();
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

	return 0;
}