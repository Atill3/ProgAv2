#include <Bart2d.h>
#include <ConsoleLogger.h>
#include <iostream>
#include <SDL.h>
using namespace std;
HANDLE hConsole;
bool bart::ConsoleLogger::Initialize()
{
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	return true;
}

void bart::ConsoleLogger::Destroy()
{
	FreeConsole();
}

void bart::ConsoleLogger::Log(const string& myString)
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "INFO" << myString << endl;
}

void bart::ConsoleLogger::LogWarning(const string& myString)
{
	SetConsoleTextAttribute(hConsole, 6);
	cout << "WARNING" << myString << endl;
}

void bart::ConsoleLogger::LogError(const string& myString)
{
	SetConsoleTextAttribute(hConsole, 4);
	cout << "ERROR" << myString << endl;
}
