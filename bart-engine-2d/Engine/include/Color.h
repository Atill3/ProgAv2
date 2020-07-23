#pragma once

namespace bart
{
	class Color
	{
	public:
		Color(unsigned char red, unsigned char green, unsigned char blue);
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

		void Set(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		void Set(const Color& other);

		static const Color& Red;
		static const Color& Green;
		static const Color& Blue;
		static const Color& White;
		static const Color& Black;
		static const Color& DarkRed;
		static const Color& Pink;
		static const Color& Teal;
		static const Color& DarkGreen;
		static const Color& Turquoise;
		static const Color& DarkBlue;
		static const Color& Violet;
		static const Color& Gray;
		static const Color& DarkYellow;
		static const Color& Yellow;
		static const Color& CornflowerBlue;
		static const Color& Orange;

		unsigned char red = 255;
		unsigned char green = 255;
		unsigned char blue = 255;
		unsigned char alpha = 255;
	};
}
