#include <Bart2d.h>
#include <Entity.h>

void bart::Entity::Update(float deltaTime)
{
	if (m_isActive)
	{
		for (Component* component : m_Components)
		{
			component->Update(deltaTime);
		}
	}
}

void bart::Entity::Render()
{
	if (m_isActive)
	{
		for (Component* component : m_Components)
		{
			component->Render();
		}
	}
}

void bart::Entity::Destroy()
{
	m_isActive = false;
	for (Component* component : m_Components)
	{
		component->Destroy();
		delete component;
	}
	m_Components.clear();
}

void bart::Entity::Start()
{
	if (m_isActive)
	{
		for (Component* component : m_Components)
		{
			component->Start();
		}
	}
}

void bart::Entity::SetActive(bool active)
{
	if (m_isActive != active)
	{
		m_isActive = active;
		if (m_isActive)
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
