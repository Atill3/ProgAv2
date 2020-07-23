#pragma once

namespace bart
{
	class IService
	{
	public:
		virtual ~IService() = default;

		virtual bool Initialize() = 0;
		virtual void Destroy() = 0;
	};
}