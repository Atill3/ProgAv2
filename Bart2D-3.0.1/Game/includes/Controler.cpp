#include "Controler.h"
#include <SdlInput.h>
#include <Engine.h>
#include <RandomService.h>

Controler::~Controler()
{
}

void Controler::Start()
{
	m_Transform = m_Owner->GetComponent<bart::Transform>() ;

	assert(m_Transform);

	m_Color = m_Owner->GetComponent<bart::Square>();
	assert(m_Color);
}

void Controler::Update(float deltatime)
{
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_LEFT))
	{
		m_Transform->Translate(-5.0f, 0.0f);
	}
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_RIGHT))
	{
		m_Transform->Translate(5.0f, 0.0f);
	}	
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_DOWN))
	{
		m_Transform->Translate(0.0f, 5.0f);
	}	
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_UP))
	{
		m_Transform->Translate(0.0f, -5.0f);
	}

	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_SPACE) && m_Pressed == false)
	{
		m_Color->SetColor(bart::Engine::Get().Random().Range(0, 255), bart::Engine::Get().Random().Range(0, 255), bart::Engine::Get().Random().Range(0, 255));
		m_Pressed = true;
	}
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_SPACE)== false && m_Pressed)
	{
		m_Pressed = false;
	}

}
