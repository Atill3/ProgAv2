#pragma once

#include <IService.h>
#include <string>

using namespace std;

namespace bart
{
	class ILogger : public IService
	{
	public:
		virtual ~ILogger() = default;
		virtual void Log(const string& message) = 0;
		virtual void LogWarning(const string& message) = 0;
		virtual void LogError(const string& message) = 0;
	};
}
