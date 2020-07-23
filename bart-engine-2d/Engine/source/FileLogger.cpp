#include <FileLogger.h>

bool bart::FileLogger::Initialize()
{
	m_File.open("engine.log", ios::out);
	return m_File.is_open();
}

void bart::FileLogger::Destroy()
{
	m_File.close();
}

void bart::FileLogger::Log(const string& message)
{
	m_File << "INFO: " << message << endl;
}

void bart::FileLogger::LogWarning(const string& message)
{
	m_File << "WARN: " << message << endl;
}

void bart::FileLogger::LogError(const string& message)
{
	m_File << "ERROR: " << message << endl;
}
