#pragma once

#include <ILogger.h>
#include <fstream>

namespace bart
{
	class FileLogger final : public ILogger
	{
	public:
		virtual ~FileLogger() = default;

		bool Initialize() override;
		void Destroy() override;
		void Log(const string& message) override;
		void LogWarning(const string& message) override;
		void LogError(const string& message) override;

	private:
		fstream m_File;
	};
}
