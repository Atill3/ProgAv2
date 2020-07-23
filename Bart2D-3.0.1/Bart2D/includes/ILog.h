#pragma once

#include <IService.h>
#include <string>

using namespace std;
namespace bart 
{
	class ILog : public IService
	{
	public:
		virtual ~ILog() = default;
		virtual void Log(const string& myString) = 0;
		virtual void LogWarning(const string& myString) = 0;
		virtual void LogError(const string& myString) = 0;

	private:
	};
}