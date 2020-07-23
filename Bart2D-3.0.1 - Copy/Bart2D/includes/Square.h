#pragma once

#include <Component.h>

namespace bart
{	
	class Transform;
	class Square final : public Component
	{
	public:
		virtual ~Square() = default;
		void Render() override;
		void Start() override;
		void SetColor(unsigned char r, unsigned char g, unsigned char b);

	private:
		unsigned char m_Red = 255;
		unsigned char m_Green = 255;
		unsigned char m_Blue = 255;

		Transform* m_Transform = nullptr;
	};
}