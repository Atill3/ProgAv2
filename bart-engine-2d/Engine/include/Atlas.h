#pragma once

#include <string>
#include <map>
#include <Sprite.h>
#include <Rect.h>

using namespace std;

namespace bart
{
	class Atlas final : public Sprite
	{
	public:
		virtual ~Atlas() = default;

		void AddFrame(const string& name, int x, int y, int w, int h);
		void SetFrame(const string& name);

	private:
		typedef map<string, Rect<int>> TFrameMap;
		TFrameMap m_Frames;
	};
}
