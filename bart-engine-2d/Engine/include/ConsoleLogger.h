#pragma once

#include <ILogger.h>

namespace bart
{
	class ConsoleLogger final : public ILogger
	{
	public:
		virtual ~ConsoleLogger() = default;

		bool Initialize() override;
		void Destroy() override;
		void Log(const string& message) override;
		void LogWarning(const string& message) override;
		void LogError(const string& message) override;
	};
}
