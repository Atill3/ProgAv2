#include <PlayerController.h>
#include <Engine.h>
#include <SdlInput.h>
#include <RandomService.h>
#include <Square.h>

PlayerController::~PlayerController()
{
}

void PlayerController::Start()
{

	m_Transform = m_Owner->GetComponent<bart::Transform>();
	assert(m_Transform);

}

void PlayerController::Update(float deltatime)
{
	CheckInput();
}

void PlayerController::CheckInput()
{
	
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_A))
	{
		m_Transform->Translate(-m_Speed, 0.0f);
	}
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_D))
	{
		m_Transform->Translate(m_Speed, 0.0f);
	}
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_W))
	{
		m_Transform->Translate(0.0f, -m_Speed);
	}
	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_S))
	{
		m_Transform->Translate(0.0f, m_Speed);
	}
}



