#pragma once
#include <IRandom.h>


namespace bart
{
	class RandomService final : public IRandom
	{
	public:
		virtual ~RandomService() = default;
		bool Initialize() override;
		void Destroy() override;
		void InitRanSeed() override;
		unsigned int GetRandom(int a, int b) override;

	private:
		

	};
}