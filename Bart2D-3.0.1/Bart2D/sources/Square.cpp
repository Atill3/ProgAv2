#include <Bart2d.h>
#include <Square.h>
#include <Engine.h>
#include <Transform.h>

void bart::Square::Render()
{
	Engine::Get().Graphics().SetColor(m_Red, m_Green, m_Blue);
	Engine::Get().Graphics().FillRect(
		m_Transform->x,
		m_Transform->y,
		m_Transform->w,
		m_Transform->h);
}

void bart::Square::Start()
{
	m_Transform = m_Owner->GetComponent<Transform>();
	assert(m_Transform);
}

void bart::Square::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_Red = r;
	m_Green = g;
	m_Blue = b;
}

void bart::Square::SetShape(unsigned int x, unsigned int y, unsigned w, unsigned h)
{
	Engine::Get().Graphics().FillRect(
		m_Transform->x,
		m_Transform->y,
		m_Transform->w,
		m_Transform->h);
}
