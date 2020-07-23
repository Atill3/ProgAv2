#pragma once

#include <IRandom.h>
#include <time.h>

namespace bart
{
	class RandomService final : public IRandom
	{
	public:
		virtual ~RandomService() = default;

		bool Initialize() override;
		void Destroy() override;
		unsigned int GetRandom(int a, int b) override;
		void InitSeed() override;

	};
}