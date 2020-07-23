#include <Bart2d.h>
#include <Atlas.h>

void bart::Atlas::AddFrame(const string & name, int x, int y, int w, int h)
{
	m_Frames.emplace(name, FrameInfo{ x, y, w, h });
}

void bart::Atlas::SetFrame(const string & name)
{
	m_SourceX = m_Frames[name].x;
	m_SourceY = m_Frames[name].y;
	m_SourceW = m_Frames[name].w;
	m_SourceH = m_Frames[name].h;
}
