#pragma once

#include <Component.h>
#include <Rect.h>
#include <Flip.h>

namespace bart
{
	class Transform final : public Component
	{
	public:
		virtual ~Transform() = default;

		void Translate(float x, float y);
		void Rotation(float angle);
		void Set(float x, float y, float w, float h);
		void Set(int x, int y, int w, int h);
		void Set(const RectF& destination);
		void SetPosition(float x, float y);
		void SetSize(float width, float height);

		RectF m_Destination;
		float angle = 0.0f;
		Flip flip;
	};
}
