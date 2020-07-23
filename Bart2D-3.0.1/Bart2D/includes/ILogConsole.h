#pragma once
#include <IService.h>
namespace bart
{
	class ILogConsole : public IService
	{
	public:
		virtual ~ILogConsole() = default;
		virtual void WriteInConsole(string consoleTxt) = 0;
		virtual void CloseConsole() = 0;
	private:
		virtual void OpenConsole() = 0;
	};
}