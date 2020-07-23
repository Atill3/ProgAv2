#include <Square.h>
#include <Engine.h>
#include <Transform.h>

void Square::Render()
{
	Engine::Get().Graphics().FillRect(m_Transform->m_Destination, m_Color);
}

void Square::Start()
{
	m_Transform = m_Owner->GetComponent<Transform>();
	assert(m_Transform);
}

void Square::SetColor(const unsigned char r, const unsigned char g, const unsigned char b)
{
	m_Color.Set(r, g, b, 255);
}

void Square::SetColor(const Color& color)
{
	m_Color.Set(color);
}
