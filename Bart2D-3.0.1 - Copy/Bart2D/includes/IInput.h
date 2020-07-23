#pragma once

#include <IService.h>
#include <EKeys.h>
#include <EmouseButton.h>

namespace bart
{
	class IInput : public IService
	{
	public:
		virtual ~IInput() = default;

		virtual void PoolEvents() = 0;
		virtual bool IsKeyDown(EKeys key) = 0;
		virtual bool IsMouseButtonDown(EMouseButton button) = 0;
		virtual void GetMousePosition(int* x, int* y) = 0;

	};
}