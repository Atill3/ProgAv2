#pragma once
#include <IService.h>

namespace bart
{
	class ILogFile : public IService
	{
	public:
		virtual ~ILogFile() = default;
		virtual void WriteFile(string LogTxt) = 0;
		virtual void CloseFile() = 0;
	private:
		virtual void OpenFile() = 0;
	};
}