#pragma once

#include <IMaths.h>

namespace bart
{
	class MathService final : public IMaths
	{
	public:
		virtual ~MathService() = default;

		bool Initialize() override;
		void Destroy() override;
		int Random() override;
	};
}
