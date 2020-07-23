#include <Bart2d.h>
#include <SDL.h>
#include <Engine.h>
#include <SdlLogFile.h>

using namespace std;

bool bart::SdlLogFile::Initialize()
{
	OpenFile();
	return true;
}

void bart::SdlLogFile::Destroy()
{
}

void bart::SdlLogFile::OpenFile()
{
	myLogs.open("EngineLogs.txt", ios::out);
}


void bart::SdlLogFile::WriteFile(string LogTxt)
{
	myLogs << LogTxt << endl;
}

void bart::SdlLogFile::CloseFile()
{
	myLogs.close();
}
