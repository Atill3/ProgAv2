#include <Atlas.h>

void bart::Atlas::AddFrame(const string& name, const int x, const int y, const int w, const int h)
{
	m_Frames.emplace(name, Rect<int>{x, y, w, h});
}

void bart::Atlas::SetFrame(const string& name)
{
	m_Source.Set(m_Frames[name]);
}
