#pragma once
#include <IService.h>

namespace bart
{
	class IRandom : public IService
	{
	public:
		virtual ~IRandom() = default;

		virtual unsigned int GetRandom(int a, int b) = 0;
		virtual void InitSeed() = 0;

		template<typename T>
		T Range(T a, T b)
		{
			return(T)GetRandom(a, b);
		}
	};
}