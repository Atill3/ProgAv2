#include <Bart2d.h>
#include <FileLogger.h>

bool bart::FileLogger::Initialize()
{
	myLog.open("Log.txt", ios::out);
	return myLog.is_open();
}

void bart::FileLogger::Destroy()
{
	myLog.close();
}

void bart::FileLogger::Log(const string& myString)
{
	myLog << "INFO" << myString << endl;
}

void bart::FileLogger::LogWarning(const string& myString)
{
	myLog << "WARNING" << myString << endl;
}

void bart::FileLogger::LogError(const string& myString)
{
	myLog << "ERROR" << myString << endl;
}
