#include <Bart2d.h>
#include "..\includes\Entity.h"

void bart::Entity::Update(float deltatime)
{
	if (m_IsActive)
	{
		for (Component* component : m_Components) 
		{
			component->Update(deltatime);
		}
	}
}

void bart::Entity::Render()
{
	if (m_IsActive)
	{
		for (Component* component : m_Components)
		{
			component->Render();
		}
	}
}

void bart::Entity::Destroy()
{
	if (m_IsActive)
	{
		for (Component* component : m_Components)
		{
			component->Destroy();
			delete component;
		}
	}
	m_Components.clear();
}

void bart::Entity::Start()
{
	if (m_IsActive)
	{
		for (Component* component : m_Components)
		{
			component->Start();
		}
	}
}

void bart::Entity::SetActive(bool active)
{
	if (m_IsActive != active)
	{
		m_IsActive = active;
		if (m_IsActive)
		{
			for (Component* component : m_Components)
			{
				component->OnEnable();
			}
		}
		else
		{
			for (Component* component : m_Components)
			{
				component->OnDisable();
			}
		}
	}
}
