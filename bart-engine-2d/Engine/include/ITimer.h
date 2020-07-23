#pragma once

#include <IService.h>

namespace bart
{
	class ITimer : public IService
	{
	public:
		virtual ~ITimer() = default;
		virtual float GetTime() = 0;
		virtual void Sleep(float delay) = 0;
	};
}
