#pragma once

#include <type_traits>
#include <cassert>

namespace bart
{
	class IService
	{
	public:
		virtual ~IService() = default;

		virtual bool Initialize() = 0;
		virtual void Destroy() = 0;

		template <typename T>
		static T* Create()
		{
			T* service = new T();
			const bool result = service->Initialize();
			assert(result);
			return service;
		}

		template <typename T>
		static void Destroy(T* service)
		{
			if (service != nullptr)
			{
				service->Destroy();
				delete service;
				service = nullptr;
			}
		}
	};
}
