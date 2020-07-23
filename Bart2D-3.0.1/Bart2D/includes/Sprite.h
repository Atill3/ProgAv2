#pragma once

#include <Component.h>
#include <string>

using namespace std;

namespace bart
{
	class Transform;

	class Sprite : public Component
	{
	public:
		virtual ~Sprite() = default;
		void Load(const string& filename);

		void Start() override;
		void Render() override;

		void SetColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

	protected:
		size_t m_TextureId = 0;
		int m_SourceX = 0;
		int m_SourceY = 0;
		int m_SourceW = 0;
		int m_SourceH = 0;

		unsigned int m_Red = 255;
		unsigned int m_Green = 255;
		unsigned int m_Blue = 255;
		unsigned int m_Alpha = 255;

		Transform* m_Transform = nullptr;
	};
}