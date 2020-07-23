#pragma once

#include <ITimer.h>

namespace bart 
{
	class SdlTimer final : public ITimer
	{
	public:
		virtual ~SdlTimer() = default;

		// Inherited via ITimer
		virtual bool Initialize() override;
		virtual void Destroy() override;
		virtual float GetTime() override;
		virtual void Sleep(float delay) override;

	private:

	};
}
