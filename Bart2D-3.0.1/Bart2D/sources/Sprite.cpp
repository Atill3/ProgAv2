#include <Bart2d.h>
#include <Sprite.h>
#include <Engine.h>
#include <Transform.h>

void bart::Sprite::Load(const string & filename)
{
	m_TextureId = Engine::Get().Graphics().LoadTexture(filename);
	Engine::Get().Graphics().GetTextureSize(m_TextureId, &m_SourceW, &m_SourceH);
}

void bart::Sprite::Start()
{
	m_Transform = m_Owner->GetComponent<Transform>();
	assert(m_Transform);
}

void bart::Sprite::Render()
{
	Engine::Get().Graphics().DrawTexture(m_TextureId,
		m_SourceX, m_SourceY, m_SourceW, m_SourceH,
		m_Transform->x,
		m_Transform->y,
		m_Transform->w,
		m_Transform->h,
		m_Transform->angle,
		m_Transform->hFlip,
		m_Transform->vFlip,
		m_Red, m_Green, m_Blue, m_Alpha);
}

void bart::Sprite::SetColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	m_Red = r;
	m_Green = g;
	m_Blue = b;
	m_Alpha = a;
}
