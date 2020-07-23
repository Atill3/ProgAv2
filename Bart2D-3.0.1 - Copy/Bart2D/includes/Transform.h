#pragma once

#include <Component.h>

namespace bart
{
	class Transform final : public Component
	{
	public:
		virtual ~Transform() = default;

		void Translate(float x, float y);
		void Rotation(float angle);
		void Set(float x, float y, float w, float h);

		float x = 0.0f;
		float y = 0.0f;
		float w = 0.0f;
		float h = 0.0f;
		float angle = 0.0f;
		bool hflip = false;
		bool vflip = false;
	};
}