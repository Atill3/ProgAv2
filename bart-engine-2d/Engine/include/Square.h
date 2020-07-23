#pragma once

#include <Component.h>
#include <Color.h>

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
		void SetColor(const Color& color);

	private:
		Color m_Color{255, 255, 255, 255};
		Transform* m_Transform = nullptr;
	};
}
