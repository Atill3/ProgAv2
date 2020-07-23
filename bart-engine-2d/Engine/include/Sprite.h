#pragma once

#include <Component.h>
#include <string>
#include <Color.h>
#include <Rect.h>

using namespace std;

namespace bart
{
	class Properties;
	class Transform;

	class Sprite : public Component
	{
	public:
		virtual ~Sprite() = default;

		void Load(const string& filename);

		void Start() override;
		void Render() override;

		void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		void SetColor(const Color& color);

	protected:
		size_t m_TextureId = 0;
		RectI m_Source{0, 0, 0, 0};
		Color m_Color{255, 255, 255, 255};
		Transform* m_Transform = nullptr;
	};
}
