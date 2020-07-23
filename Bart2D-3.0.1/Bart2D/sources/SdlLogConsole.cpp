#include <Bart2d.h>
#include <SDL.h>
#include <Engine.h>
#include <SdlLogConsole.h>


bool bart::SdlLogConsole::Initialize()
{
	OpenConsole();
	return true;
}

void bart::SdlLogConsole::Destroy()
{

}

void bart::SdlLogConsole::WriteInConsole(string consoleTxt)
{
	SDL_Log(consoleTxt.c_str());
}

void bart::SdlLogConsole::CloseConsole()
{
	FreeConsole();
}

void bart::SdlLogConsole::OpenConsole()
{
	AllocConsole();
}
