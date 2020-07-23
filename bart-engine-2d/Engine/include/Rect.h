#pragma once

namespace bart
{
	template <typename T>
	class Rect
	{
	public:
		virtual ~Rect() = default;

		Rect()
		{
			Set(0, 0, 0, 0);
		}

		Rect(T x, T y, T w, T h)
		{
			Set(x, y, w, h);
		}

		void Set(T x, T y, T w, T h)
		{
			this->x = x;
			this->y = y;
			this->width = w;
			this->height = h;
		}

		void Set(const Rect& other)
		{
			Set(other.x, other.y, other.width, other.height);
		}

		T x;
		T y;
		T width;
		T height;
	};

	class RectI final : public Rect<int>
	{
	public:
		RectI()
		{
			Set(0, 0, 0, 0);
		}

		RectI(const int x, const int y, const int w, const int h)
		{
			Set(x, y, w, h);
		}

		virtual ~RectI() = default;
	};

	class RectF final : public Rect<float>
	{
	public:
		RectF()
		{
			Set(0, 0, 0, 0);
		}

		RectF(const float x, const float y, const float w, const float h)
		{
			Set(x, y, w, h);
		}

		virtual ~RectF() = default;
	};
}
