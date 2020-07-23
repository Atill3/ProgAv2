#include <Engine.h>
#include <Helicontrol.h>
#include <SdlInput.h>

HeliControl::~HeliControl()
{
}

void HeliControl::Start()
{
	m_Transform = m_Owner->GetComponent<bart::Transform>();
	assert(m_Transform);
	m_Animation = m_Owner->GetComponent<bart::Animation>();
	assert(m_Animation);

	m_Animation->Load("Assets/bandit.png");
	m_Animation->InitAnimation(2, 32, 32);
	m_Animation->Play(0, 2, 0.01f, true);
}

void HeliControl::Update(float deltatime)
{
	CheckInput();
}

void HeliControl::CheckInput()
{

	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_A))
	{
		m_Transform->Translate(-m_Speed, 0.0f);
		if (!hasChangedA)
		{
			hasChangedA = true;
			ChangeAnim(4, 2, 0.01f, true);
			CurrentAnim();
		}
	}
	else
	{
		hasChangedA = false;
		
	}

	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_D))
	{

		m_Transform->Translate(m_Speed, 0.0f);
		if (!hasChangedD)
		{
			hasChangedD = true;
			ChangeAnim(2, 2, 0.01f, true);
			CurrentAnim();
		}

	}
	else
	{
		hasChangedD = false;
	}

	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_W))
	{
		m_Transform->Translate(0.0f, -m_Speed);
		if (!hasChangedW)
		{
			hasChangedW = true;
			ChangeAnim(6, 2, 0.01f, true);
			CurrentAnim();
		}

	}
	else
	{
		hasChangedW = false;
	}

	if (bart::Engine::Get().Input().IsKeyDown(EKeys::KEY_S))
	{
		m_Transform->Translate(0.0f, m_Speed);

		if (!hasChangedS)
		{
			hasChangedS = true;
			ChangeAnim(0, 2, 0.01f, true);
			CurrentAnim();
		}
	}
	else
	{
		hasChangedS = false;
	}

}

void HeliControl::ChangeAnim(int start, int count, float delay, bool loop)
{
	m_CurrentStart = start;
	m_CurrentCount = count;
	m_CurrentDelay = delay;
	m_CurrentLoop = loop;
}

void HeliControl::CurrentAnim()
{
	m_Animation->Play(m_CurrentStart, m_CurrentCount, m_CurrentDelay, m_CurrentLoop);
}


