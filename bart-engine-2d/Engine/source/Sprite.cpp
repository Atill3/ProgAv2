#include <Sprite.h>
#include <Transform.h>
#include <Engine.h>
#include <cassert>
#include <tinyxml.h>
#include <Properties.h>

void Sprite::Load(const string& filename)
{
	m_TextureId = Engine::Get().Graphics().LoadTexture(filename);
	Engine::Get().Graphics().GetTextureSize(m_TextureId, &m_Source.width, &m_Source.height);
}

void Sprite::Start()
{
	m_Transform = m_Owner->GetComponent<Transform>();
	assert(m_Transform);
}

void Sprite::Render()
{
	Engine::Get().Graphics().DrawTexture(
		m_TextureId,
		m_Source,
		m_Transform->m_Destination,
		m_Transform->angle,
		m_Transform->flip,
		m_Color);
}

void Sprite::SetColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
{
	m_Color.Set(r, g, b, a);
}

void Sprite::SetColor(const Color& color)
{
	m_Color.Set(color);
}