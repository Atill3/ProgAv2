#pragma once

#include <ILogFile.h>
#include <fstream>
#include <Windows.h>

namespace bart
{
	class SdlLogFile final : public ILogFile
	{
	public:
		virtual ~SdlLogFile() = default;


		// herite de ILog
		bool Initialize() override;

		void Destroy() override;

		void WriteFile(string LogTxt) override;

		void CloseFile() override;
	private:
		fstream myLogs;
		void OpenFile() override;

	};
}
