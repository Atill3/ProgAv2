#pragma once

#include <IService.h>

namespace bart
{
	class IMaths : public IService
	{
	public:
		virtual ~IMaths() = default;
		virtual int Random() = 0;

		template <typename T>
		T Range(T min, T max)
		{
			return min + static_cast<T>(Random()) / (static_cast<T>(RAND_MAX) / (max - min));
		}
	};
}
