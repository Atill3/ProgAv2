#pragma once

#include <ILogConsole.h>
#include <Windows.h>

using namespace std;
namespace bart
{
	class SdlLogConsole final : public ILogConsole
	{
	public:
		virtual ~SdlLogConsole() = default;

		virtual bool Initialize() override;
		virtual void Destroy() override;
		virtual void WriteInConsole(string consoleTxt) override;
		virtual void CloseConsole() override;
	private:
		virtual void OpenConsole() override;

	};
}