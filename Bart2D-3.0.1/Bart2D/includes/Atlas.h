#pragma once

#include <string>
#include <map>
#include <Sprite.h>

using namespace std;

namespace bart
{
	struct FrameInfo
	{
	public:
		int x;
		int y;
		int w;
		int h;
	};

	class Atlas final : public Sprite
	{
	public:
		virtual ~Atlas() = default;

		void AddFrame(const string& name, int x, int y, int w, int h);
		void SetFrame(const string& name);

	private:
		typedef map<string, FrameInfo> TFrameMap;
		TFrameMap m_Frames;
	};
}