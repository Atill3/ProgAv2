#pragma once

#include <IService.h>

namespace bart
{
	class IRandom : public IService
	{
	public:
		virtual ~IRandom() = default;
		virtual void InitRanSeed() = 0;
		virtual unsigned int GetRandom(int a, int b) = 0;

		template<typename R>
		R Range(R a, R b)
		{
			return (R)GetRandom(a, b);
		}
	};
}