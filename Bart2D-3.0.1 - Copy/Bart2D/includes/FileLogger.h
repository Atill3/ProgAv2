#pragma once

#include <ILog.h>
#include <fstream>

using namespace std;
namespace bart
{
	class FileLogger final : public ILog
	{
	public:

		virtual bool Initialize() override;
		virtual void Destroy() override;
		virtual void Log(const string& myString) override;
		virtual void LogWarning(const string& myString) override;
		virtual void LogError(const string& myString) override;
	private:

		fstream myLog;
	};
}