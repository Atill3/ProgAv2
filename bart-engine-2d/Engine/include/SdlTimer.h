#pragma once

#include <ITimer.h>

namespace bart
{
	class SdlTimer final : public ITimer
	{
	public:
		virtual ~SdlTimer() = default;
		bool Initialize() override;
		void Destroy() override;
		float GetTime() override;
		void Sleep(float delay) override;
	};
}
