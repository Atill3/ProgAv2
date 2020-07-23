#include <Bart2d.h>
#include <Windows.h>
#include <ConsoleLogger.h>
#include <iostream>

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

void bart::ConsoleLogger::Log(const string& message)
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "INFO: " << message << endl;
}

void bart::ConsoleLogger::LogWarning(const string& message)
{
	SetConsoleTextAttribute(hConsole, 6);
	cout << "WARN: " << message << endl;
}

void bart::ConsoleLogger::LogError(const string& message)
{
	SetConsoleTextAttribute(hConsole, 4);
	cout << "ERROR: " << message << endl;
}
