#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Engine.h>

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
	if (Engine::Get().Initialize("assets/Engine.ini"))
	{
		Engine::Get().Start("assets/Project.project");
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
